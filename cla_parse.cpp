// cla_parse.cpp : Parse given command line arguments.
// Austin Hester CS542o nov 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>

#include "./include/cla_parse.hpp"

// parse command line arguments
int
parse_arguments(
    int argc,
    const char** argv,
    std::string* image1,
    std::string* image2,
    std::string* mask1,
    std::string* mask2
) {
    cv::String keys =
        "{image1 i1  |<none>| input image}"             // image1 (optional)
        "{image2 i2  |<none>| input image}"             // image2 (optional)
        "{mask1  m1  |<none>| input image}"             // mask1  (optional)
        "{mask2  m2  |<none>| input image}"             // mask2  (optional)
        "{help h   |      | show help message}";

    cv::CommandLineParser parser(argc, argv, keys);

    if (parser.has("h")) {
        parser.printMessage();
        return 0;
    }

    if (!parser.check()) {
        parser.printErrors();
        parser.printMessage();
        return -1;
    }

    try {
        *image1 = (std::string) parser.get<std::string>("i1").c_str();
    } catch (...) {
        std::cerr << "Failed to parse image1 argument!:" << std::endl;
        return -1;
    }

    try {
        *image2 = (std::string) parser.get<std::string>("i2").c_str();
    } catch (...) {
        std::cerr << "Failed to parse image2 argument!:" << std::endl;
        return -1;
    }

    try {
        *mask1 = (std::string) parser.get<std::string>("m1").c_str();
    } catch (...) {
        std::cerr << "Failed to parse mask1 argument!:" << std::endl;
        return -1;
    }

    try {
        *mask2 = (std::string) parser.get<std::string>("m2").c_str();
    } catch (...) {
        std::cerr << "Failed to parse mask2 argument!:" << std::endl;
        return -1;
    }

    return 1;
}
