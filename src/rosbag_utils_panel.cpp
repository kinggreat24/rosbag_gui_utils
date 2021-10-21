/*
 * @Author: kinggreat24
 * @Date: 2021-10-20 11:36:32
 * @LastEditTime: 2021-10-20 21:54:42
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/rosbag_utils_panel.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */
#include <stdio.h>

#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

#include <geometry_msgs/Twist.h>
#include <QDebug>

#include "rosbag_utils_gui/rosbag_utils_panel.h"

namespace rosbag_utils_gui
{

// 构造函数，初始化变量
RosbagUtilsPanel::RosbagUtilsPanel(QWidget *parent)
    : rviz::Panel(parent)
{
    initUI();
}

void RosbagUtilsPanel::initUI()
{
	setWindowIcon(QIcon("/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/icons/rosbag_record.png"));
	setMinimumSize(640, 320);
	contentsWidget = new QListWidget;
	contentsWidget->setViewMode(QListView::IconMode);
	contentsWidget->setIconSize(QSize(96, 96));
	contentsWidget->setMovement(QListView::Static);
	contentsWidget->setMaximumWidth(128);
	contentsWidget->setSpacing(12);

	pagesWidget    = new QStackedWidget;
	recordPage_    = new RosbagRecordPage();
	serializePage_ = new RosbagSerializePage();
	
	pagesWidget->addWidget(recordPage_);
	pagesWidget->addWidget(serializePage_);
	
	createIcons();
	contentsWidget->setCurrentRow(0);

	mainLayout = new QHBoxLayout;
	mainLayout->addWidget(contentsWidget);
	mainLayout->addWidget(pagesWidget);
	setLayout(mainLayout);
	setWindowTitle(QString::fromLocal8Bit("泰坦数据采集"));
}

// 重载父类的功能
void RosbagUtilsPanel::save(rviz::Config config) const
{
    rviz::Panel::save(config);


    // config.mapSetValue("Topic", output_topic_);
}

// 重载父类的功能，加载配置数据
void RosbagUtilsPanel::load(const rviz::Config &config)
{
    rviz::Panel::load(config);
    
    
    // QString topic;
    // if (config.mapGetString("Topic", &topic))
    // {
    //     output_topic_editor_->setText(topic);
    //     updateTopic();
    // }
}

void RosbagUtilsPanel::createIcons()
{
	recordButton_ = new QListWidgetItem(contentsWidget);
	recordButton_->setIcon(QIcon("/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/icons/rosbag_record.png"));
	recordButton_->setText(QString::fromLocal8Bit("录制数据包"));
	recordButton_->setTextAlignment(Qt::AlignHCenter);
	recordButton_->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	serializedButton_ = new QListWidgetItem(contentsWidget);
	serializedButton_->setIcon(QIcon("/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/icons/rosbag_serialize.png"));
	serializedButton_->setText(QString::fromLocal8Bit("解析数据包"));
	serializedButton_->setTextAlignment(Qt::AlignHCenter);
	serializedButton_->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	connect(contentsWidget, &QListWidget::currentItemChanged, this, &RosbagUtilsPanel::changePage);
}

void RosbagUtilsPanel::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (!current)
		current = previous;

	pagesWidget->setCurrentIndex(contentsWidget->row(current));
}




} // end namespace rosbag_utils_gui

// 声明此类是一个rviz的插件
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rosbag_utils_gui::RosbagUtilsPanel, rviz::Panel)
// END_TUTORIAL