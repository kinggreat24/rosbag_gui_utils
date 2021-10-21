// /*
//  * @Author: kinggreat24
//  * @Date: 2021-10-20 19:21:33
//  * @LastEditTime: 2021-10-20 19:51:53
//  * @LastEditors: kinggreat24
//  * @Description: 
//  * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/rosbag_recorder.h
//  * 可以输入预定的版权声明、个性签名、空行等
//  */

// #ifndef ROSBAG_RECORDER_H
// #define ROSBAG_RECORDER_H

// #include <sys/stat.h>
// #include <termios.h>
// #include <time.h>
// #include <unistd.h>

// #include <queue>
// #include <string>
// #include <vector>

// #include <boost/thread/condition.hpp>
// #include <boost/thread/mutex.hpp>
// #include <boost/regex.hpp>

// #include <ros/ros.h>
// #include <ros/time.h>

// #include <std_msgs/Empty.h>
// #include <topic_tools/shape_shifter.h>

// #include "rosbag/bag.h"
// #include "rosbag/stream.h"

// namespace rosbag
// {

// class OutgoingMessage
// {
// public:
//     OutgoingMessage(std::string const &_topic, topic_tools::ShapeShifter::ConstPtr _msg, boost::shared_ptr<ros::M_string> _connection_header, ros::Time _time);

//     std::string topic;
//     topic_tools::ShapeShifter::ConstPtr msg;
//     boost::shared_ptr<ros::M_string> connection_header;
//     ros::Time time;
// };

// class OutgoingQueue
// {
// public:
//     OutgoingQueue(std::string const &_filename, std::queue<OutgoingMessage> *_queue, ros::Time _time);

//     std::string filename;
//     std::queue<OutgoingMessage> *queue;
//     ros::Time time;
// };

// struct RecorderOptions
// {
//     RecorderOptions();

//     bool trigger;
//     bool record_all;
//     bool regex;
//     bool do_exclude;
//     bool quiet;
//     bool append_date;
//     bool snapshot;
//     bool verbose;
//     CompressionType compression;
//     std::string prefix;
//     std::string name;
//     boost::regex exclude_regex;
//     uint32_t buffer_size;
//     uint32_t limit;
//     bool split;
//     uint32_t max_size;
//     ros::Duration max_duration;
//     std::string node;

//     std::vector<std::string> topics;
// };

// class Recorder
// {
// public:
//     Recorder(RecorderOptions const &options);

//     void doTrigger();

//     bool isSubscribed(std::string const &topic) const;

//     boost::shared_ptr<ros::Subscriber> subscribe(std::string const &topic);

//     int run();

// private:
//     void printUsage();

//     void updateFilenames();
//     void startWriting();
//     void stopWriting();

//     bool checkLogging();
//     bool scheduledCheckDisk();
//     bool checkDisk();

//     void snapshotTrigger(std_msgs::Empty::ConstPtr trigger);
//     //    void doQueue(topic_tools::ShapeShifter::ConstPtr msg, std::string const& topic, boost::shared_ptr<ros::Subscriber> subscriber, boost::shared_ptr<int> count);
//     void doQueue(ros::MessageEvent<topic_tools::ShapeShifter const> msg_event, std::string const &topic, boost::shared_ptr<ros::Subscriber> subscriber, boost::shared_ptr<int> count);
//     void doRecord();
//     bool checkSize();
//     bool checkDuration(const ros::Time &);
//     void doRecordSnapshotter();
//     void doCheckMaster(ros::TimerEvent const &e, ros::NodeHandle &node_handle);

//     bool shouldSubscribeToTopic(std::string const &topic, bool from_node = false);

//     template <class T>
//     static std::string timeToStr(T ros_t);

// private:
//     RecorderOptions options_;

//     Bag bag_;

//     std::string target_filename_;
//     std::string write_filename_;

//     std::set<std::string> currently_recording_;
//     int num_subscribers_;

//     int exit_code_;

//     boost::condition_variable_any queue_condition_;
//     boost::mutex queue_mutex_;
//     std::queue<OutgoingMessage> *queue_;
//     uint64_t queue_size_;
//     uint64_t max_queue_size_;

//     uint64_t split_count_;

//     std::queue<OutgoingQueue> queue_queue_;

//     ros::Time last_buffer_warn_;

//     ros::Time start_time_;

//     bool writing_enabled_;
//     boost::mutex check_disk_mutex_;
//     ros::WallTime check_disk_next_;
//     ros::WallTime warn_next_;
// };

// } // namespace rosbag

// #endif //ROSBAG_RECORDER_H