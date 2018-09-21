#ifndef PICTURE_H
#define PICTURE_H

#endif // PICTURE_H
using namespace std;
#include "shape.h"
class Picture{
private:
    vector<Shape> *shapes;
public:
    Picture();
    ~Picture();
    void addShape(Shape shape);
    void savePicture();
    void loadPicture();
};
