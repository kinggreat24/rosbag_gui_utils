#！/bin/bash
###
 # @Author: kinggreat24
 # @Date: 2021-10-20 22:22:38
 # @LastEditTime: 2021-10-21 09:44:46
 # @LastEditors: kinggreat24
 # @Description: 
 # @FilePath: /rosbag_utils_gui/shell/rosbag_record.sh
 # 可以输入预定的版权声明、个性签名、空行等
### 
echo "output rosbag_name: $1"
echo "recorded topics: '$2'"
sleep 1
# bash -c "roslaunch --pid=/home/kinggreat24/direct_lidar_align_ws/src/rosbag_utils_gui/rosbag_record.txt rosbag_utils_gui rosbag_record.launch rosbag_name:=$1 rosbag_topics:=$2" 
bash -c "source /home/kinggreat24/direct_lidar_align_ws/devel/setup.bash; \
    roslaunch --pid=./rosbag_record.txt \
    rosbag_utils_gui rosbag_record.launch rosbag_name:=$1 rosbag_topics:='$2'" 
