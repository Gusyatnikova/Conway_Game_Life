#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStatusBar *bar = new QStatusBar;
    this->setStatusBar(bar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(GameModel* gameModelArg) {
    resize(QDesktopWidget().availableGeometry(this).size() * 0.95);

    this->timer = new QTimer(this);
    this->timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextStep()));

    this->gamemodel = gameModelArg;
    this->myWidget = new MyWidget(this->width(), this->height(), this->gamemodel, this->automat);
    //тут м.б. перерасчет
    QScrollArea* scrollArea = new QScrollArea();
    QVBoxLayout* layout = new QVBoxLayout;
    myWidget->resize(this->width() - 10, this->height() - 100);
    myWidget->setLayout(layout);
    scrollArea->setWidget(myWidget);
    this->setCentralWidget(scrollArea);

    myWidget->getAlgoritms()->drawGameField(myWidget->getImage(), myWidget->getGameField());
    if(myWidget->getGameField()->getImpactMode() == true) {
        //myWidget->displayImpacts();
        //std::unique_ptr<QPainter> p = std::make_shared<QPainter>(this);
    }
}

void MainWindow::setAlgorithms(DrawAlgorithms * algorithms)
{
    this->drawAlgorithm = algorithms;
}

void MainWindow::on_actionOpen_File_triggered()
{

    QString path = "D:\\education\\Qt - works\\Conway_Game\\Data";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "D://education//Qt - works//Conway_Game//FIT_16206_Gusyatnikova_Life_Data//",
                                                    tr("Game Life Configuration (*.txt)"));
    //TODO: send param to model
    //init(gamemodel);

    QFile file(fileName);
    bool isFine = false;
    QString curLine;
    QString states;
    int curNum = 0;
    int n = 0;
    int m = 0;
    int i, j;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream inStream(&file);
        while(!inStream.atEnd()) {
            curLine = inStream.readLine();
            //qDebug()<< "i read line " <<  curLine;
            if(curNum == 0){
                QStringList arr = curLine.split(" ");
                n = arr[1].toInt();
                m = arr[0].toInt();
                myWidget->getGameModel()->set_NM(m, n);
            }
            if(curNum == 1){
                //
            }
            if(curNum == 2){
                myWidget->getGameModel()->set_cell_size(curLine.toInt());
            }
            if(curNum == 3){
                //all
            }
            if(curNum >= 4) {
                QStringList arr = curLine.split(' ');
                i = arr[0].toInt();
                j = arr[1].toInt();
                states = states + QString::number(i) + " " + QString::number(j) + ",";
                //qDebug()<< "i read live: (i, j)" << i << j;
            }
            curNum = curNum + 1;
        }
        isFine = true;
        QMessageBox::information(this, "Notification", "Game was read!");
        file.close();
    }
    if(!isFine) QMessageBox::information(this, "Notification", "Sorry, we don't read file.....");

    myWidget->setGameField(new GameField(gamemodel->get_N(), gamemodel->get_M(), gamemodel->get_cellSize()));
    myWidget->getGameField()->setConfiguration(states);

    myWidget->setGameAutomat(new ConwayAutomat(gamemodel->get_N(), gamemodel->get_M()));
    myWidget->getGameAutomat()->setGameField(myWidget->getGameField());
    myWidget->getAlgoritms()->drawGameField(myWidget->getImage() ,myWidget->getGameField());
    int w = gamemodel->get_M() * myWidget->getGameField()->getHexagone(0, 0)->getA();
    int h = gamemodel->get_N()/2 * (myWidget->getGameField()->getHexagone(0, 0)->getB() + myWidget->getGameModel()->get_cellSize());
    myWidget->resize(w + 100, h + 100);
    this->setAutomat(myWidget->getGameAutomat());

    myWidget->update();

}

void MainWindow::on_actionNew_File_triggered()
{
    NewFileDialog newFieldDialog;
    newFieldDialog.setModel(this->gamemodel);
    newFieldDialog.setModal(true);
    newFieldDialog.setMyWidget(myWidget);
    newFieldDialog.init();
    newFieldDialog.exec();



    myWidget->setGameModel(newFieldDialog.getGameModel());
    myWidget->setGameField(new GameField(gamemodel->get_N(), gamemodel->get_M(), gamemodel->get_cellSize()));

    myWidget->setGameAutomat(new ConwayAutomat(gamemodel->get_N(), gamemodel->get_M()));
    myWidget->getGameAutomat()->setGameField(myWidget->getGameField());
    myWidget->getAlgoritms()->drawGameField(myWidget->getImage() ,myWidget->getGameField());

    this->setAutomat(myWidget->getGameAutomat());
    int w = gamemodel->get_M() * myWidget->getGameField()->getHexagone(0, 0)->getA();
    int h = gamemodel->get_N()/2 * (myWidget->getGameField()->getHexagone(0, 0)->getB() + myWidget->getGameModel()->get_cellSize());
    myWidget->resize(w + 100, h + 100);
    myWidget->update();
}

