/*
 * @Author: kinggreat24
 * @Date: 2021-10-20 14:52:05
 * @LastEditTime: 2021-10-27 17:57:17
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/rosbag_serialize_page.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */
#include "rosbag_utils_gui/rosbag_serialize_page.h"
#include <QAction>
#include <QFormLayout>
#include <QStringList>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <unistd.h>
#include <QDir>

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

namespace rosbag_utils_gui
{

    RosbagSerializePage::RosbagSerializePage(QWidget *parent)
        : QWidget(parent)
    {
        initUI();
    }

    RosbagSerializePage::~RosbagSerializePage()
    {
    }

    void RosbagSerializePage::initUI()
    {
        //对ros数据包进行解析
        QVBoxLayout *mainLayout = new QVBoxLayout();

        QGroupBox *input_output_groupbox = new QGroupBox(QString::fromLocal8Bit("输入/输出"));
        QFormLayout *rosbag_input_layout = new QFormLayout();

        rosbag_content_ = new QLineEdit();
        rosbag_content_->setPlaceholderText(QString::fromLocal8Bit("请输入rosbag"));
        QAction *load_rosbag_act_ = new QAction(QIcon("/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/icons/file_explore.png"), "", this);
        connect(load_rosbag_act_, &QAction::triggered, this, &RosbagSerializePage::onLoadRosbagSlot);
        rosbag_content_->addAction(load_rosbag_act_, QLineEdit::TrailingPosition);

        save_path_lineedit_ = new QLineEdit();
        save_path_lineedit_->setPlaceholderText(QString::fromLocal8Bit("请输入文件保存地址"));
        QAction *savepath_act_ = new QAction(QIcon("/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/icons/file_explore.png"), "", this);
        connect(savepath_act_, &QAction::triggered, this, &RosbagSerializePage::onSaveRosbagFileSlot);
        save_path_lineedit_->addAction(savepath_act_, QLineEdit::TrailingPosition);

        rosbag_input_layout->addRow(QString::fromLocal8Bit("rosbag文件名"), rosbag_content_); //
        rosbag_input_layout->addRow(QString::fromLocal8Bit("保存地址"), save_path_lineedit_); //

        input_output_groupbox->setLayout(rosbag_input_layout);

        // rosbag基本信息
        QGroupBox *rosbag_info_groupbox = new QGroupBox(QString::fromLocal8Bit("rosbag基本信息"));
        QFormLayout *rosbag_info_layout = new QFormLayout();
        rosbag_file_label_ = new QLabel();
        rosbag_size_label_ = new QLabel();
        rosbag_begin_label_ = new QLabel();
        rosbag_end_label_ = new QLabel();
        rosbag_duration_label_ = new QLabel();
        rosbag_file_label_->setStyleSheet("QLabel { background-color : white; color : blue; }");
        rosbag_size_label_->setStyleSheet("QLabel { background-color : white; color : blue; }");
        rosbag_begin_label_->setStyleSheet("QLabel { background-color : white; color : blue; }");
        rosbag_end_label_->setStyleSheet("QLabel { background-color : white; color : blue; }");
        rosbag_duration_label_->setStyleSheet("QLabel { background-color : white; color : blue; }");

        rosbag_info_layout->addRow(QString::fromLocal8Bit("文件名"), rosbag_file_label_); //
        rosbag_info_layout->addRow(QString::fromLocal8Bit("大小（GB）"), rosbag_size_label_);
        rosbag_info_layout->addRow(QString::fromLocal8Bit("起始时间"), rosbag_begin_label_);
        rosbag_info_layout->addRow(QString::fromLocal8Bit("结束时间"), rosbag_end_label_);
        rosbag_info_layout->addRow(QString::fromLocal8Bit("时长"), rosbag_duration_label_);
        rosbag_info_layout->setSpacing(10);
        //layout->setRowWrapPolicy(QFormLayout::WrapLongRows);//该参数通常适用于小屏幕中，当标签和文本框在本行显示不全时，文本框会显示在下一行，使得标签独占一行
        rosbag_info_layout->setLabelAlignment(Qt::AlignLeft); //设置标签的对齐方式
        rosbag_info_groupbox->setLayout(rosbag_info_layout);

        //消息设置
        rosbag_topics_tableWidget_ = new QTableWidget(0, 4);
        QStringList header;
        header << "Topics Name"
               << "Topics Type"
               << "Size"
               << "Save?";
        rosbag_topics_tableWidget_->setHorizontalHeaderLabels(header);
        rosbag_topics_tableWidget_->setEditTriggers(QAbstractItemView::NoEditTriggers);   //表头不能编辑
        rosbag_topics_tableWidget_->setSelectionBehavior(QAbstractItemView::SelectRows);  //选择一行
        rosbag_topics_tableWidget_->setSelectionMode(QAbstractItemView::SingleSelection); //单个选择
        rosbag_topics_tableWidget_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        QTableWidgetItem *columnHeaderItem0 = rosbag_topics_tableWidget_->horizontalHeaderItem(0); //获得水平方向表头的Item对象
        columnHeaderItem0->setFont(QFont("Helvetica"));                                            //设置字体
        columnHeaderItem0->setBackgroundColor(QColor(0, 60, 10));                                  //设置单元格背景颜色
        columnHeaderItem0->setTextColor(QColor(200, 111, 30));                                     //设置文字颜色

        //按键区
        ok_ = new QPushButton(QString::fromLocal8Bit("确定"));
        connect(ok_, &QPushButton::clicked, this, &RosbagSerializePage::onOKBtnClickedSlot);
        cancel_ = new QPushButton(QString::fromLocal8Bit("取消"));
        QHBoxLayout *btn_layout = new QHBoxLayout();
        btn_layout->addWidget(ok_);
        btn_layout->addWidget(cancel_);

        // 进度条
        m_progressBar = new QProgressBar();
        m_progressBar->setRange(0, 100);
        m_progressBar->setValue(0);

        mainLayout->addWidget(input_output_groupbox);
        mainLayout->addWidget(rosbag_info_groupbox);
        mainLayout->addWidget(rosbag_topics_tableWidget_);
        mainLayout->addLayout(btn_layout);
        mainLayout->addWidget(m_progressBar);

        setLayout(mainLayout);
    }

