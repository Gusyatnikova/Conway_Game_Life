#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QPixmap pix(":/ConwayGameRes/Изображение 004.jpg");
    QPixmap hex(":/ConwayGameRes/hex.jpg");
    ui->label->setScaledContents(true);
    ui->label_2->setScaledContents(true);
    ui->label->setPixmap(pix);
    ui->label_2->setPixmap(hex);

}

About::~About()
{
    delete ui;
}
