#include "point.h"

Point::Point()
{

}

Point::Point(int x, int y, unsigned char* color)
{
    this->y = y;
    this->x = x;
    this->color = color;
}

Point::Point(int x, int y)
{
    this->y = y;
    this->x = x;
}

unsigned char *Point::getColor()
{
    return this->color;
}

void Point::setColor(unsigned char* color)
{
    this->color = color;
}

int Point::getX()
{
    return this->x;
}


int Point::getY()
{
    return this->y;
}

void Point::setXY(int x, int y)
{
    this->x = x;
    this->y = y;

}

bool Point::operator<(const Point& point) {
    return (this->getX() < point.x);
}
