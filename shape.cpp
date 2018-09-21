#include "shape.h"

Shape::Shape(){
    points=new vector<QPoint>;
    shapename="unknown";
}

void Shape::addPoint(QPoint point){
    points->push_back(point);
}

void Shape::changeShape(string name){
    shapename=name;
}

Shape::~Shape(){
    delete points;
    shapename="unknown";
}
