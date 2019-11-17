#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <QString>
#include <QtMath>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>

class GameModel
{
public:
    GameModel();
    void set_NM(int, int);
    void set_cell_size(int);
    void set_mode(QString);
    void set_states(bool**);
    QString get_mode();
    int get_N();
    int get_M();
    int get_cellSize();
    int getLineSize() const;

private:
    int N;
    int M;
    int lineSize = 1;
    int cellSize;
    QString mode;
};

#endif // GAMEMODEL_H
