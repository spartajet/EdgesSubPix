#ifndef __EDGES_SUBPIX_H__
#define __EDGES_SUBPIX_H__
#include <opencv2/opencv.hpp>
#include <vector>

// #ifndef SUB_EDGE_EXPORT
// # define SUB_EDGE_EXPORT
// #endif

// #ifdef SUB_EDGE_EXPORT
# if defined _WIN32 || defined WINCE || defined __CYGWIN__
#   define SUB_EDGE_EXPORT __declspec(dllexport)
# elif defined __GNUC__ && __GNUC__ >= 4
#   define SUB_EDGE_EXPORT __attribute__ ((visibility ("default")))
# endif
// #endif

struct Contour
{
    std::vector<cv::Point2f> points;
    std::vector<float> direction;
    std::vector<float> response;
};

struct PointResult
{
    const float* xs;
    const float* ys;
    int length;
};

// only 8-bit
void EdgesSubPix(cv::Mat& gray, double alpha, int low, int high,
                 std::vector<Contour>& contours, cv::OutputArray hierarchy,
                 int mode);

extern "C" SUB_EDGE_EXPORT std::vector<Contour> EdgesSubPix(cv::Mat& gray, double alpha, int low, int high);
extern "C" SUB_EDGE_EXPORT PointResult EdgesSubPixPoints(void* data, int width, int height, double alpha, int low, int high, int thread_length, int capacity);

extern "C" SUB_EDGE_EXPORT void freePointResult(PointResult* result);

#endif // __EDGES_SUBPIX_H__
