#include <QApplication>
#include <QLabel>
#include <QtDebug>
#include "gamemodel.h"
#include "mainwindow.h"
#include "DrawAlgorithms.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    GameModel  * gameModel = new GameModel();
    DrawAlgorithms* alghorithms = new DrawAlgorithms(gameModel);
    ConwayAutomat* automat = new ConwayAutomat(gameModel->get_N(), gameModel->get_M());

    w.setAutomat(automat);
    w.setAlgorithms(alghorithms);
    w.init(gameModel);
    w.show();

    return a.exec();
}
