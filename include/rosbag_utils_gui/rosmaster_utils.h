/*
 * @Author: kinggreat24
 * @Date: 2021-10-20 16:16:39
 * @LastEditTime: 2021-10-20 16:26:58
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/rosmatser_utils.h
 * 可以输入预定的版权声明、个性签名、空行等
 */
#ifndef ROSMASTER_UTILS_H
#define ROSMASTER_UTILS_H


#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ros/master.h>
#include <iostream>


namespace rosbag_utils_gui{

bool getUri(std::string&uri);


/*
 * Get list of topics that can be subscribed to.
 * This does not return topics that have no publishers.
 * See getSystemState() to get more comprehensive list.
 * */
bool getPublishedTopics(const std::string& subgraph,
    ros::master::V_TopicInfo& topics);

/*
 * Retrieve list topic names and their types.
 * */
bool getTopicTypes(ros::master::V_TopicInfo& topics);

/*
 * Get the XML-RPC URI of the node with the associated name/caller_id.
 * This API is for looking information about publishers and subscribers.
 * Use lookupService instead to lookup ROS-RPC URIs.
 */
bool lookupNode(const std::string& node, std::string&uri);

/*
 * Lookup all provider of a particular service.
 */
bool lookupService(const std::string& service, std::string&uri);

/*
 * Retrieve list representation of system state
 * (i.e. publishers, subscribers, and services).
 * */
bool getSystemState();




}


#endif//ROSMASTER_UTILS_H