#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "hexagone.h"
#include <QtMath>
#include <math.h>

class GameField
{
public:
    GameField();
    ~GameField();
    GameField(int, int, int);
    Hexagone* getHexagone(int, int);
    Hexagone* findByCoord(int, int);
    static double calculateH(int);
    static double calculateR(int);
    static double degreeToRadian(double);
    Point getHexIndexByCoords(int, int);
    int getN();
    int getM();
    bool isExist(int, int);
    int calculateAll();
    bool getImpactMode() const;
    void setImpactMode(bool value);
    QString getActiveCells();
    void setConfiguration(QString);
    double getA() const;
    double getB() const;

private:
    int N;
    int M;
    int cellWidth;
    int cellHeight;
    int cellSize;
    bool impactMode;
    double a;
    double b;
    QString activeCells;
    Hexagone*** vertexes;

};

#endif // GAMEFIELD_H
