#include "conwayautomat.h"

ConwayAutomat::ConwayAutomat(int N, int M)
{
    this->n = N;
    this->m = M;
    impact = new double*[n];
    oldStates = new bool*[n];
    newStates = new bool*[n];
    for(int i = 0; i < n; i++) {
        if(i % 2 == 1) {
            impact[i] = new double[m - 1];
            oldStates[i] = new bool[m - 1];
            newStates[i] = new bool[m - 1];
        } else {
            impact[i] = new double[m];
            oldStates[i] = new bool[m];
            newStates[i] = new bool[m];
        }
        for(int j = 0; j < m; j++) {
            if((j == m - 1) && i % 2 == 1) break;
            impact[i][j] = 0.0;
            oldStates[i][j] = false;
            newStates[i][j] = false;
        }
    }
}

ConwayAutomat::~ConwayAutomat()
{
    delete[] impact[gameField->getM()];
    delete[] oldStates[gameField->getM()];
    delete[] newStates[gameField->getM()];
}

void ConwayAutomat::setGameField(GameField* gameFieldParam) {
    this->gameField = gameFieldParam;
    this->n = gameFieldParam->getN();
    this->m = gameFieldParam->getM();
}

void ConwayAutomat::getOldStates(bool ** oldStatesParam) const
{
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i%2 == 1 && j >= m-1) break;
            //qDebug() << gameField->getM();
            oldStatesParam[i][j] = gameField->getHexagone(i, j)->getIsAlive();
            //qDebug() << "old states: is Alive? (i, j): " << i << j << oldStates[i][j];
        }
    }
}



void ConwayAutomat::setNewStates(bool** statesParam)
{
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {

            if(i%2 == 1 && (j == m - 1)) break;
            //check birth
            if(oldStates[i][j] == false && (birthBegin <= impact[i][j] && impact[i][j] <= birthEnd)) {
                newStates[i][j] = true;
                gameField->getHexagone(i, j)->setIsAlive(true);
            }
            //check continue be live
            if(oldStates[i][j] == true && (liveBegin <= impact[i][j] && impact[i][j] <= liveEnd)) {
                newStates[i][j] = true;
                gameField->getHexagone(i, j)->setIsAlive(true);
            }
            //check rip : too many
            if(impact[i][j] > liveEnd) {
                newStates[i][j] = false;
                gameField->getHexagone(i, j)->setIsAlive(false);
            }
            //check rip : lonely
            if(impact[i][j] < liveBegin) {
                newStates[i][j] = false;
                gameField->getHexagone(i, j)->setIsAlive(false);
            }
           // qDebug() << "set new state for" << i << j << newStates[i][j];
        }
    }
}

bool ConwayAutomat::setParam(QString l_bs, QString l_es, QString b_bs, QString b_es, QString f_is, QString s_is)
{
    double l_b = l_bs.toDouble();
    double l_e = l_es.toDouble();
    double b_b = b_bs.toDouble();
    double b_e = b_es.toDouble();
    double f_i = f_is.toDouble();
    double s_i = s_is.toDouble();

    if (l_b < 0 || l_e < 0 || b_b < 0 || b_e < 0 || f_i < 0 || s_i < 0) return false;
    if(l_b > b_b || b_b > b_e || b_e > l_e) return false;
    this->liveBegin = l_b;
    this->liveEnd = l_e;
    this->birthBegin = b_b;
    this->birthEnd = b_e;
    this->firstImpact = f_i;
    this->secondImpact = s_i;
    return true;
}

void ConwayAutomat::step()
{
    getOldStates(this->oldStates);
    calculateImpact();
    setNewStates(this->newStates);
}

double ConwayAutomat::getLiveBegin() const
{
    return liveBegin;
}

double ConwayAutomat::getLiveEnd() const
{
    return liveEnd;
}

double ConwayAutomat::getBirthBegin() const
{
    return birthBegin;
}

double ConwayAutomat::getBirthEnd() const
{
    return birthEnd;
}

double ConwayAutomat::getFirstImpact() const
{
    return firstImpact;
}

double ConwayAutomat::getSecondImpact() const
{
    return secondImpact;
}

