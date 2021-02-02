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
#include "./include/img_struct.hpp"


const std::string WINDOW_NAME = "Porter-Duff";

// CLA variables
std::string image1;
std::string image2;
std::string mask1;
std::string mask2;
bool grayscale;

img_struct_t* og_image;
cv::Mat displayed_image;


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


// save the ROI to a cv::Mat
cv::Mat
extract_roi(cv::Mat src, cv::Rect rect)
{
    cv::Mat dst;
    src(rect).copyTo(dst);
    return dst;
}


int
main(int argc, const char** argv)
{
    // parse and save command line args
    int parse_result = parse_arguments(
        argc, argv,
        &image1,
        &image2,
        &mask1,
        &mask2,
        &grayscale
    );
    if (parse_result != 1) return parse_result;

    if (image1.size() == 0) {
        std::cout << "Using default image1" << std::endl;
    }

    if (image2.size() == 0) {
        std::cout << "Using default image2" << std::endl;
    }

    // open image, grayscale = true
    og_image = open_image(image1.c_str(), grayscale);

    assert(og_image != NULL);

    // deep keep to displayed_image
    og_image->image.copyTo(displayed_image);

    std::cout << "\nShortcuts:\n\tq\t- quit\n";

    // display the original image
    cv::imshow(WINDOW_NAME, displayed_image);

    // 'event loop' for keypresses
    while (wait_key());

    og_image->image.release();
    delete og_image;

    displayed_image.release();

    return 0;
}
