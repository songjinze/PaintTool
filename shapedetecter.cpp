#include <opencv2\opencv.hpp>
#include <vector>
#include <iostream>
#include "shapedetecter.h"
using namespace std;
using namespace cv;

/////////////////////////////////////////////////////////////////////////////////////////////
// Thinning algorithm from here:
// https://github.com/bsdnoobz/zhang-suen-thinning
/////////////////////////////////////////////////////////////////////////////////////////////

void ShapeDetecter::thinningIteration(cv::Mat& img, int iter)
{
    CV_Assert(img.channels() == 1);
    CV_Assert(img.depth() != sizeof(uchar));
    CV_Assert(img.rows > 3 && img.cols > 3);

    cv::Mat marker = cv::Mat::zeros(img.size(), CV_8UC1);

    int nRows = img.rows;
    int nCols = img.cols;

    if (img.isContinuous()) {
        nCols *= nRows;
        nRows = 1;
    }

    int x, y;
    uchar *pAbove;
    uchar *pCurr;
    uchar *pBelow;
    uchar *nw, *no, *ne;    // north (pAbove)
    uchar *we, *me, *ea;
    uchar *sw, *so, *se;    // south (pBelow)

    uchar *pDst;

    // initialize row pointers
    pAbove = NULL;
    pCurr = img.ptr<uchar>(0);
    pBelow = img.ptr<uchar>(1);

    for (y = 1; y < img.rows - 1; ++y) {
        // shift the rows up by one
        pAbove = pCurr;
        pCurr = pBelow;
        pBelow = img.ptr<uchar>(y + 1);

        pDst = marker.ptr<uchar>(y);

        // initialize col pointers
        no = &(pAbove[0]);
        ne = &(pAbove[1]);
        me = &(pCurr[0]);
        ea = &(pCurr[1]);
        so = &(pBelow[0]);
        se = &(pBelow[1]);

        for (x = 1; x < img.cols - 1; ++x) {
            // shift col pointers left by one (scan left to right)
            nw = no;
            no = ne;
            ne = &(pAbove[x + 1]);
            we = me;
            me = ea;
            ea = &(pCurr[x + 1]);
            sw = so;
            so = se;
            se = &(pBelow[x + 1]);

            int A = (*no == 0 && *ne == 1) + (*ne == 0 && *ea == 1) +
                (*ea == 0 && *se == 1) + (*se == 0 && *so == 1) +
                (*so == 0 && *sw == 1) + (*sw == 0 && *we == 1) +
                (*we == 0 && *nw == 1) + (*nw == 0 && *no == 1);
            int B = *no + *ne + *ea + *se + *so + *sw + *we + *nw;
            int m1 = iter == 0 ? (*no * *ea * *so) : (*no * *ea * *we);
            int m2 = iter == 0 ? (*ea * *so * *we) : (*no * *so * *we);

            if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
                pDst[x] = 1;
        }
    }

    img &= ~marker;
}

void ShapeDetecter::thinning(const cv::Mat& src, cv::Mat& dst)
{
    dst = src.clone();
    dst /= 255;         // convert to binary image

    cv::Mat prev = cv::Mat::zeros(dst.size(), CV_8UC1);
    cv::Mat diff;

    do {
        thinningIteration(dst, 0);
        thinningIteration(dst, 1);
        cv::absdiff(dst, prev, diff);
        dst.copyTo(prev);
    } while (cv::countNonZero(diff) > 0);

    dst *= 255;
}


void ShapeDetecter::shapeDetect(string path_to_image,string save_path)
{
    RNG rng(123);

    // Read image
    Mat3b src = imread(path_to_image);

    // Convert to grayscale
    Mat1b gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // Binarize
    Mat1b bin;
    threshold(gray, bin, 127, 255, THRESH_BINARY_INV);

    // Perform thinning
    thinning(bin, bin);

    // Create result image
    Mat3b res = src.clone();

    // Find contours
    vector<vector<Point>> contours;
    findContours(bin.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    // For each contour
    for (vector<Point>& contour : contours)
    {
        // Compute convex hull
        vector<Point> hull;
        convexHull(contour, hull);

        // Compute circularity, used for shape classification
        double area = contourArea(hull);
        double perimeter = arcLength(hull, true);
        double circularity = (4 * CV_PI * area) / (perimeter * perimeter);

        // Shape classification

        if (circularity > 0.9)
        {
            // CIRCLE

            {
              // Fit an ellipse ...
              RotatedRect rect = fitEllipse(contour);
              Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
              ellipse(res, rect, color, 5);
            }
//            {
//                // ... or find min enclosing circle
//                Point2f center;
//                float radius;
//                minEnclosingCircle(contour, center, radius);
//                Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//                circle(res, center, radius, color, 5);
//            }
        }
        else if (circularity > 0.75)
        {
            // RECTANGLE

            {
              // Minimum oriented bounding box ...
              RotatedRect rect = minAreaRect(contour);
              Point2f pts[4];
              rect.points(pts);

              Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
              for (int i = 0; i < 4; ++i)
              {
                  line(res, pts[i], pts[(i + 1) % 4], color, 5);
              }
            }
//            {
//                // ... or bounding box
//                Rect box = boundingRect(contour);
//                Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//                rectangle(res, box, color, 5);
//            }
        }
        else if (circularity > 0.5)
        {
            // TRIANGLE

            // Select the portion of the image containing only the wanted contour
            Rect roi = boundingRect(contour);
            Mat1b maskRoi(bin.rows, bin.cols, uchar(0));
            rectangle(maskRoi, roi, Scalar(255), CV_FILLED);
            Mat1b triangle(roi.height, roi.height, uchar(0));
            bin.copyTo(triangle, maskRoi);

            // Find min encolsing circle on the contour
            Point2f center;
            float radius;
            minEnclosingCircle(contour, center, radius);

            // decrease the size of the enclosing circle until it intersects the contour
            // in at least 3 different points (i.e. the 3 vertices)
            vector<vector<Point>> vertices;
            do
            {
                vertices.clear();
                radius--;

                Mat1b maskCirc(bin.rows, bin.cols, uchar(0));
                circle(maskCirc, center, radius, Scalar(255), 5);

                maskCirc &= triangle;
                findContours(maskCirc.clone(), vertices, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

            } while (vertices.size() < 3);

            // Just get the first point in each vertex blob.
            // You could get the centroid for a little better accuracy

            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            line(res, vertices[0][0], vertices[1][0], color, 5);
            line(res, vertices[1][0], vertices[2][0], color, 5);
            line(res, vertices[2][0], vertices[0][0], color, 5);

        }
        else
        {
            cout << "Some other shape..." << endl;
        }

    }
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    try {
        imwrite(save_path, res, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
        return;
    }
    fprintf(stdout, "Saved PNG file with alpha data.\n");
    return;
}
