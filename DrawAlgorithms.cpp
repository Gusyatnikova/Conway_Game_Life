#include "DrawAlgorithms.h"

DrawAlgorithms::DrawAlgorithms(GameModel* gameModel)
{
    this->gameModel = gameModel;
}

void DrawAlgorithms::drawLine(QImage* image, int x1,int y1,int x2,int y2){
    unsigned char* color = new uchar[4]{0, 0, 0, 255};

    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;

    int error = deltaX - deltaY;

    setPixel(image, x2, y2, color);


    while(x1 != x2 || y1 != y2) {
        setPixel(image, x1, y1, color);
        //qDebug() << "I set pixel: (x, y): " << x1 << y1;


        const int error2 = error * 2;

        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }


}

void DrawAlgorithms::setPixel(QImage* image, int x, int y, unsigned char* qolor)
{
    unsigned char* line = &image->bits()[image->bytesPerLine() * y];
    line[x * 4 + 0] = qolor[0]; //blue
    line[x * 4 + 1] = qolor[1]; //green
    line[x * 4 + 2] = qolor[2]; // red
    line[x * 4 + 3] = qolor[3];
}


void DrawAlgorithms::drawHexagone(QImage * image, Hexagone * curHex)
{
    Point** vertices = curHex->getCoords();
    for(int i = 0; i < 5; i++) {
        int x0 = vertices[i]->getX();
        int y0 = vertices[i]->getY();
        int x1 = vertices[i+1]->getX();
        int y1 = vertices[i+1]->getY();

        drawLine(image, x0, y0, x1, y1);
        if(4 == i)
        {
            drawLine(image, x1, y1, vertices[0]->getX(), vertices[0]->getY());
        }
    }
    Point * seed = new Point(vertices[0][0].getX() + 1, vertices[0][0].getY());
    //uchar* upColor = new uchar[4] {255, 0, 0, 255};
    //uchar* downColor = new uchar[4] {0, 255, 0, 255};
    //setPixel(image, vertices[2]->getX(), vertices[2]->getY(), upColor);
    //setPixel(image, vertices[5]->getX(), vertices[5]->getY(), downColor);
    if(curHex->getIsAlive() == false){
        fillSpan(image, seed, curHex->ripColor);
    } else {
        fillSpan(image, seed, curHex->aliveColor);
    }
}

void DrawAlgorithms::drawGameField(QImage * image, GameField* gameField)
{
    //BUG: когда cs < 15 и нечетное сбивается заливка
    setWhiteBackground(image);
    int N = gameField->getN();
    int M = gameField->getM();
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if (i%2 == 1 && j == M - 1) break;
            //qDebug() << i << j << gameField->getHexagone(i, j)->getIsAlive();
            drawHexagone(image, gameField->getHexagone(i, j));
        }
    }
    //  if(gameField->getImpactMode() == true) drawImpacts(image, gameField);

}

void DrawAlgorithms::setWhiteBackground(QImage * image)
{
    memset(image->bits(), 255, image->byteCount());
}

unsigned char *DrawAlgorithms::checkColor(QImage * image, int x, int y)
{
    unsigned char* color = new unsigned char[4]{};
    unsigned char * line = &image->bits()[y * image->bytesPerLine()];
    color[0] = line[x * 4 + 0];
    color[1] = line[x * 4 + 1];
    color[2] = line[x * 4 + 2];
    color[3] = line[x * 4 + 3];
    return color;
}

void DrawAlgorithms::clearField(QImage* image, GameField* gameField)
{
    unsigned char* ripColor = gameField->getHexagone(0, 0)->ripColor;
    int N = gameField->getN();
    int M = gameField->getM();
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if (i%2 == 1 && j == M - 1) break;
            gameField->getHexagone(i, j)->setIsAlive(false);
            int x = gameField->getHexagone(i, j)->getCoordX();
            int y = gameField->getHexagone(i, j)->getCoordY();
            fillSpan(image, new Point(x + 1, y), ripColor);
        }
    }
}

void DrawAlgorithms::fillSpan(QImage * image, Point * seed, unsigned char* aimColor)
{
    int x = seed->getX();
    int y = seed->getY();

    unsigned char* curColor = new unsigned char[4]{};
    unsigned char* oldColor = new unsigned char[4]{};
    std::deque<Point> coordStack;
    curColor = checkColor(image, x, y);
    oldColor = checkColor(image, x, y);
    int w = image->width();
    int h = image->height();
    if(isEqualColor(oldColor, aimColor)) return;

    int x1;
    bool spanAbove, spanBelow;

    coordStack.push_front(Point(x, y, curColor));
    while(!coordStack.empty()) {
        auto point = coordStack.front();
        x = point.getX();
        y = point.getY();
        coordStack.pop_front();
        x1 = x;
        while(x1 >=0 && isEqualColor(checkColor(image, x1, y), oldColor)) x1--;
        x1++;
        spanAbove = 0;
        spanBelow = 0;
        while(x1 < w && isEqualColor(checkColor(image, x1, y), oldColor)) {
            setPixel(image, x1, y, aimColor);
            if(!spanAbove && y > 0 && isEqualColor(checkColor(image, x1, y-1), oldColor)) {
                coordStack.push_front(Point(x1, y-1, aimColor));
                spanAbove = 1;
            } else if(spanAbove && y > 0 && isEqualColor(checkColor(image, x1, y - 1), oldColor)) {
                spanAbove = 0;
            }
            if(!spanBelow && y < h - 1 && isEqualColor(checkColor(image, x1, y + 1), oldColor)) {
                coordStack.push_front(Point(x1, y + 1, aimColor));
                spanBelow = 1;
            } else if(spanBelow && y < h - 1 && isEqualColor(checkColor(image, x1, y + 1), oldColor)){
                spanBelow = 0;
            }
            x1++;
        }
    }
}

bool DrawAlgorithms::isEqualColor(unsigned char * source, unsigned char * aim)
{
    return source[0] == aim[0] && source[1] == aim[1] && source[2] == aim[2] && source[3] == aim[3];
}



