#include <opencv2/core/mat.hpp>

#ifndef SHAPEDETECTER_H
#define SHAPEDETECTER_H

#endif // SHAPEDETECTER_H
using namespace std;

class ShapeDetecter
{
private:
    void thinningIteration(cv::Mat&img,int iter);
    void thinning(const cv::Mat& src,cv::Mat& dst);
public:
    void shapeDetect(string path_to_img);
};
