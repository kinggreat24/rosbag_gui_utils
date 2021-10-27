/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 17:35:04
 * @LastEditTime: 2021-10-27 17:48:47
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/serialize_factory.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */
#include "rosbag_utils_gui/serialize_factory.h"


std::map<std::string, std::function<RosbagSerializeBaseHandle*()>> RosbagSerializeFactory::obj_map_;
std::map<std::string, RosbagSerializeBaseHandle*>  RosbagSerializeFactory::handler_map_;

RosbagSerializeBaseHandle* RosbagSerializeFactory::produce(const std::string& key)
{
	if(obj_map_.find(key) == obj_map_.end())
	{
		throw std::invalid_argument("the message key is not exist!");
	}
	return obj_map_[key]();
}
std::unique_ptr<RosbagSerializeBaseHandle> RosbagSerializeFactory::produce_unique(const std::string& key)
{
	return std::unique_ptr<RosbagSerializeBaseHandle>(produce(key));
}

std::shared_ptr<RosbagSerializeBaseHandle> RosbagSerializeFactory::produce_shared(const std::string& key)
{
	return std::shared_ptr<RosbagSerializeBaseHandle>(produce(key));
}

	