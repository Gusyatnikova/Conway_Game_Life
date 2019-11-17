#ifndef POINT_H
#define POINT_H
#include <iostream>

class Point
{
public:
    Point();
    Point(int, int, unsigned char*);
    Point(int, int);
    void setColor(unsigned char*);
    unsigned char* getColor();
    int getX();
    int getY();
    void setXY(int, int);
    bool operator<(const Point& point);
private:
    int x;
    int y;
    unsigned char* color;
};

#endif // POINT_H
