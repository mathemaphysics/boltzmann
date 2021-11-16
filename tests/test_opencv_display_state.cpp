#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/plot.hpp>
#include <boost/filesystem.hpp>
#include "boltzmann/boltzmann_config.hpp"
#include "gtest/gtest.h"

/**
 * @brief Tests display of a basic layer state via OpenCV
 * @test
 *  - Take the top layer of an RBM
 *  - Plots it as an image to the screen
 */

#define CV_IMAGE_TYPESIZE CV_8U
typedef cv::uint8_t image_t;

int main(int argc, char **argv)
{
    try
    {
        cv::Mat image;
        image.create(100, 100, CV_IMAGE_TYPESIZE);
        image.forEach<image_t>(
            [](image_t &pnt, const int *pos) -> void
            {
                pnt = (image_t) (rand() % 255);
            }
        );
        cv::imwrite("test_opencv_display_state_output01.png", image, {cv::IMWRITE_PNG_COMPRESSION, 9});
        boost::filesystem::path outPath("test_opencv_display_state_output01.png");
        if (boost::filesystem::exists(outPath))
        {
            std::cout << "Test succeeded" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Test failed" << std::endl;
            return 1;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 2; // Some other unknown exception
    }
    
    return 0;
}