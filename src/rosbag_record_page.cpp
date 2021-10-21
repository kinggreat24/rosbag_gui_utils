/*
 * @Author: kinggreat24
 * @Date: 2021-10-20 14:46:36
 * @LastEditTime: 2021-10-20 22:14:02
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/rosbag_record_page.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/rosbag_record_page.h"


namespace rosbag_utils_gui
{

RosbagRecordPage::RosbagRecordPage(QWidget *parent)
    : QWidget(parent)
{
    initUI();

    connect(rosbag_record_btn_,&QPushButton::clicked, this, &RosbagRecordPage::onRosbagRecordSlot);
}


RosbagRecordPage::~RosbagRecordPage()
{

}

void RosbagRecordPage::initUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout();

	rosbag_record_btn_ = new QPushButton(QString::fromLocal8Bit("录制"));
	QHBoxLayout * layout = new QHBoxLayout;
	layout->addWidget(rosbag_record_btn_);

	// mainLayout->addWidget(mapView_);
	mainLayout->addLayout(layout);

	setLayout(mainLayout);
}

void RosbagRecordPage::onRosbagRecordSlot()
{
    rosbag_record_dlg_ = new RosbagUtilsDlg(this);
    rosbag_record_dlg_->setRosbagRecordCallback(boost::bind(&RosbagRecordPage::onRosbagRecordCallback,
        this,_1,_2));
    rosbag_record_dlg_->show();
}


bool RosbagRecordPage::onRosbagRecordCallback(QString rosbag_name, QVector<QString> topic_names)
{
    // recorder_options_ptr_ = new rosbag::RecorderOptions();
    // recorder_options_ptr_->name = rosbag_name.toStdString();
    // for(size_t i=0;i<topic_names.size();i++)
    // {
    //     recorder_options_ptr_->topics.push_back(topic_names.at(i).toStdString());
    // }
    // rosbag_recorder_ptr_ = new rosbag::Recorder(*recorder_options_ptr_);
    // rosbag_recorder_ptr_->run();
}

bool RosbagRecordPage::onFinishRosbagRecordCallback()
{
    
}


}//end of namespace rosbag_utils_gui