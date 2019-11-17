#include "gamefield.h"

GameField::GameField()
{

}

GameField::~GameField()
{
    for(int i = 0; i < N; i++) {
        delete [] vertexes[i];
    }
    delete [] vertexes;
}

GameField::GameField(int N, int M, int cellSize)
{
    this->N = N;
    this->M = M;
    this->cellSize = cellSize;
    double h = round(calculateH(cellSize));
    double r = round(calculateR(cellSize));
    a = 2 * r;
    b = cellSize + 2*h;

    this->cellWidth = static_cast<int>(a);
    this->cellHeight = static_cast<int>(b);
    this->impactMode = false;
    this->vertexes = new Hexagone**[N];
    for(int i = 0; i < N; i++) {
        if(i%2 == 1) {
            vertexes[i] = new Hexagone*[M - 1];
            for(int j = 0; j < M - 1; j++) {
                vertexes[i][j] = new Hexagone(static_cast<int>(j*a) + r, static_cast<int>(b*i - h*(i-1)), this->cellSize, false);
                vertexes[i][j]->setIsAlive(false);
                vertexes[i][j]->setH(h);
                vertexes[i][j]->setR(r);
                vertexes[i][j]->setA(a);
                vertexes[i][j]->setB(b);
            }
        }
        vertexes[i] = new Hexagone*[M];
        for(int j = 0; j < M; j++) {
            if (0 == i) {
                vertexes[i][j] = new Hexagone(static_cast<int>(j*a), static_cast<int>(i*b) + h, this->cellSize, false);
            } else if (1 == i%2) {
                vertexes[i][j] = new Hexagone(static_cast<int>(j*a) + r, static_cast<int>(b*i - h*(i-1)), this->cellSize, false);
            } else if (0 == i%2) {
                vertexes[i][j] = new Hexagone(static_cast<int>(j*a), static_cast<int>(b*i - h*(i-1)), this->cellSize, false);
            }
            vertexes[i][j]->setIsAlive(false);
            vertexes[i][j]->setH(h);
            vertexes[i][j]->setR(r);
            vertexes[i][j]->setA(a);
            vertexes[i][j]->setB(b);
        }
    }
}

Hexagone* GameField::getHexagone(int i, int j)
{
    if(j < 0 || i < 0 || i >= N) return nullptr;
    if(i%2 == 0 && j >= M) return nullptr;
    if(i%2 == 1 && j >= M - 1) return nullptr;
    return vertexes[i][j];
}

Hexagone* GameField::findByCoord(int x, int y)
{
    //qDebug() << "press on:" << x << y;
    int centerCurHexX, centerCurHexY;
    int valueXY = INT_MAX;
    int curDistanse = 0;
    int nearestX;
    int nearestY;
    for(int str = 0; str < N; str++) {
        for(int col = 0; col < M; col++) {
            if (str%2 == 1 && col >= M - 1) break;
            centerCurHexX = getHexagone(str, col)->getCenter().getX();
            centerCurHexY = getHexagone(str, col)->getCenter().getY();
            curDistanse = sqrt(pow((x - centerCurHexX),2) + pow((y - centerCurHexY),2));
            if (valueXY >= curDistanse) {
                valueXY = curDistanse;
                nearestX = col;
                nearestY = str;
            }
        }
    }

    //qDebug() << "I found!! (i, j)" << nearestY << nearestX;
    return vertexes[nearestY][nearestX];
}

double GameField::calculateH(int cellSize)
{
    double a = qSin(degreeToRadian(30))*cellSize;
    return qSin(degreeToRadian(30))*cellSize;
}
double GameField::calculateR(int cellSize)
{
    int a = qCos(degreeToRadian(30))*cellSize;
    return qCos(degreeToRadian(30))*cellSize;
}
double GameField::degreeToRadian(double degrees)
{
    return degrees * M_PI / 180;
}

Point GameField::getHexIndexByCoords(int x, int y)
{
    int centerCurHexX, centerCurHexY;
    int valueXY = INT_MAX;
    int curDistanse = 0;
    int nearestX;
    int nearestY;
    for(int str = 0; str < N; str++) {
        for(int col = 0; col < M; col++) {
            if (str%2 == 1 && col >= M - 1) break;
            centerCurHexX = getHexagone(str, col)->getCenter().getX();
            centerCurHexY = getHexagone(str, col)->getCenter().getY();
            curDistanse = sqrt(pow((x - centerCurHexX),2) + pow((y - centerCurHexY),2));
            if (valueXY >= curDistanse) {
                valueXY = curDistanse;
                nearestX = col;
                nearestY = str;
            }
        }
    }

    //qDebug() << "I found!! (i, j)" << nearestY << nearestX;
    return Point(nearestY, nearestX, nullptr);
}

int GameField::getN()
{
    return N;
}

int GameField::getM()
{
    return M;
}

int GameField::calculateAll()
{
    int count = 0;
    for(int str = 0; str < N; str++) {
        for(int col = 0; col < M; col++) {
            if (str%2 == 1 && col >= M - 1) break;
            if(vertexes[str][col]->getIsAlive() == true) count++;
        }
    }
    return count;
}

bool GameField::getImpactMode() const
{
    return impactMode;
}

void GameField::setImpactMode(bool value)
{
    impactMode = value;
}

QString GameField::getActiveCells()
{
    QString result = "";
    for(int str = 0; str < this->N; str++) {
        for(int col = 0; col < this->M; col++) {
            if (str%2 == 1 && col >= this->M - 1) break;
            if(getHexagone(str, col)->getIsAlive() == true) {
                result = result + "" + QString::number(str) + " " + QString::number(col);
                result = result + ",";
                qDebug() << result;
            }
        }
    }
    return result;
}

void GameField::setConfiguration(QString config)
{
    QStringList pairs = config.split(",");
    if (config == "") return;
    for(int k = 0; k < pairs.length(); k++) {
        QStringList values = pairs[k].split(" ");
        if(values[0] == "" || values[1] == "") continue;
        int i = values[0].toInt();
        int j = values[1].toInt();
        if(i >= 0 && i < N) {
            if((i%2 == 1 && j > M - 2) || (i%2 == 0 && j > M - 1) || j < 0) continue;
            getHexagone(i, j)->setIsAlive(true);
            //qDebug() << "set true from config: " << i << j;
        }
    }
}

double GameField::getA() const
{
    return a;
}

double GameField::getB() const
{
    return b;
}



