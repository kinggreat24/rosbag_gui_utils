/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 16:19:41
 * @LastEditTime: 2021-10-27 19:19:23
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/base_serialize_handle.h
 * 可以输入预定的版权声明、个性签名、空行等
 */
#ifndef BASE_SERIALIZE_HANDLE_H
#define BASE_SERIALIZE_HANDLE_H

#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <QString>
#include <map>

class RosbagSerializeBaseHandle{
public:
	RosbagSerializeBaseHandle()
    {
        clearBuf();
    }
	virtual ~RosbagSerializeBaseHandle(){}

	/** Initialize the handler.  Sets the NodeHandle and calls onInitialize(). */
	void initialize(const std::map<QString, QString> topic_save_dir){		
        m_topic_save_dirs = topic_save_dir;
		onInitialize();
	}
	virtual void onInitialize(){};

	virtual int serialize(rosbag::MessageInstance const m)=0;

    void clearBuf(){memset(file_name_buf,'\0',256);}
protected:
    std::map<QString, QString> m_topic_save_dirs;
    char file_name_buf[256];
};



#endif//