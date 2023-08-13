# CppND-Capstone-SSD-Object-Detection

Capstone for Udacity Nanodegree in C++

## Requirements

- OpenCV >= 4
- cmake >= 3.7 
- make >= 4.1 (Linux, Mac), 3.81 (Windows) 
- gcc/g++ >= 5.4 

## Download models (Optional)

In this example I used MobileNet SSD from TensorFlow to be implemented in OpenCV. 
Models were already downloaded in this project. 
Here shows how to download those models if needed.

In the root directory (this repository), execute the command below:

1. `mkdir models`

2.  download the model file 

    `wget https://github.com/rdeepc/ExploreOpencvDnn/raw/master/models/frozen_inference_graph.pb -O models/frozen_inference_graph.pb`


3. download the config file

    `wget https://github.com/rdeepc/ExploreOpencvDnn/raw/master/models/ssd_mobilenet_v2_coco_2018_03_29.pbtxt -O models/ssd_mobilenet_v2_coco_2018_03_29.pbtxt`

4. download the objection classes file to show results

    `wget https://raw.githubusercontent.com/opencv/opencv/master/samples/data/dnn/object_detection_classes_coco.txt  -O models/object_detection_classes_coco.txt `

## Build

In the root directory (this repository), execute the command below:

1. `rm -rf build` (optional)
2. `mkdir build`
3. `cd build`
4. `cmake ..`
5. `make`

## Run

In `build` directory, run the executable like below:

`./detect [options] <image file>`
 

#### Options

- `-c` : specifies _confidence threshold_ between 0 and 1.0. If omitted, default value is 0.5. (example: `-c=0.3`)
- `-n` : specifies the threshold used for _Non-max Suppression_ between 0 and 1.0. If omitted, default value is 0.5. (example: `-n=0.7`)
- `-h` `-?` `--help` `--usage`: Show usage.

#### Example

`./detect -c=0.6 ../images/apple.mp4`

`./detect -c=0.2 -n=0.5 ../images/harvesting.mp4`

`./detect -c=0.7 -n=0.4 ../images/orange.mp4`

`./detect -c=0.5 ../images/pplfollowing.mp4`

`./detect -c=0.8 ../images/collision_avoidance.mp4`


## Output

<video controls width="500">
  <source src="output/demo.mp4" type="video/mp4"> 
</video>


## Content

1. `CMakeLists.txt`

    CMake configuration file sets up the project with the necessary compiler flags, finds and includes the OpenCV library, defines the source files, and links the executable with the required libraries, ensuring that dependencies are correctly linked and the correct compiler flags are used.

2. `MessageQueue.h`

    Class MessageQueue is designed to manage a queue of messages that can be sent and received concurrently by different threads, using mutexes and condition variables to ensure proper synchronization and thread safety. 

3. `Graphic.h` and `Graphic.cpp`

    Class Graphic is responsible for handling images, drawing object detection results on images, and managing message queues for communication.  

4. `SSDModel.h` and `SSDModel.cpp`

    Class SSDModel 




5. `main.cpp`


## Program Schematic

