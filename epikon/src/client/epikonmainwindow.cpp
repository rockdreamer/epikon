#include "epikonmainwindow.h"
#include "ui_epikonmainwindow.h"
#include <QMessageBox>
#include "epikongame.h"
#include "epikonnetworkgame.h"
//#include "epikonplanet.h"
//#include "epikonattack.h"
//#include "epikonplayer.h"
#include "epikongamescene.h"
#include "epikonconnection.h"

using namespace Epikon::Client;

EpikonMainWindow::EpikonMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EpikonMainWindow),m_game(0),p1(0),p2(0),m_scene(0)
{
    ui->setupUi(this);

    connect(ui->actionExit, SIGNAL(triggered()),this,SLOT(onQuit()));
    connect(ui->actionAbout_Epikon, SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->actionNew_Game, SIGNAL(triggered()),this,SLOT(onNewGame()));
    connect(ui->actionConnectToServer, SIGNAL(triggered()),this,SLOT(onNewConnection()));
    // This is here for testing purposes...
    onNewGame();
}

EpikonMainWindow::~EpikonMainWindow()
{
    delete ui;
}

void EpikonMainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void EpikonMainWindow::onNewConnection(){
    m_connection = new Connection();
    connect(m_connection,SIGNAL(error(const QString&)), this, SLOT(onConnectionError(const QString&)));
    m_connection ->connectToHost("127.0.0.1",20000);
}

void EpikonMainWindow::onNewNetworkGame()
{

    m_game = new Epikon::Client::NetworkGame(m_connection, this);

    buildGameView();

}
void EpikonMainWindow::onNewGame()
{

    m_game = new Epikon::Client::Game(this);
    m_game->testGame();

    buildGameView();

}

void EpikonMainWindow::onConnectionError(const QString &error)
{
    qDebug() << "Connection error:" << error;
}

void EpikonMainWindow::buildGameView(){
    if (m_scene==NULL){
        m_scene=new EpikonGameScene(this);
    }
    m_scene->setGame(m_game);
    m_game->setScene(m_scene);
    ui->gameView->setScene(m_scene);
}

void EpikonMainWindow::onQuit()
{
    QMessageBox ask;
    ask.setText(tr("Press OK to confirm you want to quit"));
    ask.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    ask.setDefaultButton(QMessageBox::Cancel);
    int ret = ask.exec();
    if (ret==QMessageBox::Ok)
        QApplication::quit();
}
