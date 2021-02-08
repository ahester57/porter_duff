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


const int default_height = 480;
const int default_width = 640;
const cv::Size default_size = cv::Size(default_width, default_height);

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


void
do_porter_duff_ops(cv::Mat image1, cv::Mat image2, cv::Mat mask1, cv::Mat mask2)
{
    // cv::imshow("clear_1", clear_i1(image1));
    // cv::imshow("clear_2", clear_i1(image2));

    cv::imshow("bitwise_clear_1", bitwise_clear_i1(image1, mask1));
    cv::imshow("bitwise_clear_2", bitwise_clear_i1(image2, mask2));

    while (wait_key());

    // cv::imshow("copy_1", copy_i1(image1));
    // cv::imshow("copy_2", copy_i1(image2));

    cv::imshow("bitwise_copy_1", bitwise_copy_i1(image1, mask1));
    cv::imshow("bitwise_copy_2", bitwise_copy_i1(image2, mask2));

    while (wait_key());

    // cv::imshow("1_over_2", do_porter_operation(i1_over_i2, image1, image2, mask1, mask2));
    // cv::imshow("2_over_1", do_porter_operation(i1_over_i2, image2, image1, mask2, mask1));

    cv::imshow("bitwise_1_over_2", bitwise_i1_over_i2(image1, image2, mask1, mask2));
    cv::imshow("bitwise_2_over_1", bitwise_i1_over_i2(image2, image1, mask2, mask1));

    while (wait_key());

    cv::imshow("1_in_2", do_porter_operation(i1_in_i2, image1, image2, mask1, mask2));
    cv::imshow("2_in_1", do_porter_operation(i1_in_i2, image2, image1, mask2, mask1));

    while (wait_key());

    cv::imshow("1_out_2", do_porter_operation(i1_out_i2, image1, image2, mask1, mask2));
    cv::imshow("2_out_1", do_porter_operation(i1_out_i2, image2, image1, mask2, mask1));

    while (wait_key());

    // cv::imshow("1_atop_2", do_porter_operation(i1_atop_i2, image1, image2, mask1, mask2));
    // cv::imshow("2_atop_1", do_porter_operation(i1_atop_i2, image2, image1, mask2, mask1));

    cv::imshow("bitwise_1_atop_2", bitwise_i1_atop_i2(image1, image2, mask1, mask2));
    cv::imshow("bitwise_2_atop_1", bitwise_i1_atop_i2(image2, image1, mask2, mask1));

    while (wait_key());

    cv::imshow("1_xor_2", do_porter_operation(i1_xor_i2, image1, image2, mask1, mask2));
    cv::imshow("2_xor_1", do_porter_operation(i1_xor_i2, image2, image1, mask2, mask1));
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
        &maskFile2
    );
    if (parse_result != 1) return parse_result;

    cv::Mat image1;
    cv::Mat image2;

    cv::Mat mask1;
    cv::Mat mask2;

    if (imageFile1.size() == 0) {
        std::cout << "Using default image1" << std::endl;
        image1 = cv::Mat::zeros(default_size, CV_8UC3);
        // draw a blue circle
        cv::circle(image1,
            cv::Point((default_width/2), (default_height/2)), 150,
            cv::Scalar(222, 235, 0), //blue
            cv::FILLED, cv::LINE_8
        );
        // draw circle mask
        mask1 = cv::Mat::zeros(image1.size(), CV_8UC1);
        cv::circle(mask1,
            cv::Point((default_width/2), (default_height/2)), 150,
            cv::Scalar(255, 255, 255), //blue
            cv::FILLED, cv::LINE_8
        );
        mask1 /= 255;
    } else {
        // open image, grayscale = true
        image1 = open_image(imageFile1.c_str(), false);
        cv::resize(image1, image1, default_size);
    }

    if (imageFile2.size() == 0) {
        std::cout << "Using default image2" << std::endl;
        image2 = cv::Mat::zeros(default_size, CV_8UC3);
        // draw a red cross
        centered_rectangle(image2, 96, 512, cv::Scalar(0, 77, 222));
        centered_rectangle(image2, 548, 128, cv::Scalar(0, 77, 222));
        // draw cross mask
        mask2 = cv::Mat::zeros(image2.size(), CV_8UC1);
        centered_rectangle(mask2, 96, 512, cv::Scalar(255, 255, 255));
        centered_rectangle(mask2, 548, 128, cv::Scalar(255, 255, 255));
        mask2 /= 255;

    } else {
        // open image, grayscale = true
        image2 = open_image(imageFile2.c_str(), false);
        cv::resize(image2, image2, default_size);
    }

    std::cout << "\nShortcuts:\n\tq\t- quit\n";

    // display the original images
    cv::imshow(WINDOW_NAME + "_1", image1);
    cv::imshow(WINDOW_NAME + "_2", image2);

    while (wait_key());

    do_porter_duff_ops(image1, image2, mask1, mask2);

    // 'event loop' for keypresses
    while (wait_key());

    image1.release();
    image2.release();

    return 0;
}
