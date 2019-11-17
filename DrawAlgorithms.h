#ifndef DRAWALGHORITMS_H
#define DRAWALGHORITMS_H
#include "gamemodel.h"
#include "hexagone.h"
#include <iostream>
#include <deque>
#include <vector>
#include <QImage>
#include "gamefield.h"

class DrawAlgorithms
{
public:
    DrawAlgorithms(GameModel* gameModel);
    void drawLine(QImage*, int,int,int,int);
    void setPixel(QImage*, int, int, uchar*);
    void drawHexagone(QImage*, Hexagone*);
    void drawGameField(QImage*, GameField*);
    void setWhiteBackground(QImage*);
    void fillSpan(QImage*, Point*, uchar*);
    bool isEqualColor(uchar*, uchar*);
    unsigned char* checkColor(QImage*, int, int);
    void clearField(QImage*, GameField*);

private:
    GameModel* gameModel;
    void drawImpacts(QImage*, GameField*);
};

#endif // DRAWALGHORITMS_H
