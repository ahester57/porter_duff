// porter_duff.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Austin Hester CS542o dec 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>
#include <iostream>

#include "./include/cla_parse.hpp"
#include "./include/dir_func.hpp"
#include "./include/porter_duff_ops.hpp"


const std::string WINDOW_NAME = "Porter-Duff";

// CLA variables
std::string imageFile1;
std::string imageFile2;
std::string maskFile1;
std::string maskFile2;
bool grayscale;

cv::Mat image1;
cv::Mat image2;

const int default_height = 480;
const int default_width = 640;

// 'event loop' for keypresses
int
wait_key()
{
    char key_pressed = cv::waitKey(0) & 255;
    if (cv::getWindowProperty(WINDOW_NAME, cv::WND_PROP_VISIBLE) < 1) {
        // this ends the program if window is closed
        return 0;
    }
    // 'q' or  <escape> quits out
    if (key_pressed == 27 || key_pressed == 'q') {
        cv::destroyAllWindows();
        return 0;
    }
    return 1;
}


cv::Mat
do_clear(cv::Mat src)
{
    return clear_i1(src);
}


cv::Mat
do_copy(cv::Mat src)
{
    // cv::Mat copy;
    return copy_i1(src);
}


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


int
main(int argc, const char** argv)
{
    // parse and save command line args
    int parse_result = parse_arguments(
        argc, argv,
        &imageFile1,
        &imageFile2,
        &maskFile1,
        &maskFile2,
        &grayscale
    );
    if (parse_result != 1) return parse_result;


    if (imageFile1.size() == 0) {
        std::cout << "Using default image1" << std::endl;
        image1 = cv::Mat::zeros(default_height, default_width, CV_8UC3);
        cv::circle(image1,
            cv::Point((default_width/2), (default_height/2)), 150,
            cv::Scalar(222, 235, 0), //blue
            cv::FILLED, cv::LINE_8
        );
    } else {
        // open image, grayscale = true
        open_image(image1, imageFile1.c_str(), grayscale);
    }

    if (imageFile2.size() == 0) {
        std::cout << "Using default imageFile2" << std::endl;
        image2 = cv::Mat::zeros(default_height, default_width, CV_8UC3);
        centered_rectangle(image2, 96, 512, cv::Scalar(0, 77, 222));
        centered_rectangle(image2, 548, 128, cv::Scalar(0, 77, 222));
    } else {
        // open image, grayscale = true
        open_image(image2, imageFile2.c_str(), grayscale);
    }

    // deep keep to displayed_image
    // og_image->image.copyTo(displayed_image);

    std::cout << "\nShortcuts:\n\tq\t- quit\n";

    // display the original images
    cv::imshow(WINDOW_NAME + "_1", image1);
    cv::imshow(WINDOW_NAME + "_2", image2);

    while (wait_key());

    cv::imshow("Clear_1", do_clear(image1));
    cv::imshow("Clear_2", do_clear(image2));

    while (wait_key());

    cv::imshow("Copy_1", do_copy(image1));
    cv::imshow("Copy_2", do_copy(image2));

    // 'event loop' for keypresses
    while (wait_key());

    image1.release();
    image2.release();

    return 0;
}
