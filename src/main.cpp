//
// SDD object detection using OpenCV
//   - Using SSD MobileNet v2 COCO data with TensorFlow
// 
// Sample source:
// https://github.com/opencv/opencv/blob/master/samples/dnn/object_detection.cpp
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/filesystem.hpp>

#if CV_VERSION_MAJOR < 4
#pragma message( "OpenCV version < 4" )
#endif

#include "SSDModel.h"
#include "Graphic.h"


int main(int argc, char** argv)
{
    // Get command line options.
    const cv::String keys = 
        "{help h usage ? |      | print this message. }"
        "{c conf         |   .5 | Confidence threshold. }"
        "{n nms          |   .5 | Non-max suppression threshold. }"
        "{@input         |<none>| Input image or movie file. }";
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("SSD MobileNet Object Detection with C++");
    if(parser.has("help") || argc == 1)
    {
        parser.printMessage();
        return 0;
    }
    float conf_threshold = parser.get<float>("c");
    float nms_threshold = parser.get<float>("n");

    // Check if the input file has been specified properly.
    std::string img_file = parser.get<std::string>("@input");
    if(img_file == "")
    {
        std::cout << "Input file is not specified.\n";
        parser.printMessage();
        return 0;
    }
    if(!cv::utils::fs::exists(img_file))
    {
        std::cout << "Input file (" << img_file << ") not found.\n" ;
        return 0;
    }

    const std::string window_name= "Object Detection";
    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    
    // Create queues for sending image to display and to detection
    std::shared_ptr<MessageQueue<cv::Mat>> image_queue(new MessageQueue<cv::Mat>);
    std::shared_ptr<MessageQueue<cv::Mat>> detection_queue(new MessageQueue<cv::Mat>);

    // Create SSD MobileNet model
    SSDModel ssd_model(conf_threshold, nms_threshold);

    // Create Graphic model which handles images 
    Graphic input(img_file, ssd_model.getClassSize());

    // Set shared pointers of queues into objects
    input.setImageQueue(image_queue);
    input.setDetectionQueue(detection_queue);
    ssd_model.setDetectionQueue(detection_queue);

    cv::resizeWindow(window_name, input.getWindowSize());

    // Launch the readinig thread and the detecting thread
    input.thread_for_read();
    ssd_model.thread_for_detection();

    std::vector<int> classIds;
    std::vector<std::string> classNames;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;
    cv::Mat current_image;

    // waittime of processing the next iteration
    const int duration = (int)(1000/input.getFps());

    // the number of iteration processed within the loop 
    int count = 0;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    while(cv::waitKey(duration) < 0) 
    {
        if(image_queue->getTotal() > 0 && count >= image_queue->getTotal()) 
            break; 

        // receive image from the thread of reading
        current_image = image_queue->receive();
  
        // object detection at a certain frequency 
        if(count%(input.getDetectFreq()) == 0) 
            ssd_model.getNextDetection(classIds, classNames, confidences, boxes); 

        input.drawResult(current_image, classIds, classNames, confidences, boxes);

        cv::imshow(window_name, current_image);

        ++count;
    }
    std::cout << " --- Object detection finished. Press Enter key to quit.---\n";

    // keep the display window open after the loop finishes.
    cv::waitKey(0);
   
    return 0;
}
