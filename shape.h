#include <QObject>
#include <QPoint>
using namespace std;
#ifndef SHAPE_H
#define SHAPE_H

#endif // SHAPE_H

class Shape
{

private:
    vector<QPoint> *points;
    string shapename;
public:
    Shape();
    void addPoint(QPoint point);
    void changeShape(string name);
    void getShape();
    ~Shape();
};
