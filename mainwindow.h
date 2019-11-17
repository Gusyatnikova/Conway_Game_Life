#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamemodel.h"
#include "gameproperty_dialog.h"
#include "mywidget.h"
#include "newfiledialog.h"
#include <QDesktopWidget>
#include <QScrollArea>
#include <QImage>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow* getMainWindow();
    explicit MainWindow(QWidget *parent = nullptr);
    void init(GameModel*);
    void setAlgorithms(DrawAlgorithms*);
    void setAutomat(ConwayAutomat*);
    void setFieldImage(QImage*);
    void getModelArguments(int*);
    ~MainWindow();



private slots:
    void on_actionNew_File_triggered();
    void on_actionSettings_triggered();
    void on_actionOpen_File_triggered();
    void on_actionClear_triggered();
    void on_actionRun_triggered();
    void on_actionNext_Step_triggered();
    void on_actionStop_triggered();
    void nextStep();

    void on_actionON_OFF_Impact_triggered();

    void on_actionSet_XOR_triggered();

    void on_actionSet_Replace_triggered();

    void on_actionAbout_author_triggered();

    void on_actionSave_Game_triggered();

private:
    Ui::MainWindow *ui;
    GameModel* gamemodel;
    QImage* fieldImage;
    DrawAlgorithms* drawAlgorithm;
    MyWidget* myWidget;
    ConwayAutomat* automat;
    QTimer* timer;
    //GameProperty_dialog* gameProperty_dialog;
};

#endif // MAINWINDOW_H