    void RosbagSerializePage::onLoadRosbagSlot()
    {
        QFileDialog *fd = new QFileDialog(this); //                                                                 //
        fd->setDirectory(".");
        fd->setNameFilter(tr("rosbag file(*.bag)")); //
        fd->setFileMode(QFileDialog::ExistingFiles);
        fd->setViewMode(QFileDialog::List); //

        if (fd->exec() == QDialog::Accepted) //
        {
            QStringList selected_fileName_lists = fd->selectedFiles(); //
            QString fileName = selected_fileName_lists[0];             //
            rosbag_content_->setText(QString::fromLocal8Bit("%1").arg(fileName));
            fd->close();

            //后台线程加载rosbag
            m_load_rosbag_thread = new LoadRosbagWorkingThread(this);
            m_load_rosbag_thread->setRosbagFileName(QFileInfo(fileName));
            m_load_rosbag_thread->start();

            m_progressBar->setValue(0);
            int progress_status = 0;
            while (!m_load_rosbag_thread->isLoadCompleted())
            {
                progress_status += 3;
                if (progress_status >= 100)
                    progress_status = 0;
                m_progressBar->setValue(progress_status);

                usleep(1000000);
            }
            m_progressBar->setValue(100);

            m_rosbag_view = m_load_rosbag_thread->getRosbagView();
            m_rosbag_bag = m_load_rosbag_thread->getRosbagBag();

            //设置rosbag的名字
            rosbag_file_label_->setText(QString::fromStdString(m_rosbag_bag->getFileName()));

            //设置rosbag的大小
            uint64_t rosbag_size = m_rosbag_bag->getSize();
            rosbag_size_label_->setText(QString("%1").arg(rosbag_size * 1.0 / (1024 * 1024 * 1024), 0, 'g', 4));

            // 设置起始时间
            ros::Time rosbag_begin_time = m_rosbag_view->getBeginTime();
            ros::Time rosbag_end_time = m_rosbag_view->getEndTime();
            rosbag_begin_label_->setText(QString("%1").arg(rosbag_begin_time.toSec()));
            rosbag_end_label_->setText(QString("%1").arg(rosbag_end_time.toSec()));

            //设置topic
            m_rosbag_connection_infos = m_load_rosbag_thread->getConnectionInfo();
            BOOST_FOREACH (const rosbag::ConnectionInfo *info, m_rosbag_connection_infos)
            {
                std::cout << "topics: " << info->topic << " type: " << info->datatype << std::endl;
                int rowIndex = rosbag_topics_tableWidget_->rowCount();
                rosbag_topics_tableWidget_->setRowCount(rowIndex + 1);  //总行数增加1
                rosbag_topics_tableWidget_->setRowHeight(rowIndex, 24); //设置行的高度

                QTableWidgetItem *topic_name_item = new QTableWidgetItem(QString::fromStdString(info->topic));
                QTableWidgetItem *topic_type_item = new QTableWidgetItem(QString::fromStdString(info->datatype));
                rosbag_topics_tableWidget_->setItem(rowIndex, 0, topic_name_item);
                rosbag_topics_tableWidget_->setItem(rowIndex, 1, topic_type_item);

                QTableWidgetItem *checkBox = new QTableWidgetItem();
                checkBox->setCheckState(Qt::Checked);
                rosbag_topics_tableWidget_->setItem(rowIndex, 3, checkBox);
            }

            QMessageBox msgResultBox;
            msgResultBox.setText(QString::fromLocal8Bit("rosbag加载完成！\n"));
            msgResultBox.setIcon(QMessageBox::Information);
            msgResultBox.addButton(QMessageBox::Ok);
            msgResultBox.exec();

            m_progressBar->reset();
        }
        else
        {
            fd->close();
        }
    }

