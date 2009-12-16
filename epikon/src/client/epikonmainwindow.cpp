#include "epikonmainwindow.h"
#include "ui_epikonmainwindow.h"
#include "ui_serverdialog.h"

#include <QMessageBox>
#include "epikongame.h"
#include "epikonnetworkgame.h"
#include "epikongamescene.h"
#include "protocol/protocol.h"
#include "server/epikonserver.h"

using namespace Epikon::Client;

EpikonMainWindow::EpikonMainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::EpikonMainWindow),m_game(0),p1(0),p2(0),m_scene(0), m_server(0)
{
    ui->setupUi(this);

    connect(ui->actionExit, SIGNAL(triggered()),this,SLOT(onQuit()));
    connect(ui->actionAbout_Epikon, SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->actionNew_Game, SIGNAL(triggered()),this,SLOT(onNewGame()));
    connect(ui->actionConnectToServer, SIGNAL(triggered()),this,SLOT(onNewConnection()));
    connect(ui->actionAllow_Others_to_Connect_to_me, SIGNAL(toggled(bool)),this,SLOT(onTriggerServer(bool)));
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
    m_connection = new Epikon::Protocol::Protocol("127.0.0.1",20000);
    connect(m_connection,SIGNAL(error(const QString&)), this, SLOT(onConnectionError(const QString&)));
    m_connection ->start();
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

void EpikonMainWindow::onTriggerServer(bool enable){
    if (enable){
        QDialog dlg;
        Ui::ServerDialog ui_dlg;
        ui_dlg.setupUi(&dlg);
        dlg.exec();
        if (dlg.result()==QDialog::Accepted){
            if (!m_server)
                m_server = new Epikon::Server::Server(this);
            m_server->setMaxClients((quint16) ui_dlg.maxPlayers->value());
            m_server->listen(QHostAddress::Any, (quint16) ui_dlg.portNumber->value());
        }
        return;

    }
    if (
            QMessageBox::question(this, tr("Really stop server?"),
                                  tr("If you wish to stop allowin others to connect,"
                                     "press OK"),
                                  QMessageBox::Ok | QMessageBox::Cancel,
                                  QMessageBox::Ok )
            == QMessageBox::Ok)
    {
        qDebug() << "Closing Server";
        m_server->close();
    }
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
