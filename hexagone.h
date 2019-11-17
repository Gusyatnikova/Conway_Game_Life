#ifndef HEXAGONE_H
#define HEXAGONE_H

#include <QDebug>
#include <math.h>
#include "point.h"

class Hexagone
{
public:
    Hexagone();
    Hexagone(int, int, int, bool);
    int getCoordX();
    int getCoordY();
    bool getIsAlive();
    int getA();
    int getB();
    void setCellSize(int);
    void setH(double);
    void setR(double);
    void setA(double);
    void setB(double);
    void setIsAlive(bool);
    unsigned char* aliveColor;
    unsigned char* ripColor;
    Point getCenter();
    Point** getCoords();

    //WARNING caclH ret float?


private:
    int xCoord;
    int yCoord;
    Point *pointsArray[6];
    Point center;
    int borderSize;
    double h;
    double r;
    double a;
    double b;
    int cellSize;
//r=a*sqrt(3)/2
    bool isAlive;
    void calculateVertices();

};

#endif // HEXAGONE_H