    void RosbagSerializePage::onSaveRosbagFileSlot()
    {
        QString dirpath = QFileDialog::getExistingDirectory(
            this, QString::fromLocal8Bit("选择文件保存目录"), "./",
            QFileDialog::ShowDirsOnly);

        if (dirpath.isEmpty())
        {
            //mkdir
            return;
        }
        else
        {
            QDir dir;
            if (!dir.exists(dirpath))
                dir.mkdir(dirpath);

            save_path_lineedit_->setText(QString::fromLocal8Bit("%1").arg(dirpath));
        }
    }

    void RosbagSerializePage::onOKBtnClickedSlot()
    {
        QDir dir(save_path_lineedit_->text());
        if (!dir.exists())
        {
            QMessageBox msgResultBox;
            msgResultBox.setText(QString::fromLocal8Bit("目录: %1 不存在，请重新选择保存路径！\n").arg(save_path_lineedit_->text()));
            msgResultBox.setIcon(QMessageBox::Information);
            msgResultBox.addButton(QMessageBox::Ok);
            msgResultBox.exec();
            return;
        }

        //开始处理，
        //（1）创建对应的文件夹
        std::cout << "debug RosbagSerializePage::onOKBtnClickedSlot 1" << std::endl;
        int rowCnt = rosbag_topics_tableWidget_->rowCount();
        std::vector<QString> checked_topics;
        std::map<QString, QString> savepath_topics;
        for (int i = 0; i < rowCnt; i++)
        {
            if (rosbag_topics_tableWidget_->item(i, 3)->checkState() == Qt::Checked)
            {
                QString topic_name = rosbag_topics_tableWidget_->item(i, 0)->text();
                checked_topics.push_back(topic_name);

                QString save_path_dir = topic_name.replace(QRegExp("/"), "_");
                QString save_path_full_dir = save_path_lineedit_->text() + "/" + save_path_dir;
                std::cout << "topic: " << topic_name.toStdString() << " save_path_full_dir: " << save_path_full_dir.toStdString() << std::endl;
                savepath_topics[rosbag_topics_tableWidget_->item(i, 0)->text()] = save_path_full_dir;
                QDir dir;
                if (!dir.exists(save_path_full_dir))
                    dir.mkdir(save_path_full_dir);
            }
        }

        //(2)在工作线程中进行解析
        std::cout << "debug RosbagSerializePage::onOKBtnClickedSlot 2" << std::endl;
        m_rosbag_serialize_thread = new RosbagSerializeWorkingThread(
            this, m_rosbag_bag, m_rosbag_view, checked_topics, savepath_topics);

        m_rosbag_serialize_thread->start();
        m_progressBar->setValue(0);
        int progress_status = 0;
        while (!m_rosbag_serialize_thread->isCompleted())
        {
            progress_status += 3;
            if (progress_status >= 100)
                progress_status = 0;
            m_progressBar->setValue(progress_status);

            usleep(1000000);
        }
        m_progressBar->setValue(100);

        //
        QMessageBox msgResultBox;
        msgResultBox.setText(QString::fromLocal8Bit("处理完成！\n"));
        msgResultBox.setIcon(QMessageBox::Information);
        msgResultBox.addButton(QMessageBox::Ok);
        msgResultBox.exec();
    }

}