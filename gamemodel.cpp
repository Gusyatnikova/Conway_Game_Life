#include "gamemodel.h"

GameModel::GameModel()
{
    this->M = 10;
    this->N = 10;
    this->mode = "Replace";
    this->cellSize = 30;
    this->lineSize = 1;
}

QString GameModel::get_mode() {
    return this->mode;
    //QDebug() << "i set " + this->mode;
}

void GameModel::set_NM(int N, int M) {
    this->N = qAbs(N);
    qDebug() << "in set_NM N " << this->N << endl;
    this->M = qAbs(M);
    qDebug() << "in set_NM M " << this->M << endl;
}

void GameModel::set_cell_size(int cell_size) {
    this->cellSize = abs(cell_size);
}

void GameModel::set_mode(QString mode) {
    this->mode = mode;
}

int GameModel::get_M(){
    return this->M;
}

int GameModel::get_N(){
    return this->N;
}

int GameModel::get_cellSize() {
    return  this->cellSize;
}

int GameModel::getLineSize() const
{
    return lineSize;
}
