#include "newfiledialog.h"
#include "ui_newfiledialog.h"

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);

}

NewFileDialog::~NewFileDialog()
{
    delete ui;
}

void NewFileDialog::setModel(GameModel * gameModel)
{
    this->gameModel = gameModel;
}

void NewFileDialog::init()
{
    ui->N_edit->setText(QString::number(gameModel->get_N()));
    ui->M_edit->setText(QString::number(gameModel->get_M()));

}

void NewFileDialog::on_buttonBox_accepted()
{
    QString rowsCNT = ui->N_edit->text();
    QString columnsCNT = ui->M_edit->text();

    //calculate(w, h)
    int w = columnsCNT.toInt() * myWidget->getGameField()->getHexagone(0, 0)->getA();
    int h = rowsCNT.toInt()/2 * (myWidget->getGameField()->getHexagone(0, 0)->getB() + myWidget->getGameModel()->get_cellSize());
    if(w + 100 >= myWidget->getImage()->width() || h + 100 >= myWidget->getImage()->height()) {
        QMessageBox::information(this, "Notification", "Your parameters is too big! Please, set another configuration");
        return;
    }
    myWidget->resize(w + 100, h + 100);
    sendParamToModel(rowsCNT, columnsCNT);
    myWidget->update();
}

GameModel *NewFileDialog::getGameModel() const
{
    return gameModel;
}

void NewFileDialog::sendParamToModel(QString rows, QString columns)
{
    if(rows.isEmpty() || columns.isEmpty()) {
        QMessageBox::information(this, "Notification", "You did't set N or M. Standart values was set! Have a good game!");
        gameModel->set_NM(this->gameModel->get_N(), this->gameModel->get_M());
    } else {
        gameModel->set_NM(rows.toInt(), columns.toInt());
    }
}

void NewFileDialog::setMyWidget(MyWidget *value)
{
    myWidget = value;
}

void NewFileDialog::createNewGameFile(GameModel * gameModel) {
    QDate date = QDate::currentDate();

    QString stringFromModel = "-" + QString::number(gameModel->get_N()) + "-" + QString::number(gameModel->get_M()) + "-" + QString::number(gameModel->get_cellSize());
    QString filename = "D:\\education\\Qt - works\\Conway_Game\\FIT_16206_Gusyatnikova_Life_Data\\" + date.toString() + stringFromModel + ".txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream( &file );
        stream << gameModel->get_M() << " " << gameModel->get_N() << "\r\n";
        stream << gameModel->getLineSize() << "\r\n";
        stream << gameModel->get_cellSize() << "\r\n";
        stream.flush();
        file.close();
    }
}
