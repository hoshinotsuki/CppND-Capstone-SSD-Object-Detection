# CppND-Capstone-SSD-Object-Detection

[demo](https://drive.google.com/file/d/1XUSKXu-G87XQyCqey40H_eJu593En7O-/view?usp=sharing)

![alt collision avoidance](output/gif.gif)
 
This is a Capstone project for Udacity Nanodegree in C++. 

This a Object Detection with Collision Warning application used in Robotic Automation Navigation.

* Object Detection using MobileNet SSD Model with OpenCV

    MobileNet SSD (Single Shot MultiBox Detector) model is a deeplearning-based object detection model optimized for real-time processing. The model is capable of detecting objects in images or frames from a video stream.  
    
    OpenCV is a popular computer vision library that provides various tools and functions for image and video processing.

* User Input and Display

    The project takes input from either a video stream or an image.
    The detected objects are highlighted with bounding boxes and labeled with their respective class names.
    The results are displayed in a new window, allowing users to visualize the detected objects and their positions.

* Collision Warning

    A crucial aspect of the project is collision warning. If the detected objects are within a certain distance of the robotic system, a collision warning message is displayed on the terminal. This collision warning feature enhances the safety of robotic navigation, allowing the system to take preventive actions when potential collisions are detected.

* Real-time Processing

    The project involves real-time processing, where the object detection and collision warning are performed in near-real-time as the video frames or images are processed. 
  

## Dependencies  

- OpenCV >= 4
- cmake >= 3.7 
- make >= 4.1 (Linux, Mac), 3.81 (Windows) 
- gcc/g++ >= 5.4 

## Download models (Optional)

MobileNet SSD Models were already downloaded in this project. 
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

`./detect -c=0.8 ../images/collision_avoidance.mp4`

`./detect -c=0.7 -n=0.4 ../images/orange.mp4`
 


## Content

1. `CMakeLists.txt`

    CMake configuration file sets up the project with the necessary compiler flags, finds and includes the OpenCV library, defines the source files, and links the executable with the required libraries, ensuring that dependencies are correctly linked and the correct compiler flags are used.

2. `MessageQueue.h`

    Class MessageQueue is designed to manage a queue of messages that can be sent and received concurrently by different threads, using mutexes and condition variables to ensure proper synchronization and thread safety. 

3. `Graphic.h` and `Graphic.cpp`

    Class Graphic is responsible for handling images, drawing object detection results on images, sending message to the terminal for collision warning and managing message queues for communication.  

4. `SSDModel.h` and `SSDModel.cpp`

    Class SSDModel encapsulates the entire object detection pipeline using the SSD MobileNet model. It initializes the model, processes images for object detection, and handles synchronization between threads using mutexes and condition variables.  

5. `main.cpp`

    This function processes images, performs object detection using an SSD model, and displays the detection results on a window. It processes images in a loop, detects objects periodically, and updates the display with the detection results.


## Program Schematic

![alt diagram](output/diagram.png)