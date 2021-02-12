// pd_initialize.cpp : Load/Create initial images and masks
// Austin Hester CS542o dec 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#include "./include/dir_func.hpp"
#include "./include/pd_initializer.hpp"


const int default_height = 480;
const int default_width = 640;
const cv::Size default_size = cv::Size(default_width, default_height);


// draw a centered rectange on image 'dst'
// with given width, height, and color
void
centered_rectangle(cv::Mat dst, int w, int h, cv::Scalar color)
{
    cv::rectangle(dst,
        cv::Rect(
            (default_width/2)-(w/2),
            (default_height/2)-(h/2),
            w, h
        ),
        color,
        cv::FILLED, cv::LINE_8
    );
}

// a blue circle
void
open_or_create_image_1(std::string imageFile, cv::Mat* image, cv::Mat* mask)
{
    if (imageFile.size() == 0) {
        std::cout << "Using default image1" << std::endl;
        *image = cv::Mat::zeros(default_size, CV_8UC3);
        // draw a blue circle
        cv::circle(*image,
            cv::Point((default_width/2), (default_height/2)), 150,
            cv::Scalar(222, 235, 0), //blue
            cv::FILLED, cv::LINE_8
        );
    } else {
        // open image, grayscale = false
        *image = open_image(imageFile.c_str(), false);
        cv::resize(*image, *image, default_size);
    }
    // TODO allow importing mask
    // draw circle mask
    *mask = cv::Mat::zeros(image->size(), CV_8UC1);
    cv::circle(*mask,
        cv::Point((default_width/2), (default_height/2)), 150,
        cv::Scalar(255, 255, 255), //blue
        cv::FILLED, cv::LINE_8
    );
}

// a red cross
void
open_or_create_image_2(std::string imageFile, cv::Mat* image, cv::Mat* mask)
{
    if (imageFile.size() == 0) {
        std::cout << "Using default image2" << std::endl;
        *image = cv::Mat::zeros(default_size, CV_8UC3);
        // draw a red cross
        centered_rectangle(*image, 96, 512, cv::Scalar(0, 77, 222));
        centered_rectangle(*image, 548, 128, cv::Scalar(0, 77, 222));
    } else {
        // open image, grayscale = false
        *image = open_image(imageFile.c_str(), false);
        cv::resize(*image, *image, default_size);
    }
    // TODO allow importing mask
    // draw cross mask
    *mask = cv::Mat::zeros(image->size(), CV_8UC1);
    centered_rectangle(*mask, 96, 512, cv::Scalar(255, 255, 255));
    centered_rectangle(*mask, 548, 128, cv::Scalar(255, 255, 255));
}
