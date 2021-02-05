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
    // cv::Vec3b not_mask2;
    // cv::bitwise_not(mask2, not_mask2);
    // cv::Vec3b Mr;
    // cv::bitwise_and(mask1, not_mask2, Mr);
    // cv::Vec3b result;
    // cv::bitwise_and(pixel1, Mr, result);
    // return result;
    return (pixel2 == ZERO_PIXEL) ? pixel1 : ZERO_PIXEL;
}

// Ir = (I1 ∧ M1) ∨ (I2 ∧ ¬M2)
// Mr = M2
cv::Vec3b
i1_atop_i2(cv::Vec3b pixel1, cv::Vec3b pixel2, cv::Vec3b mask1, cv::Vec3b mask2)
{
    // cv::Vec3b t0, t1, t2, Ir;
    // cv::bitwise_and(pixel1, mask1, t0);
    // cv::bitwise_not(mask2, t1);
    // cv::bitwise_and(pixel2, t1, t2);
    // cv::bitwise_or(t0, t2, Ir);
    // cv::Vec3b result;
    // cv::bitwise_and(Ir, mask2, result);
    // return result;
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

// Ir = (I1 ∧ M1) ∨ (I2 ∧ ¬M2)
// Mr = M2
cv::Mat
test_i1_atop_i2(cv::Mat img1, cv::Mat img2, cv::Mat mask1, cv::Mat mask2)
{
    // cv::Vec3b t0, t1, t2, Ir;
    // cv::bitwise_and(pixel1, mask1, t0);
    // cv::bitwise_not(mask2, t1);
    // cv::bitwise_and(pixel2, t1, t2);
    // cv::bitwise_or(t0, t2, Ir);
    // cv::Vec3b result;
    // cv::bitwise_and(Ir, mask2, result);
    cv::Mat i1, i2;
    cv::Mat m1, m2;

    mask1.convertTo(m1, CV_8UC1);
    mask2.convertTo(m2, CV_8UC1);
    m1 /= 255;
    m2 /= 255;
    img1.copyTo(i1, m1);
    img2.copyTo(i2, ~m2);
    cv::Mat Ir = i1 | i2;
    cv::Mat result;
    Ir.copyTo(result, m2);
    return result;
}
