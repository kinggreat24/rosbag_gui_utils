/*
 * @Author: kinggreat24
 * @Date: 2021-10-20 11:27:03
 * @LastEditTime: 2021-10-20 22:15:07
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/rosbag_utils_dlg.h
 * 可以输入预定的版权声明、个性签名、空行等
 */

#ifndef ROSBAG_UTILS_DLG_H
#define ROSBAG_UTILS_DLG_H

#include <QDialog>
#include <qcheckbox.h>
#include <qmessagebox.h>
#include <QLineEdit>
#include <qlistwidget.h>
#include <QStandardItemModel>
#include <qlistview.h>
#include <QGroupBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateTime>
#include <QTimer>
#include <QModelIndex>
#include <qdebug.h>
#include <QMap>
#include <QMapIterator>
#include <QtCore>
#include <qglobal.h>

#include <boost/function.hpp>
#include <rosbag/recorder.h>

namespace rosbag_utils_gui{

typedef boost::function<bool (QString, QVector<QString>) > ROSBAG_RECORD_CALLBACK;
typedef boost::function<bool () > ROSBAG_FINISH_RECORD_CALLBACK;
class RosbagUtilsDlg : public QDialog
{
// 后边需要用到Qt的信号和槽，都是QObject的子类，所以需要声明Q_OBJECT宏
Q_OBJECT
public:
	RosbagUtilsDlg(QWidget *parent = Q_NULLPTR);
	~RosbagUtilsDlg();

	void initUI();
	void setCurrentTopics(const QVector<QString>& topics);

	void setRosbagRecordCallback(const ROSBAG_RECORD_CALLBACK& callback_){rosbag_record_callback_ = callback_;}
	void setRosbagFinishRecordCallback(const ROSBAG_FINISH_RECORD_CALLBACK& callback_){rosbag_finish_record_callback_ = callback_;}

// signals:
// 	void recordRosbag(const QString& name, const QVector<QString>& topics);

public Q_SLOTS:
	void onOkBtnClicked();
	void updateDefaultBagname();
	void onAddTopicItem();
	void onDeleteTopicItem();
	void onRefreshTopics();
	void onTotalTopicListViewClicked(const QModelIndex& index);
	void onRecordTopicListViewClicked(const QModelIndex& index);

private:
	QListView *totalTopicListView_;
	QListView *recordTopicListView_;

	QStandardItemModel *totalTopicModel_;
	QStandardItemModel *recordTopicModel_;

	QPushButton *addBtn_;
	QPushButton *refreshBtn_;
	QPushButton *deleteBtn_;

	QLabel *bagNameLabel_;
	QLineEdit *bagNameLineEdit_;
	QPushButton *ok_;

	QString bagName_;
	QTimer *timer_;

	QVector<QString> topics_;

	ROSBAG_RECORD_CALLBACK rosbag_record_callback_;
	ROSBAG_FINISH_RECORD_CALLBACK rosbag_finish_record_callback_;

	bool isRecordingRosbag_;
	pid_t recordPid_;
};

}//end of namespace rosbag_utils_gui

#endif//ROSBAG_UTILS_DLG_H