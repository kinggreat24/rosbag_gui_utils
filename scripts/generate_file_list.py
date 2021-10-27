#!/usr/bin/python
# -*- coding: utf-8 -*-  
#  
# depth maps
# file: 'rgbd_dataset_freiburg3_cabinet.bag'
# timestamp filename

import os
def file_name(dataset_dir, fold_name):   
    file_path_dir = os.path.join(dataset_dir,fold_name)
    fo = open(fold_name + ".txt", "w")
    
    # write headers
    fo.write("#" + fold_name+"\n")
    fo.write("# file: {}\n".format(dataset_dir+".bag"))
    fo.write("# timestamp filename\n")

    for root, dirs, files in os.walk(file_path_dir):  
        print(root) #当前目录路径  
        print(dirs) #当前路径下所有子目录
        for file_name in files:
            file_name_list = file_name.split(".")
            if file_name_list[-1] == "png":
                fo.write("{} {}\n".format(file_name.replace(".png",""), fold_name + "/" +file_name))
            elif file_name_list[-1] == "bin":
                fo.write("{} {}\n".format(file_name.replace(".bin",""), fold_name + "/" +file_name))
            pass
        fo.flush()
        fo.close()


dataset_dir = "/media/kinggreat24/T7/data/realsense_L515/2021-10-22_14-44-30_laserscan_camera"

file_name(dataset_dir, "rgb")
file_name(dataset_dir, "laserscan")
