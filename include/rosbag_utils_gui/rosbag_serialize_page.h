/*
 * @Author: kinggreat24
 * @Date: 2021-10-20 14:23:33
 * @LastEditTime: 2021-10-27 17:56:59
 * @LastEditors: kinggreat24
 * @Description: 解析rosbag到文件
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/rosbag_serialize_page.h
 * 可以输入预定的版权声明、个性签名、空行等
 */
#ifndef ROSBAG_SERIALIZE_PAGE_H
#define ROSBAG_SERIALIZE_PAGE_H

#include <QWidget>
#include <QDir>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QTableWidget>
#include <QProgressBar>

#include "rosbag_utils_gui/load_rosbag_working_thread.h"
#include "rosbag_utils_gui/serialize_rosbag_working_thread.h"



namespace rosbag_utils_gui
{

class RosbagSerializePage : public QWidget
{
	Q_OBJECT

public:
	RosbagSerializePage(QWidget *parent = Q_NULLPTR);
	~RosbagSerializePage();
	void initUI();

protected Q_SLOTS:
    void onLoadRosbagSlot();
	void onSaveRosbagFileSlot();
	void onOKBtnClickedSlot();

private:
	QLineEdit   *rosbag_content_;
	QLineEdit   *save_path_lineedit_;

	QLabel   *rosbag_file_label_;
	QLabel   *rosbag_size_label_;
	QLabel   *rosbag_begin_label_;
	QLabel   *rosbag_end_label_;
	QLabel   *rosbag_duration_label_;
	
	QTableWidget *rosbag_topics_tableWidget_;

	QPushButton *ok_;
	QPushButton *cancel_;

	QProgressBar* m_progressBar;

	rosbag::View* m_rosbag_view;
	rosbag::Bag* m_rosbag_bag;
	std::vector<const rosbag::ConnectionInfo *> m_rosbag_connection_infos;
	LoadRosbagWorkingThread* m_load_rosbag_thread;
	RosbagSerializeWorkingThread * m_rosbag_serialize_thread;

	
};

}

#endif//ROSBAG_SERIALIZE_PAGE_H