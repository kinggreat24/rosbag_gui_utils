/*
 * @Author: kinggreat24
 * @Date: 2021-10-20 11:35:00
 * @LastEditTime: 2021-10-21 09:55:05
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/rosbag_utils_dlg.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/rosbag_utils_dlg.h"
#include "rosbag_utils_gui/rosmaster_utils.h"
#include <fstream>
#include <signal.h>

namespace rosbag_utils_gui
{

    RosbagUtilsDlg::RosbagUtilsDlg(QWidget *parent)
        : QDialog(parent), isRecordingRosbag_(false), recordPid_(0)
    {
        initUI();

        timer_ = new QTimer(this);
        connect(timer_, &QTimer::timeout, this, &RosbagUtilsDlg::updateDefaultBagname);
        timer_->start(100);

        connect(ok_, &QPushButton::clicked, this, &RosbagUtilsDlg::onOkBtnClicked);

        connect(addBtn_, &QPushButton::clicked, this, &RosbagUtilsDlg::onAddTopicItem);
        connect(deleteBtn_, &QPushButton::clicked, this, &RosbagUtilsDlg::onDeleteTopicItem);
        connect(refreshBtn_, &QPushButton::clicked, this, &RosbagUtilsDlg::onRefreshTopics);

        //话题列表点击事件
        connect(totalTopicListView_, &QListView::clicked, this, &RosbagUtilsDlg::onTotalTopicListViewClicked);
        connect(recordTopicListView_, &QListView::clicked, this, &RosbagUtilsDlg::onRecordTopicListViewClicked);

        // 更新当前消息
        topics_.clear();
        std::string subgraph;
        ros::master::V_TopicInfo published_topics;
        getPublishedTopics(subgraph, published_topics);
        for (size_t i = 0; i < published_topics.size(); i++)
        {
            ros::master::TopicInfo topic_info = published_topics.at(i);
            topics_.push_back(QString::fromStdString(topic_info.name));
        }
    }

    RosbagUtilsDlg::~RosbagUtilsDlg()
    {
        totalTopicModel_->clear();
        recordTopicModel_->clear();
    }

    void RosbagUtilsDlg::initUI()
    {
        setWindowTitle(QString::fromLocal8Bit("消息"));
        setWindowIcon(QIcon(":/titan3_data_collection/Resources/record.png"));
        QGroupBox *currentTopicBox = new QGroupBox(QString::fromLocal8Bit("当前Topics"));
        totalTopicListView_ = new QListView();
        totalTopicListView_->setSelectionMode(QAbstractItemView::ExtendedSelection);
        totalTopicModel_ = new QStandardItemModel();
        totalTopicListView_->setModel(totalTopicModel_);
        QHBoxLayout *layout1 = new QHBoxLayout;
        layout1->addWidget(totalTopicListView_);
        currentTopicBox->setLayout(layout1);

        QGroupBox *recordTopicBox = new QGroupBox(QString::fromLocal8Bit("录制Topics"));
        recordTopicListView_ = new QListView();
        recordTopicListView_->setSelectionMode(QAbstractItemView::ExtendedSelection);
        recordTopicModel_ = new QStandardItemModel();
        recordTopicListView_->setModel(recordTopicModel_);
        QHBoxLayout *layout2 = new QHBoxLayout;
        layout2->addWidget(recordTopicListView_);
        recordTopicBox->setLayout(layout2);

        addBtn_ = new QPushButton(this);
        addBtn_->setIcon(QIcon("/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/icons/select.png"));
        addBtn_->setEnabled(false);
        refreshBtn_ = new QPushButton(this);
        refreshBtn_->setIcon(QIcon("/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/icons/refresh.png"));
        deleteBtn_ = new QPushButton(this);
        deleteBtn_->setIcon(QIcon("/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/icons/delete.png"));
        deleteBtn_->setEnabled(false);

        QVBoxLayout *layout3 = new QVBoxLayout();
        layout3->addWidget(addBtn_);
        layout3->addWidget(refreshBtn_);
        layout3->addWidget(deleteBtn_);

        QHBoxLayout *layout4 = new QHBoxLayout();
        bagNameLabel_ = new QLabel(QString::fromLocal8Bit("数据包名字"));
        bagNameLineEdit_ = new QLineEdit();

        QDateTime current_date_time = QDateTime::currentDateTime();
        bagName_ = current_date_time.toString("yyyy-MM-dd_hh:mm:ss");
        bagNameLineEdit_->setText(bagName_);
        bagNameLineEdit_->selectAll();

        ok_ = new QPushButton(QString::fromLocal8Bit("开始"));
        ok_->setIcon(QIcon("/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/icons/database.png"));
        layout4->addWidget(bagNameLabel_);
        layout4->addWidget(bagNameLineEdit_);
        layout4->addWidget(ok_);

        QHBoxLayout *layout5 = new QHBoxLayout();
        layout5->addWidget(currentTopicBox, 2);
        layout5->addLayout(layout3, 1);
        layout5->addWidget(recordTopicBox, 2);

        QVBoxLayout *mainLayout = new QVBoxLayout();
        mainLayout->addLayout(layout5);
        mainLayout->addLayout(layout4);

        setLayout(mainLayout);
    }

    //更新当前的rostopic内容
    void RosbagUtilsDlg::setCurrentTopics(const QVector<QString> &topics)
    {
        topics_ = topics;
    }

    void RosbagUtilsDlg::updateDefaultBagname()
    {
    }

    void RosbagUtilsDlg::onAddTopicItem()
    {
        QModelIndexList modelIndexList = totalTopicListView_->selectionModel()->selectedIndexes();
        Q_FOREACH (QModelIndex modelIndex, modelIndexList)
        {
            QString topic_name = totalTopicModel_->data(modelIndex).toString();
            if (recordTopicModel_->findItems(topic_name).size())
            {
                continue;
            }
            else
            {
                QStandardItem *item = new QStandardItem(
                    QIcon(":/titan3_data_collection/Resources/topic.png"),
                    topic_name);
                recordTopicModel_->appendRow(item);
            }
        }
        //重新生成新的当前topics
        QMap<int, int> rowMap;
        Q_FOREACH (QModelIndex modelIndex, modelIndexList)
        {
            rowMap.insert(modelIndex.row(), 0);
        }
        int rowToDel = 0;
        QMapIterator<int, int> rowMapIterator(rowMap);
        rowMapIterator.toBack();
        while (rowMapIterator.hasPrevious())
        {
            rowMapIterator.previous();
            rowToDel = rowMapIterator.key();
            totalTopicModel_->removeRow(rowToDel);
        }
    }

    void RosbagUtilsDlg::onDeleteTopicItem()
    {
        //将数据添加回去
        QModelIndexList modelIndexList = recordTopicListView_->selectionModel()->selectedIndexes();
        Q_FOREACH (QModelIndex modelIndex, modelIndexList)
        {
            QString topic_name = recordTopicModel_->data(modelIndex).toString();

            if (totalTopicModel_->findItems(topic_name).size())
            {
                continue;
            }
            else
            {
                QStandardItem *item = new QStandardItem(
                    QIcon("/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/icons/ic_topic.png"),
                    topic_name);
                totalTopicModel_->appendRow(item);
            }
        }

        //重新生成新的当前topics
        QMap<int, int> rowMap;
        Q_FOREACH (QModelIndex modelIndex, modelIndexList)
        {
            rowMap.insert(modelIndex.row(), 0);
        }
        int rowToDel = 0;
        QMapIterator<int, int> rowMapIterator(rowMap);
        rowMapIterator.toBack();
        while (rowMapIterator.hasPrevious())
        {
            rowMapIterator.previous();
            rowToDel = rowMapIterator.key();
            recordTopicModel_->removeRow(rowToDel);
        }
    }

    void RosbagUtilsDlg::onRefreshTopics()
    {
        //更新默认数据包的名字
        QDateTime current_date_time = QDateTime::currentDateTime();
        bagName_ = current_date_time.toString("yyyy-MM-dd_hh-mm-ss");
        bagNameLineEdit_->setText(bagName_);
        bagNameLineEdit_->selectAll();

        totalTopicModel_->clear();

        // get published topics
        // 获取当前的topic
        topics_.clear();
        std::string subgraph;
        ros::master::V_TopicInfo published_topics;
        getPublishedTopics(subgraph, published_topics);
        for (size_t i = 0; i < published_topics.size(); i++)
        {
            ros::master::TopicInfo topic_info = published_topics.at(i);
            topics_.push_back(QString::fromStdString(topic_info.name));
        }

        //更新当前消息列表
        for (int i = 0; i < topics_.size(); i++)
        {
            QStandardItem *item = new QStandardItem(
                QIcon("/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/icons/ic_topic.png"),
                topics_.at(i));
            totalTopicModel_->appendRow(item);
        }

        recordTopicModel_->clear();
    }
    //
    void RosbagUtilsDlg::onTotalTopicListViewClicked(const QModelIndex &index)
    {
        QModelIndexList modelIndexList = totalTopicListView_->selectionModel()->selectedIndexes();
        Q_FOREACH (QModelIndex modelIndex, modelIndexList)
        {
            qDebug() << "=" << totalTopicModel_->data(modelIndex).toString();
        }
        if (modelIndexList.size())
            addBtn_->setEnabled(true);
        else
            addBtn_->setEnabled(false);
    }

    void RosbagUtilsDlg::onRecordTopicListViewClicked(const QModelIndex &index)
    {
        QModelIndexList modelIndexList = recordTopicListView_->selectionModel()->selectedIndexes();
        Q_FOREACH (QModelIndex modelIndex, modelIndexList)
        {
            qDebug() << "=" << recordTopicModel_->data(modelIndex).toString();
        }
        if (modelIndexList.size())
            deleteBtn_->setEnabled(true);
        else
            deleteBtn_->setEnabled(false);
    }

    void RosbagUtilsDlg::onOkBtnClicked()
    {
        if (!isRecordingRosbag_)
        {
            //开始录制数据包

            //检查数据包的名字是否为空
            QVector<QString> topics;
            for (int i = 0; i < recordTopicModel_->rowCount(); i++)
            {
                QString topic_name = recordTopicModel_->data(recordTopicModel_->index(i, 0)).toString();
                //QString topic_name = item->data().toString();
                topics.push_back(topic_name);
            }
            if (topics.size() <= 0)
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("数据采集"), QString::fromLocal8Bit("请选择要录制的消息"));
                return;
            }

            if (!bagNameLineEdit_->text().isEmpty())
            {
                if (rosbag_record_callback_)
                {
                    std::cout << "record topics to bag: " << bagNameLineEdit_->text().toStdString() << std::endl;
                    //新开一个线程执行回调函数
                    pid_t fork_Pid = fork();
                    if (fork_Pid < 0)
                        std::cout << "fork error" << std::endl;
                    else if (fork_Pid == 0)
                    {
                        recordPid_ = getpid();
                        std::cout<<"fork child pid: "<<recordPid_<<std::endl;
                        rosbag_record_callback_(bagNameLineEdit_->text(), topics);

                        // rosbag参数
                    #if(USE_ROS_RECODER)
                        rosbag::RecorderOptions* recorder_options_ptr_ = new rosbag::RecorderOptions();
                        recorder_options_ptr_->name = bagNameLineEdit_->text().toStdString();
                        for(size_t i=0;i<topics.size();i++)
                        {
                            recorder_options_ptr_->topics.push_back(topics.at(i).toStdString());
                        }
                        rosbag::Recorder* rosbag_recorder_ptr_ = new rosbag::Recorder(*recorder_options_ptr_);
                        rosbag_recorder_ptr_->run();
                    #else
                        QString topic_string("");
                        for(size_t i=0;i<topics.size();i++)
                        {
                            if(i != topics.size()-1)
                                topic_string += topics.at(i)+QString(" ");
                            else
                                topic_string += topics.at(i);
                        }

                        if(execl("/bin/sh","sh"
                            ,"/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/shell/rosbag_record.sh",
                            bagNameLineEdit_->text().toStdString().c_str(),topic_string.toStdString().c_str(), NULL)<0)
		                {
                            QMessageBox::information(this, QString::fromLocal8Bit("数据采集"), QString::fromLocal8Bit("数据录制中..."));
                        }
                    #endif//
                    
                    }
                    
                    long pid_parent = getpid();
                    std::cout <<"parent pid: "<<pid_parent<<std::endl;
                    
                    isRecordingRosbag_ = true;
                    ok_->setText(QString::fromLocal8Bit("结束"));
                }
            }
            else
                QMessageBox::warning(this, QString::fromLocal8Bit("数据采集"), QString::fromLocal8Bit("请输入数据包的名字"));
        }
        else
        {
            //结束录制数据包
            if (rosbag_finish_record_callback_)
            {
                rosbag_finish_record_callback_();
            }
            
            // kill rosbag record thread
            std::ifstream pid_file_in("./rosbag_record.txt");
            if(pid_file_in.is_open())
            {
                std::cout<<"file is already open"<<endl;
            }
            pid_file_in >> recordPid_;

            std::cout<<"close rosbag record, kill pid: "<<recordPid_<<std::endl;
            int result = kill(recordPid_,SIGINT);
            isRecordingRosbag_ = false;
            ok_->setText(QString::fromLocal8Bit("开始"));
            QMessageBox::information(this, QString::fromLocal8Bit("数据采集"), QString::fromLocal8Bit("数据录制完成..."));
        }
    }

}