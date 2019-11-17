#include "hexagone.h"

Hexagone::Hexagone()
{

}

Hexagone::Hexagone(int x, int y, int cellSize, bool isAlive)
{
    this->xCoord = x;
    this->yCoord = y;
    this->cellSize = cellSize;
    this->isAlive = isAlive;
    this->aliveColor = new unsigned char[4]{153, 255, 204, 255};
    this->ripColor = new unsigned char[4]{204, 229, 255, 255};
}

int Hexagone::getCoordX()
{
    return this->xCoord;
}

int Hexagone::getCoordY()
{
    return this->yCoord;
}

bool Hexagone::getIsAlive()
{
    return this->isAlive;
}

void Hexagone::setCellSize(int cellSize)
{
    this->cellSize = cellSize;
}

void Hexagone::setH(double h)
{
    this->h = h;
}

void Hexagone::setR(double r)
{
    this->r = r;
}

void Hexagone::setA(double a)
{
    this->a = a;
}

void Hexagone::setB(double b)
{
    this->b = b;
    calculateVertices();
}

void Hexagone::setIsAlive(bool isAlive)
{
    this->isAlive = isAlive;
}

Point Hexagone::getCenter()
{
    return this->center;
}

int Hexagone::getA()
{
    return a;
}

int Hexagone::getB()
{
    return b;
}

Point** Hexagone::getCoords()
{
    return this->pointsArray;
}

void Hexagone::calculateVertices()
{
    int x = this->xCoord;
    int y = this->yCoord;

    this->pointsArray[0] = new Point(x, y);
    //qDebug() << "start Vert: " << "x " << x << "y " << y;

    this->pointsArray[1] = new Point(x, y + cellSize);
    this->pointsArray[2] = new Point(x + r, y + cellSize + h);
    this->center.setXY(x + a/2, round(y + cellSize + h - b/2));
    this->pointsArray[3] = new Point(x + 2*r, y + cellSize);
    this->pointsArray[4] = new Point(x + 2*r, y);
    this->pointsArray[5] = new Point(x + r, y - h);
}
