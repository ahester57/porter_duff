// porter_duff_operators.hpp : porter-duff operators
// Austin Hester CS642o feb 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef PORTER_DUFF_OPS_H
#define PORTER_DUFF_OPS_H

#include <opencv2/core/core.hpp>

// Ir = 0
// Mr = 0
cv::Mat clear_i1(cv::Mat src);

// Ir = I1
// Mr = M1
cv::Mat copy_i1(cv::Mat src);

// Ir = (I1 ∧ M1) ∨ (I2 ∧ M2 ∧ ¬M1)
// Mr = M1 ∨ M2
cv::Vec3b i1_over_i2(cv::Vec3b pixel1, cv::Vec3b pixel2, cv::Vec3b mask1, cv::Vec3b mask2);

// Ir = I1
// Mr = M1 ∧ M2
cv::Vec3b i1_in_i2(cv::Vec3b pixel1, cv::Vec3b pixel2, cv::Vec3b mask1, cv::Vec3b mask2);

// Ir = I1
// Mr = M1 ∧ ¬M2
cv::Vec3b i1_out_i2(cv::Vec3b pixel1, cv::Vec3b pixel2, cv::Vec3b mask1, cv::Vec3b mask2);

// Ir = (I1 ∧ M1) ∨ (I2 ∧ ¬M2)
// Mr = M2
cv::Vec3b i1_atop_i2(cv::Vec3b pixel1, cv::Vec3b pixel2, cv::Vec3b mask1, cv::Vec3b mask2);
// Ir = (I1 ∧ M1 ∧ ¬M2) ∨ (I2 ∧ ¬M1 ∧ M2)
// Mr = (M1 ∧ ¬M2) ∨ (¬M1 ∧ M2)
cv::Vec3b i1_xor_i2(cv::Vec3b pixel1, cv::Vec3b pixel2, cv::Vec3b mask1, cv::Vec3b mask2);

cv::Mat do_porter_operation(
    cv::Vec3b operation(cv::Vec3b, cv::Vec3b, cv::Vec3b, cv::Vec3b),
    cv::Mat img1, cv::Mat img2,
    cv::Mat mask1, cv::Mat mask2
);

#endif
