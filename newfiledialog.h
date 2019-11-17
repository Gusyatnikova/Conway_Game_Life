#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "gamemodel.h"
#include "mywidget.h"
#include <QDateTime>

namespace Ui {
class NewFileDialog;
}

class NewFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFileDialog(QWidget *parent = nullptr);
    ~NewFileDialog();
    void setModel(GameModel*);
    void createNewGameFile(GameModel*);
    void init();
    GameModel *getGameModel() const;

    void setMyWidget(MyWidget *value);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewFileDialog *ui;
    GameModel* gameModel;
    void sendParamToModel(QString, QString);
    MyWidget* myWidget;
};

#endif // NEWFILEDIALOG_H
