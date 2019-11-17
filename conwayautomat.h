#ifndef CONWAYAUTOMAT_H
#define CONWAYAUTOMAT_H
#include "gamefield.h"
#include "gamemodel.h"

class ConwayAutomat
{
public:
    ConwayAutomat(int, int);
    ~ConwayAutomat();
    void setGameField(GameField*);
    bool setParam(QString, QString, QString, QString, QString, QString);
    double getLiveBegin() const;
    double getLiveEnd() const;
    double getBirthBegin() const;
    double getBirthEnd() const;
    double getFirstImpact() const;
    double getSecondImpact() const;
    double getImpact(int, int);
    GameField* getGameField();

    void setNewStates(bool**);
    void step();
    void getOldStates(bool**) const;
    void calculateImpact();

private:
    double liveBegin = 2.0;
    double liveEnd = 3.3;
    double birthBegin = 2.3;
    double birthEnd = 2.9;
    double firstImpact = 1.0;
    double secondImpact = 0.3;
    int n = 0;
    int m = 0;
    double** impact;
    bool** oldStates;
    bool** newStates;
    GameField* gameField;
    int calcFirstCNT(int, int);
    int calcSecondCNT(int, int);

};

#endif // CONWAYAUTOMAT_H
