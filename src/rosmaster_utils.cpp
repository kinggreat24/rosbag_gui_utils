/*
 * @Author: kinggreat24
 * @Date: 2021-10-20 16:16:49
 * @LastEditTime: 2021-10-20 17:18:58
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/rosmaster_utils.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/rosmaster_utils.h"

namespace rosbag_utils_gui
{

/*
* Get the URI of the master.
*/
bool getUri(std::string &uri)
{
    XmlRpc::XmlRpcValue args, result, payload;
    args[0] = ros::this_node::getName();

    if (!ros::master::execute("getUri", args, result, payload, true))
    {
        std::cout << "Failed!" << std::endl;
        return false;
    }
    std::cout << "----------Master URI----------" << std::endl;
    uri = std::string(payload);
    std::cout << std::string(payload) << std::endl;
}

/*
* Get list of topics that can be subscribed to.
* This does not return topics that have no publishers.
* See getSystemState() to get more comprehensive list.
* */
bool getPublishedTopics(const std::string &subgraph,
                        ros::master::V_TopicInfo &topics)
{
    XmlRpc::XmlRpcValue args, result, payload;
    args[0] = ros::this_node::getName();
    args[1] = subgraph;
    if (!ros::master::execute("getPublishedTopics", args, result, payload,
                                true))
    {
        std::cout << "Failed!" << std::endl;
        return false;
    }
    topics.clear();
    // std::cout << "----------PublishedTopics----------" << std::endl;
    // std::cout << "published_topic_name \t message_name" << std::endl;
    for (int i = 0; i < payload.size(); ++i)
    {
        topics.push_back(
            ros::master::TopicInfo(std::string(payload[i][0]),
                                    std::string(payload[i][1])));
        std::string v1 = std::string(payload[i][0]);
        std::string v2 = std::string(payload[i][1]);
        // std::cout << v1.c_str() << "\t" << v2.c_str() << std::endl;
    }
    return true;
}

/*
* Retrieve list topic names and their types.
* */
bool getTopicTypes(ros::master::V_TopicInfo &topics)
{
    XmlRpc::XmlRpcValue args, result, payload;
    args[0] = ros::this_node::getName();

    if (!ros::master::execute("getTopicTypes", args, result, payload, true))
    {
        std::cout << "Failed!" << std::endl;
        return false;
    }
    topics.clear();
    std::cout << "----------TopicTypes----------" << std::endl;
    std::cout << "topic_name\t message_name" << std::endl;
    for (int i = 0; i < payload.size(); ++i)
    {
        topics.push_back(
            ros::master::TopicInfo(std::string(payload[i][0]),
                                    std::string(payload[i][1])));
        std::string v1 = std::string(payload[i][0]);
        std::string v2 = std::string(payload[i][1]);
        std::cout << v1.c_str() << "\t" << v2.c_str() << std::endl;
    }

    return true;
}

/*
* Get the XML-RPC URI of the node with the associated name/caller_id.
* This API is for looking information about publishers and subscribers.
* Use lookupService instead to lookup ROS-RPC URIs.
*/
bool lookupNode(const std::string &node, std::string &uri)
{
    XmlRpc::XmlRpcValue args, result, payload;
    args[0] = ros::this_node::getName();
    args[1] = node;
    if (!ros::master::execute("lookupNode", args, result, payload, true))
    {
        std::cout << "Failed!" << std::endl;
        return false;
    }
    std::cout << "----------LookupedNode----------" << std::endl;
    uri = std::string(payload);
    std::cout << node << ":" << std::string(payload) << std::endl;
}

/*
* Lookup all provider of a particular service.
*/
bool lookupService(const std::string &service, std::string &uri)
{
    XmlRpc::XmlRpcValue args, result, payload;
    args[0] = ros::this_node::getName();
    args[1] = service;
    if (!ros::master::execute("lookupService", args, result, payload, true))
    {
        std::cout << "Failed!" << std::endl;
        return false;
    }
    std::cout << "----------LookupedService----------" << std::endl;
    uri = std::string(payload);
    std::cout << service << ":" << std::string(payload) << std::endl;
}

/*
* Retrieve list representation of system state
* (i.e. publishers, subscribers, and services).
* */
bool getSystemState()
{
    XmlRpc::XmlRpcValue args, result, payload;
    args[0] = ros::this_node::getName();
    if (!ros::master::execute("getSystemState", args, result, payload, true))
    {
        std::cout << "Failed!" << std::endl;
        return false;
    }
    std::cout << "----------SystemState----------" << std::endl;

    //publishers
    int t = 0;
    std::cout << "Published Topics:" << std::endl;
    for (int j = 0; j < payload[t].size(); ++j)
    {
        //topics
        std::cout << "    *" << std::string(payload[t][j][0]) << ":"
                    << std::endl;
        for (int k = 0; k < payload[t][j][1].size(); ++k)
        {
            //publisher
            std::cout << "        *" << std::string(payload[t][j][1][k])
                        << std::endl;
        }
    }
    t = 1;
    std::cout << "Subscribed Topics:" << std::endl;
    for (int j = 0; j < payload[t].size(); ++j)
    {
        //topics
        std::cout << "    *" << std::string(payload[t][j][0]) << ":"
                    << std::endl;
        for (int k = 0; k < payload[t][j][1].size(); ++k)
        {
            //publisher
            std::cout << "        *" << std::string(payload[t][j][1][k])
                        << std::endl;
        }
    }

    t = 2;
    std::cout << "Services:" << std::endl;
    for (int j = 0; j < payload[t].size(); ++j)
    {
        //topics
        std::cout << "    *" << std::string(payload[t][j][0]) << ":"
                    << std::endl;
        for (int k = 0; k < payload[t][j][1].size(); ++k)
        {
            //publisher
            std::cout << "        *" << std::string(payload[t][j][1][k])
                        << std::endl;
        }
    }
    return true;
}

} //end of namespace rosbag_utils_gui