void MainWindow::on_actionSettings_triggered()
{
    GameProperty_dialog gameProperty_dialog;
    gameProperty_dialog.set_model(this->gamemodel);
    gameProperty_dialog.set_automat(this->automat);
    gameProperty_dialog.setMyWidget(myWidget);
    gameProperty_dialog.init();
    gameProperty_dialog.setModal(true);
    gameProperty_dialog.exec();
    this->automat = myWidget->getGameAutomat();

    myWidget->update();
}

Ui::MainWindow* MainWindow::getMainWindow() {
    return this->ui;
}

void MainWindow::setFieldImage(QImage* qImage){
    this->fieldImage = qImage;
}

void MainWindow::getModelArguments(int* argArray) {
    argArray[0] = this->gamemodel->get_N();
    argArray[1] = this->gamemodel->get_M();
    argArray[2] = this->gamemodel->get_cellSize();
}

void MainWindow::on_actionClear_triggered()
{
    myWidget->getAlgoritms()->clearField(myWidget->getImage(), myWidget->getGameField());
    myWidget->update();
}

void MainWindow::on_actionRun_triggered()
{
    ui->actionNext_Step->setEnabled(false);
    ui->actionClear->setEnabled(false);
    ui->actionNew_File->setEnabled(false);
    ui->actionSettings->setEnabled(false);
    ui->actionOpen_File->setEnabled(false);
    ui->actionON_OFF_Impact->setEnabled(false);
    ui->actionSet_XOR->setEnabled(false);
    ui->actionSet_Replace->setEnabled(false);
    ui->actionSave_Game->setEnabled(false);
    timer->start();
}

void MainWindow::on_actionNext_Step_triggered()
{
    automat->step();
    myWidget->getAlgoritms()->drawGameField(myWidget->getImage(), myWidget->getGameField());
    myWidget->update();
}

void MainWindow::on_actionStop_triggered()
{
    timer->stop();
    ui->actionNext_Step->setEnabled(true);
    ui->actionClear->setEnabled(true);
    ui->actionNew_File->setEnabled(true);
    ui->actionSettings->setEnabled(true);
    ui->actionOpen_File->setEnabled(true);
    ui->actionON_OFF_Impact->setEnabled(true);
    ui->actionSet_XOR->setEnabled(true);
    ui->actionSet_Replace->setEnabled(true);
    ui->actionSave_Game->setEnabled(true);
}

void MainWindow::nextStep()
{
    automat->step();
    myWidget->getAlgoritms()->drawGameField(myWidget->getImage(), myWidget->getGameField());
    myWidget->update();
}

//NOTE: выход из run по esc и напистаь об этом в описании

void MainWindow::on_actionON_OFF_Impact_triggered()
{
    //qDebug() << "in impact NM" << myWidget->getGameField()->getN() << myWidget->getGameField()->getM();
    if(myWidget->getGameField()->getImpactMode() == false) {
        myWidget->getGameField()->setImpactMode(true);
        myWidget->update();
    } else {
        myWidget->getGameField()->setImpactMode(false);
        myWidget->update();
    }
}

void MainWindow::on_actionSet_XOR_triggered()
{
    gamemodel->set_mode("XOR");
}

void MainWindow::on_actionSet_Replace_triggered()
{
    gamemodel->set_mode("Replace");
}

void MainWindow::on_actionAbout_author_triggered()
{
    About* about = new About();
    about->exec();
}

void MainWindow::on_actionSave_Game_triggered()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    QString stringFromModel = "-" + QString::number(myWidget->getGameModel()->get_N()) + "-" + QString::number(myWidget->getGameModel()->get_M()) + "-" + QString::number(myWidget->getGameModel()->get_cellSize());
    QString filename = "D:\\education\\Qt - works\\Conway_Game\\FIT_16206_Gusyatnikova_Life_Data\\" + date.toString() + "-" + QString::number(time.minute()) + stringFromModel + ".txt";
    QFile file(filename);
    bool isFine = false;
    int n = myWidget->getGameModel()->get_N();
    int m = myWidget->getGameModel()->get_M();
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream( &file );
        stream << m << " " << n << "\r\n";
        stream << myWidget->getGameModel()->getLineSize() << "\r\n";
        stream << myWidget->getGameModel()->get_cellSize() << "\r\n";
        stream << myWidget->getGameField()->calculateAll() << "\r\n";
        for(int str = 0; str < n; str++) {
            for(int col = 0; col < m; col++) {
                if (str%2 == 1 && col >= m - 1) break;
                if (myWidget->getGameField()->getHexagone(str, col)->getIsAlive() == true) {
                    stream << str << " " << col << "\r\n";
                }
            }
        }
        stream.flush();
        isFine = true;
        QMessageBox::information(this, "Notification", "Game was Saved!");
        file.close();
    }
    if(!isFine) QMessageBox::information(this, "Notification", "Sorry, we don't save game.....");
}

void MainWindow::setAutomat(ConwayAutomat* automatParam)
{
    this->automat = automatParam;
}