double ConwayAutomat::getImpact(int i, int j)
{
    return impact[i][j];
}

GameField *ConwayAutomat::getGameField()
{
    return this->gameField;
}

void ConwayAutomat::calculateImpact()
{
    int firstCNT = 0;
    int secondCNT = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(j == m - 1 && i % 2 == 1) break;
            firstCNT = calcFirstCNT(i, j);
            secondCNT = calcSecondCNT(i, j);
            this->impact[i][j] = firstCNT * firstImpact + secondCNT * secondImpact;
            //qDebug() << "IMPACT : i j " << i << j << impact[i][j];
        }
    }
}

int ConwayAutomat::calcFirstCNT(int i, int j)
{
    int cnt = 0;


    if(gameField->getHexagone(i, j - 1) != nullptr && gameField->getHexagone(i, j - 1)->getIsAlive() == true) cnt++;
    if(gameField->getHexagone(i, j + 1) != nullptr && gameField->getHexagone(i, j + 1)->getIsAlive() == true) cnt++;
    if(gameField->getHexagone(i + 1, j) != nullptr && gameField->getHexagone(i + 1, j)->getIsAlive() == true) cnt++;

    if(i%2 == 0) {
        if(gameField->getHexagone(i - 1, j - 1) != nullptr && gameField->getHexagone(i - 1, j - 1)->getIsAlive() == true) cnt++;
        if(gameField->getHexagone(i - 1, j) != nullptr && gameField->getHexagone(i - 1, j)->getIsAlive() == true) cnt++;
        if(gameField->getHexagone(i + 1, j - 1) != nullptr && gameField->getHexagone(i + 1, j - 1)->getIsAlive() == true) cnt++;

    } else {
        if(gameField->getHexagone(i - 1, j) != nullptr && gameField->getHexagone(i - 1, j)->getIsAlive() == true) cnt++;
        if(gameField->getHexagone(i - 1, j + 1) != nullptr && gameField->getHexagone(i - 1, j + 1)->getIsAlive() == true) cnt++;
        if(gameField->getHexagone(i + 1, j + 1) != nullptr && gameField->getHexagone(i + 1, j + 1)->getIsAlive() == true) cnt++;
    }

    //qDebug() << "for (i,j) first CNT " << i << j << cnt;
    return cnt;
}

int ConwayAutomat::calcSecondCNT(int i, int j)
{
    int cnt = 0;

    if(gameField->getHexagone(i - 2, j) != nullptr && gameField->getHexagone(i -2, j)->getIsAlive() == true) cnt++;
    if(gameField->getHexagone(i + 2, j) != nullptr && gameField->getHexagone(i + 2, j)->getIsAlive() == true) cnt++;

    if(i%2 == 1) {
        if(gameField->getHexagone(i - 1, j - 1) != nullptr && gameField->getHexagone(i - 1, j - 1)->getIsAlive() == true) cnt++;
        if(gameField->getHexagone(i + 1, j - 1) != nullptr && gameField->getHexagone(i + 1, j - 1)->getIsAlive() == true) cnt++;
        if(gameField->getHexagone(i + 1, j + 2) != nullptr && gameField->getHexagone(i + 1, j + 2)->getIsAlive() == true) cnt++;
        if(gameField->getHexagone(i - 1, j + 2) != nullptr && gameField->getHexagone(i - 1, j + 2)->getIsAlive() == true) cnt++;
    } else {
        if(gameField->getHexagone(i - 1, j - 2) != nullptr && gameField->getHexagone(i - 1, j - 2)->getIsAlive() == true) cnt++;
        if(gameField->getHexagone(i + 1, j - 2) != nullptr && gameField->getHexagone(i + 1, j - 2)->getIsAlive() == true) cnt++;
        if(gameField->getHexagone(i + 1, j + 1) != nullptr && gameField->getHexagone(i + 1, j + 1)->getIsAlive() == true) cnt++;
        if(gameField->getHexagone(i - 1, j + 1) != nullptr && gameField->getHexagone(i - 1, j + 1)->getIsAlive() == true) cnt++;
    }

    //qDebug() << "for (i,j) sec CNT" << i << j << cnt;
    return cnt;
}

