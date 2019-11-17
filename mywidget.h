#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QLabel>
#include <QColor>
#include <QDebug>
#include <QMouseEvent>
#include <QFontDatabase>
#include "DrawAlgorithms.h"
#include "gamemodel.h"
#include "gamefield.h"
#include "conwayautomat.h"
#include "about.h"


class MyWidget : public QWidget
{
public:
    MyWidget(int, int, GameModel*, ConwayAutomat*);
    ~MyWidget() override;
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent (QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void setAlgorithms(DrawAlgorithms*);
    void setGameField(GameField*);
    void setGameModel(GameModel*);
    void displayImpacts(QPainter* painter);
    GameField* getGameField();
    DrawAlgorithms* getAlgoritms();
    QImage* getImage();
    ConwayAutomat *getGameAutomat() const;
    GameModel *getGameModel() const;
    void setGameAutomat(ConwayAutomat *);

private:
    int N;
    int M;
    int cellSize;
    QPainter* painter;
    DrawAlgorithms* algorithms;
    QImage* image;
    GameField* gameField;
    GameModel* gameModel;
    ConwayAutomat* gameAutomat;
};

#endif // MYWIDGET_H
