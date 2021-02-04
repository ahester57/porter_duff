// porter_duff_ops.cpp : porter-duff operators
// Austin Hester CS642o feb 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>

#include "./include/porter_duff_ops.hpp"


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
cv::Mat
i1_over_i2(cv::Mat img1, cv::Mat img2)
{
    return cv::Mat();
}

// Ir = I1
// Mr = M1 ∧ M2
cv::Mat
i1_in_i2(cv::Mat img1, cv::Mat img2)
{
    return cv::Mat();
}

// Ir = I1
// Mr = M1 ∧ ¬M2
cv::Mat
i1_out_i2(cv::Mat img1, cv::Mat img2)
{
    return cv::Mat();
}

// Ir = (I1 ∧ M1) ∨ (I2 ∧ ¬M2)
// Mr = M2
cv::Mat
i1_atop_i2(cv::Mat img1, cv::Mat img2)
{
    return cv::Mat();
}

// Ir = (I1 ∧ M1 ∧ ¬M2) ∨ (I2 ∧ ¬M1 ∧ M2)
// Mr = (M1 ∧ ¬M2) ∨ (¬M1 ∧ M2)
cv::Mat
i1_xor_i2(cv::Mat img1, cv::Mat img2)
{
    return cv::Mat();
}