/*
 * @Author: kinggreat24
 * @Date: 2021-10-20 11:36:40
 * @LastEditTime: 2021-10-20 19:57:53
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/rosbag_utils_panel.h
 * 可以输入预定的版权声明、个性签名、空行等
 */
#ifndef TELEOP_PAD_H
#define TELEOP_PAD_H

//所需要包含的头文件
#include <ros/ros.h>
#include <ros/console.h>
#include <rviz/panel.h> //plugin基类的头文件
#include <QPushButton>
#include <QDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>

#include "rosbag_utils_gui/rosbag_record_page.h"
#include "rosbag_utils_gui/rosbag_serialize_page.h"

// #include <ros/recorder.h>
// #include "rosbag/bag.h"
// #include "rosbag/stream.h"


namespace rosbag_utils_gui
{

    // 所有的plugin都必须是rviz::Panel的子类
    class RosbagUtilsPanel : public rviz::Panel
    {
        // 后边需要用到Qt的信号和槽，都是QObject的子类，所以需要声明Q_OBJECT宏
        Q_OBJECT
    public:
        // 构造函数，在类中会用到QWidget的实例来实现GUI界面，这里先初始化为0即可
        RosbagUtilsPanel(QWidget *parent = 0);

        // 重载rviz::Panel积累中的函数，用于保存、加载配置文件中的数据，在我们这个plugin
        // 中，数据就是topic的名称
        virtual void load(const rviz::Config &config);
        virtual void save(rviz::Config config) const;
   
        
    protected:
        void initUI();
        void createIcons();

    protected Q_SLOTS:
        void changePage(QListWidgetItem *current, QListWidgetItem *previous);

    protected:
        // The ROS node handle.
        ros::NodeHandle nh_;

        QListWidget* contentsWidget;
        QStackedWidget *pagesWidget;
        QHBoxLayout *mainLayout;
        
        RosbagRecordPage *recordPage_;
        RosbagSerializePage* serializePage_;

        QListWidgetItem *recordButton_;
        QListWidgetItem *serializedButton_;
    };

} // end namespace rviz_teleop_commander

#endif // TELEOP_PANEL_H