// porter_duff.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Austin Hester CS542o dec 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>
#include <iostream>

#include "./include/bitwise_porter_duff_ops.hpp"
#include "./include/cla_parse.hpp"
#include "./include/pd_initializer.hpp"
#include "./include/porter_duff_ops.hpp"


const std::string WINDOW_NAME = "Porter-Duff";


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

// do pixel-wise operations
void
do_porter_duff_ops(cv::Mat image1, cv::Mat image2, cv::Mat mask1, cv::Mat mask2)
{
    cv::imshow("clear_1", clear_i1(image1));
    cv::imshow("clear_2", clear_i1(image2));

    while (wait_key());

    cv::imshow("copy_1", copy_i1(image1));
    cv::imshow("copy_2", copy_i1(image2));

    while (wait_key());

    cv::imshow("1_over_2", do_porter_operation(i1_over_i2, image1, image2, mask1, mask2));
    cv::imshow("2_over_1", do_porter_operation(i1_over_i2, image2, image1, mask2, mask1));

    while (wait_key());

    cv::imshow("1_in_2", do_porter_operation(i1_in_i2, image1, image2, mask1, mask2));
    cv::imshow("2_in_1", do_porter_operation(i1_in_i2, image2, image1, mask2, mask1));

    while (wait_key());

    cv::imshow("1_out_2", do_porter_operation(i1_out_i2, image1, image2, mask1, mask2));
    cv::imshow("2_out_1", do_porter_operation(i1_out_i2, image2, image1, mask2, mask1));

    while (wait_key());

    cv::imshow("1_atop_2", do_porter_operation(i1_atop_i2, image1, image2, mask1, mask2));
    cv::imshow("2_atop_1", do_porter_operation(i1_atop_i2, image2, image1, mask2, mask1));

    while (wait_key());

    cv::imshow("1_xor_2", do_porter_operation(i1_xor_i2, image1, image2, mask1, mask2));
    cv::imshow("2_xor_1", do_porter_operation(i1_xor_i2, image2, image1, mask2, mask1));
}

// do bitwise operations on whole image
void
do_bitwise_porter_duff_ops(cv::Mat image1, cv::Mat image2, cv::Mat mask1, cv::Mat mask2)
{
    cv::imshow("bitwise_clear_1", bitwise_clear_i1(image1, mask1));
    cv::imshow("bitwise_clear_2", bitwise_clear_i1(image2, mask2));

    while (wait_key());

    cv::imshow("bitwise_copy_1", bitwise_copy_i1(image1, mask1));
    cv::imshow("bitwise_copy_2", bitwise_copy_i1(image2, mask2));

    while (wait_key());

    cv::imshow("bitwise_1_over_2", bitwise_i1_over_i2(image1, image2, mask1, mask2));
    cv::imshow("bitwise_2_over_1", bitwise_i1_over_i2(image2, image1, mask2, mask1));

    while (wait_key());

    cv::imshow("bitwise_1_in_2", bitwise_i1_in_i2(image1, image2, mask1, mask2));
    cv::imshow("bitwise_2_in_1", bitwise_i1_in_i2(image2, image1, mask2, mask1));

    while (wait_key());

    cv::imshow("bitwise_1_out_2", bitwise_i1_out_i2(image1, image2, mask1, mask2));
    cv::imshow("bitwise_2_out_1", bitwise_i1_out_i2(image2, image1, mask2, mask1));

    while (wait_key());

    cv::imshow("bitwise_1_atop_2", bitwise_i1_atop_i2(image1, image2, mask1, mask2));
    cv::imshow("bitwise_2_atop_1", bitwise_i1_atop_i2(image2, image1, mask2, mask1));

    while (wait_key());

    cv::imshow("bitwise_1_xor_2", bitwise_i1_xor_i2(image1, image2, mask1, mask2));
    cv::imshow("bitwise_2_xor_1", bitwise_i1_xor_i2(image2, image1, mask2, mask1));
}


int
main(int argc, const char** argv)
{
    // CLA variables
    std::string imageFile1;
    std::string imageFile2;
    std::string maskFile1;
    std::string maskFile2;
    bool pixel;

    // parse and save command line args
    int parse_result = parse_arguments(
        argc, argv,
        &imageFile1,
        &imageFile2,
        &maskFile1,
        &maskFile2,
        &pixel
    );
    if (parse_result != 1) return parse_result;

    cv::Mat image1;
    cv::Mat mask1;

    open_or_create_image_1(imageFile1, &image1, &mask1);

    cv::Mat image2;
    cv::Mat mask2;

    open_or_create_image_2(imageFile2, &image2, &mask2);

    std::cout << "\nShortcuts:\n\tq\t- quit\n";

    // display the original images
    cv::imshow(WINDOW_NAME + "_1", image1);
    cv::imshow(WINDOW_NAME + "_2", image2);

    while (wait_key());

    if (pixel) {
        do_porter_duff_ops(image1, image2, mask1, mask2);
    } else {
        do_bitwise_porter_duff_ops(image1, image2, mask1, mask2);
    }

    // 'event loop' for keypresses
    while (wait_key());

    image1.release();
    image2.release();

    return 0;
}
