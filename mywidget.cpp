


#include "mywidget.h"

MyWidget::MyWidget(int width, int height, GameModel* gameModel, ConwayAutomat* conwayAutomat)
{
    this->gameModel = gameModel;
    image = new QImage(10000, 10000, QImage::Format_RGB32);
    algorithms->setWhiteBackground(this->image);

    this->N = gameModel->get_N();
    this->M = gameModel->get_M();
    this->cellSize = gameModel->get_cellSize();
    this->gameField = new GameField(N, M, cellSize);
    this->gameAutomat = conwayAutomat;
    this->gameAutomat->setGameField(this->gameField);
    //qDebug() << this->gameField->getHexagone(0, 0)->getCoordX();

    algorithms->drawGameField(image, gameField);
}

void MyWidget::paintEvent(QPaintEvent* e)
{
    QPainter* painter = new QPainter(this);
    this->painter = painter;
    painter->drawImage(QPoint(0,0), *this->image);

    //qDebug() << "i'm into paintEvent and draw Image!";
    if(gameField->getImpactMode() == true) displayImpacts(painter);
}

void MyWidget::setAlgorithms(DrawAlgorithms * dA)
{
    this->algorithms = dA;
}

void MyWidget::setGameField(GameField * gameField)
{
    //TODO: free old field
    this->gameField = gameField;
    this->N = gameField->getN();
    this->M = gameField->getM();
}

void MyWidget::setGameModel(GameModel * gameModel)
{
    this->gameModel = gameModel;
}

void MyWidget::displayImpacts(QPainter* painter)
{
    int fontSize = 12;
    painter->setFont(QFont("Tahoma", fontSize));
    painter->setPen(QPen(Qt::black, fontSize));
    int cs = gameModel->get_cellSize();
    gameAutomat->calculateImpact();
    if(cellSize < 10) return;
    qDebug() << N << M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if (i%2 == 1 && j == M - 1) break;
            Point center(gameField->getHexagone(i, j)->getCenter());
            QString text = QString::number(gameAutomat->getImpact(i, j));
            painter->drawText(center.getX() - cs/2, center.getY() + cs/3, text);
        }
    }
}

DrawAlgorithms *MyWidget::getAlgoritms()
{
    return this->algorithms;
}

QImage *MyWidget::getImage()
{
    return this->image;
}

GameField *MyWidget::getGameField()
{
    return this->gameField;
}

void MyWidget::mousePressEvent(QMouseEvent * mouseEvent)
{
    int  x = mouseEvent->pos().x();
    int y = mouseEvent->pos().y();
    unsigned char* curColor = new unsigned char[4];
    curColor = algorithms->checkColor(image, x, y);
    if(curColor[0] == 0 && curColor[1] == 0 && curColor[2] == 0 && curColor[3] == 255) return;
    if(curColor[0] == 255 && curColor[1] == 255 && curColor[2] == 255 && curColor[3] == 255) return;
    Hexagone* curHex = gameField->findByCoord(x, y);
    if(gameModel->get_mode() == "Replace") {
        if(curHex->getIsAlive() != true) {
            curHex->setIsAlive(true);
        }
        algorithms->fillSpan(image, new Point(x, y), curHex->aliveColor);
    } else {
        if(curHex->getIsAlive() == true) {
            curHex->setIsAlive(false);
            algorithms->fillSpan(image, new Point(x, y), curHex->ripColor);
        } else {
            curHex->setIsAlive(true);
            algorithms->fillSpan(image, new Point(x, y), curHex->aliveColor);
        }
    }
    update();
    free(curColor);
}

void MyWidget::mouseMoveEvent(QMouseEvent * mouseEvent)
{
    int  x = mouseEvent->pos().x();
    int y = mouseEvent->pos().y();
    unsigned char* curColor = new unsigned char[4];
    curColor = algorithms->checkColor(image, x, y);
    if(curColor[0] == 0 && curColor[1] == 0 && curColor[2] == 0 && curColor[3] == 255) return;
    if(curColor[0] == 255 && curColor[1] == 255 && curColor[2] == 255 && curColor[3] == 255) return;
    Hexagone* curHex = gameField->findByCoord(x, y);
    if(gameModel->get_mode() == "Replace") {
        if(curHex->getIsAlive() != true) {
            curHex->setIsAlive(true);
        }
        algorithms->fillSpan(image, new Point(x, y), curHex->aliveColor);
    } else {
        if(curHex->getIsAlive() == true) {
            curHex->setIsAlive(false);
            algorithms->fillSpan(image, new Point(x, y), curHex->ripColor);
        } else {
            curHex->setIsAlive(true);
            algorithms->fillSpan(image, new Point(x, y), curHex->aliveColor);
        }
    }
    update();
    free(curColor);
}

MyWidget::~MyWidget() {
    free(this->image);
    //free(this->painter);
    free(this->gameField);
}

ConwayAutomat *MyWidget::getGameAutomat() const
{
    return gameAutomat;
}

GameModel *MyWidget::getGameModel() const
{
    return gameModel;
}

void MyWidget::setGameAutomat(ConwayAutomat *value)
{
    gameAutomat = value;
}


