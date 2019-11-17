#ifndef GAMEPROPERTY_DIALOG_H
#define GAMEPROPERTY_DIALOG_H

#include <QDialog>
#include "gamemodel.h"
#include <iostream>
#include <string>
#include <QDebug>
#include <QtGlobal>
#include <QSlider>
#include <QTextEdit>
#include <QMessageBox>
#include "mywidget.h"
#include "conwayautomat.h"

namespace Ui {
class GameProperty_dialog;
}

class GameProperty_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameProperty_dialog(QWidget *parent = nullptr);
    ~GameProperty_dialog();
    void set_model(GameModel*);
    void set_automat(ConwayAutomat*);
    void setMyWidget(MyWidget*);
    void init();

private slots:
    void on_buttonBox_accepted();
    void on_replaceButton_clicked();
    void on_xorButton_clicked();
    void setCellValue(int);
    void setCellSliderValue(QString);

private:
    Ui::GameProperty_dialog *ui;
    GameModel * gameModel;
    ConwayAutomat* automat;
    void sendParamToModel(QString, QString, GameModel*, QString);
    MyWidget* myWidget;
};

#endif // GAMEPROPERTY_DIALOG_H
