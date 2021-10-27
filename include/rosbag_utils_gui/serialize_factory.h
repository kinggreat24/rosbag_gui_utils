/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 16:18:22
 * @LastEditTime: 2021-10-27 17:56:25
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/serialize_factory.h
 * 可以输入预定的版权声明、个性签名、空行等
 */
#ifndef ROSBAG_SERIALIZE_FACTORY_H
#define ROSBAG_SERIALIZE_FACTORY_H

#include <ros/ros.h>
#include <map>
#include <string>
#include <functional>
#include <memory>
#include "rosbag_utils_gui/base_serialize_handle.h"
#include <iostream>


class RosbagSerializeFactory{
public:
	template<typename T>
	struct register_t
	{
		register_t(const std::string& key)
		{
			ROS_INFO("%s register to the factory.",key.c_str());
		    RosbagSerializeFactory::get().obj_map_.emplace(key, [] { return new T(); });   
		}

		template<typename... Args>
		register_t(const std::string& key, Args... args)
		{
			ROS_INFO("%s register to the factory.",key.c_str());
		    RosbagSerializeFactory::get().obj_map_.emplace(key, [=] { return new T(args...); });
		}
	};

	static RosbagSerializeBaseHandle* produce(const std::string& key);
	static std::unique_ptr<RosbagSerializeBaseHandle> produce_unique(const std::string& key);
    static std::shared_ptr<RosbagSerializeBaseHandle> produce_shared(const std::string& key);
	static RosbagSerializeFactory& get()
	{
		static RosbagSerializeFactory instance;
		return instance;
	} 
	static std::map<std::string, std::function<RosbagSerializeBaseHandle*()> > getMap(){
		return obj_map_;
	}
	static std::map<std::string, RosbagSerializeBaseHandle* > getHandlers(){
		return handler_map_;
	}
private:
	RosbagSerializeFactory(){}
	RosbagSerializeFactory(const RosbagSerializeFactory&) = delete;
    RosbagSerializeFactory(RosbagSerializeFactory&&) = delete;
	

    static std::map<std::string, std::function<RosbagSerializeBaseHandle*()> > obj_map_;
	static std::map<std::string, RosbagSerializeBaseHandle*>  handler_map_;
};


//Register macro
#define REGISTER_MESSAGE_VNAME(T) reg_msg_##T##_
#define REGISTER_MESSAGE(T, key, ...) static RosbagSerializeFactory::register_t<T> REGISTER_MESSAGE_VNAME(T)(key, ##__VA_ARGS__);


#endif//ROSBAG_SERIALIZE_FACTORY_H
