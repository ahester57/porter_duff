// porter_duff_ops.cpp : porter-duff operators
// Austin Hester CS642o feb 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>

#include "./include/porter_duff_ops.hpp"


const cv::Vec3b ZERO_PIXEL = cv::Vec3b(0, 0, 0);

// Ir = 0
// Mr = 0
cv::Mat
clear_i1(cv::Mat src)
{
    return cv::Mat::zeros(src.size(), src.type());
}

// Ir = I1
// Mr = M1
cv::Mat
copy_i1(cv::Mat src)
{
    cv::Mat dst;
    src.copyTo(dst);
    return dst;
}

// Ir = (I1 ∧ M1) ∨ (I2 ∧ M2 ∧ ¬M1)
// Mr = M1 ∨ M2
cv::Vec3b
i1_over_i2(cv::Vec3b pixel1, cv::Vec3b pixel2, cv::Vec3b mask1, cv::Vec3b mask2)
{
    return (pixel1 == ZERO_PIXEL) ? pixel2 : pixel1;
}

// Ir = I1
// Mr = M1 ∧ M2
cv::Vec3b
i1_in_i2(cv::Vec3b pixel1, cv::Vec3b pixel2, cv::Vec3b mask1, cv::Vec3b mask2)
{
    return (pixel2 != ZERO_PIXEL) ? pixel1 : ZERO_PIXEL;
}

// Ir = I1
// Mr = M1 ∧ ¬M2
cv::Vec3b
i1_out_i2(cv::Vec3b pixel1, cv::Vec3b pixel2, cv::Vec3b mask1, cv::Vec3b mask2)
{
    return (pixel2 == ZERO_PIXEL) ? pixel1 : ZERO_PIXEL;
}

// Ir = (I1 ∧ M1) ∨ (I2 ∧ ¬M2)
// Mr = M2
cv::Vec3b
i1_atop_i2(cv::Vec3b pixel1, cv::Vec3b pixel2, cv::Vec3b mask1, cv::Vec3b mask2)
{
    return (pixel1 != ZERO_PIXEL && pixel2 != ZERO_PIXEL) ? pixel1 :  pixel2;
}

// Ir = (I1 ∧ M1 ∧ ¬M2) ∨ (I2 ∧ ¬M1 ∧ M2)
// Mr = (M1 ∧ ¬M2) ∨ (¬M1 ∧ M2)
cv::Vec3b
i1_xor_i2(cv::Vec3b pixel1, cv::Vec3b pixel2, cv::Vec3b mask1, cv::Vec3b mask2)
{
    return (pixel1 != ZERO_PIXEL && pixel2 == ZERO_PIXEL) ? pixel1
            : (pixel1 == ZERO_PIXEL && pixel2 != ZERO_PIXEL) ? pixel2
            : ZERO_PIXEL;
}

// do given operation on given images
cv::Mat
do_porter_operation(
    cv::Vec3b operation(cv::Vec3b, cv::Vec3b, cv::Vec3b, cv::Vec3b),
    cv::Mat img1, cv::Mat img2,
    cv::Mat mask1, cv::Mat mask2
) {
    assert(img1.size() == img2.size());
    assert(img1.type() == img2.type());
    cv::Mat result = cv::Mat::zeros(img1.size(), img1.type());
    for (int r = 0; r < result.rows; r++) {
        for (int c = 0; c < result.cols; c++) {
            // do pixel operation
            result.at<cv::Vec3b>(r, c)
                = operation(
                    img1.at<cv::Vec3b>(r, c),
                    img2.at<cv::Vec3b>(r, c),
                    mask1.at<cv::Vec3b>(r, c),
                    mask2.at<cv::Vec3b>(r, c)
                );
        }
    }
    return result;
}
