/*
 * @Author: kinggreat24
 * @Date: 2021-10-20 14:23:33
 * @LastEditTime: 2021-10-20 15:01:37
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

namespace rosbag_utils_gui
{

class RosbagSerializePage : public QWidget
{
	Q_OBJECT

public:
	RosbagSerializePage(QWidget *parent = Q_NULLPTR);
	~RosbagSerializePage();
	void initUI();
	
private:
	QPushButton *send_;
	QLineEdit   *content_;


};

}

#endif//ROSBAG_SERIALIZE_PAGE_H