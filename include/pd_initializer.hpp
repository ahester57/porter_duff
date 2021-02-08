// pd_initialize.cpp : Load/Create initial images and masks
// Austin Hester CS542o dec 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef PD_INITIALIZER_H
#define PD_INITIALIZER_H

#include <opencv2/core/core.hpp>

// draw a centered rectange on image 'dst'
// with given width, height, and color
void centered_rectangle(cv::Mat dst, int w, int h, cv::Scalar color);

// a blue circle
void open_or_create_image_1(std::string imageFile, cv::Mat* image, cv::Mat* mask);

// a red cross
void open_or_create_image_2(std::string imageFile, cv::Mat* image, cv::Mat* mask);

#endif
