#include "epikonmainwindow.h"
#include "ui_epikonmainwindow.h"
#include <QMessageBox>
#include "epikongame.h"
#include "epikonplanet.h"
#include "epikonattack.h"
#include "epikonplayer.h"
#include "epikongamescene.h"

EpikonMainWindow::EpikonMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EpikonMainWindow),m_game(0),p1(0),p2(0),m_scene(0)
{
    ui->setupUi(this);

    connect(ui->actionExit, SIGNAL(triggered()),this,SLOT(onQuit()));
    connect(ui->actionAbout_Epikon, SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->actionNew_Game, SIGNAL(triggered()),this,SLOT(onNewGame()));
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
void EpikonMainWindow::onNewGame()
{

    m_game = new Epikon::Client::Game(this);
    EpikonPlanet *pl1, *pl2,*pl3,*pl4;

    p1 = new EpikonPlayer(m_game);
    p1->setName("Player 1");
    p1->setPlanet(QString(":/resources/common/earth-4.svg"));

    m_game->addPlayer(p1,true);

    p2 = new EpikonPlayer(m_game);
    p2->setName("Player 2");
    p2->setPlanet(QString(":/resources/common/earth-3.svg"));
    m_game->addPlayer(p2);

    pl1 = new EpikonPlanet(10,10,100,100, m_game);
    pl1->setName("Test Planet 1");
    m_game->addPlanet(pl1);
    pl1->setMaster(p1);
    pl1->shipsCreated(10);

    pl2 = new EpikonPlanet(10,200,100,100, m_game);
    pl2->setName("Test Planet 2");
    m_game->addPlanet(pl2);
    pl2->setMaster(p1);
    pl2->shipsCreated(10);


    pl3 = new EpikonPlanet(300,200,100,100, m_game);
    pl3->setName("Test Planet 1 2");
    m_game->addPlanet(pl3);
    pl3->setMaster(p2);
    pl3->shipsCreated(10);

    pl4 = new EpikonPlanet(350,400,100,100, m_game);
    pl4->setName("Test Planet 2 2");
    m_game->addPlanet(pl4);
    pl4->setMaster(p2);
    pl4->shipsCreated(10);

    buildGameView();

}

void EpikonMainWindow::buildGameView(){
    if (m_scene==NULL){
        m_scene=new EpikonGameScene(this);
    }
    m_scene->setGame(m_game);
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
