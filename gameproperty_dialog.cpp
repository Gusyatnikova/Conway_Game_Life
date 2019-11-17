#include "gameproperty_dialog.h"
#include "ui_gameproperty_dialog.h"

GameProperty_dialog::GameProperty_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameProperty_dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Properties");
    connect(ui->cellSize_slider, SIGNAL(valueChanged(int)), this, SLOT(setCellValue(int)));
    connect(ui->cellSize_edit, SIGNAL(textChanged(QString)), this, SLOT(setCellSliderValue(QString)));

}

GameProperty_dialog::~GameProperty_dialog()
{
    delete ui;
}

void GameProperty_dialog::set_model(GameModel * model) {
    this->gameModel = model;
}

void GameProperty_dialog::set_automat(ConwayAutomat * automat)
{
    this->automat = automat;
}

void GameProperty_dialog::on_buttonBox_accepted() {
    QString n_edit = ui->N_edit->text();
    QString m_edit = ui->M_edit->text();
    QString cellSize_edit = ui->cellSize_edit->text();
    QString liveB = ui->L_B->text();
    QString liveE = ui->L_E->text();
    QString birthB = ui->B_B->text();
    QString birthE = ui->B_E->text();
    QString firstI = ui->F_I->text();
    QString secondI = ui->S_I->text();

    QString activeCells = this->myWidget->getGameField()->getActiveCells();
    sendParamToModel(n_edit, m_edit, this->gameModel, cellSize_edit);

    myWidget->setGameModel(gameModel);
    bool impact = myWidget->getGameField()->getImpactMode();
    myWidget->setGameField(new GameField(gameModel->get_N(), gameModel->get_M(), gameModel->get_cellSize()));
    int w = m_edit.toInt() * myWidget->getGameField()->getHexagone(0, 0)->getA();
    int h = n_edit.toInt()/2 * (myWidget->getGameField()->getHexagone(0, 0)->getB() + myWidget->getGameModel()->get_cellSize());
    if(w + 100 >= myWidget->getImage()->width() || h + 100 >= myWidget->getImage()->height()) {
        QMessageBox::information(this, "Notification", "Your parameters is too big! Please, set another configuration");
        return;
    }
    myWidget->getGameField()->setConfiguration(activeCells);
    myWidget->getGameField()->setImpactMode(impact);

    this->automat = new ConwayAutomat(gameModel->get_N(), gameModel->get_M());
    if(automat->setParam(liveB, liveE, birthB, birthE, firstI, secondI) != true) {
        QMessageBox::information(this, "Notification", "You set invalid values in Game Parameters block. Please, make sure, that all values is nonnegative. Have a good game!");
    }
    this->automat->setGameField(myWidget->getGameField());
    this->myWidget->setGameAutomat(this->automat);
    this->myWidget->getAlgoritms()->drawGameField(myWidget->getImage(), myWidget->getGameField());

    myWidget->resize(w + 100, h + 100);
    myWidget->update();
}


void GameProperty_dialog::on_replaceButton_clicked()
{
    gameModel->set_mode("Replace");
}

void GameProperty_dialog::on_xorButton_clicked()
{
    gameModel->set_mode("XOR");
}

void GameProperty_dialog::sendParamToModel(QString n_edit, QString m_edit, GameModel * gameModel, QString cellSize_edit) {
    if(n_edit.isEmpty() || m_edit.isEmpty()) {
        QMessageBox::information(this, "Notification", "You did't set N or M. Standart values was set! Have a good game!");
        gameModel->set_NM(this->gameModel->get_N(), this->gameModel->get_M());
    } else {
        gameModel->set_NM(n_edit.toInt(), m_edit.toInt());
    }
    if(gameModel->get_mode().isEmpty()) {
        QMessageBox::information(this, "Notification", "You did't select game mode. Standart mode ""Replace"" was set! Have a good game!");
        gameModel->set_mode("Replace");
    }

    if (cellSize_edit.isEmpty()) {
        gameModel->set_cell_size(this->gameModel->get_cellSize());
    } else {
        gameModel->set_cell_size(cellSize_edit.toInt());
    }

}

void GameProperty_dialog::setCellValue(int tmp) {
    tmp = ui->cellSize_slider->value();
    ui->cellSize_edit->setText(QString::number(tmp));
}

void GameProperty_dialog::setCellSliderValue(QString tmp) {
    int tmp_toInt = ui->cellSize_edit->text().toInt();
    ui->cellSize_slider->setValue(tmp_toInt);
}


void GameProperty_dialog::setMyWidget(MyWidget * myWidget)
{
    this->myWidget = myWidget;
}

void GameProperty_dialog::init() {
    ui->cellSize_edit->setText(QString::number(gameModel->get_cellSize()));
    ui->N_edit->setText(QString::number(gameModel->get_N()));
    ui->M_edit->setText(QString::number(gameModel->get_M()));
    if(gameModel->get_mode() != "Replace") {
        ui->xorButton->setChecked(true);
    } else {
        ui->replaceButton->setChecked(true);
    }
    ui->L_B->setText(QString::number(automat->getLiveBegin()));
    ui->L_E->setText(QString::number(automat->getLiveEnd()));
    ui->B_B->setText(QString::number(automat->getBirthBegin()));
    ui->B_E->setText(QString::number(automat->getBirthEnd()));
    ui->F_I->setText(QString::number(automat->getFirstImpact()));
    ui->S_I->setText(QString::number(automat->getSecondImpact()));
}

