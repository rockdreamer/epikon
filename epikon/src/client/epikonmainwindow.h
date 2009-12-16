#ifndef EPIKONMAINWINDOW_H
#define EPIKONMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class EpikonMainWindow;
}
namespace Epikon {
    namespace Client {
        class Game;
        class NetworkGame;
        class Connection;
    }
    namespace Server {
        class Server;
    }
    namespace Protocol {
        class Protocol;
    }
}
class EpikonPlayer;
class EpikonGameScene;

class EpikonMainWindow : public QMainWindow {
    Q_OBJECT
public:
    EpikonMainWindow(QWidget *parent = 0);
    ~EpikonMainWindow();

public slots:
    void onQuit();
    void onNewGame();
    void onNewConnection();
    void onNewNetworkGame();
    void onTriggerServer(bool enable);
    void onConnectionError(const QString &error);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::EpikonMainWindow *ui;
    Epikon::Client::Game * m_game;
    Epikon::Client::NetworkGame * m_netgame;
    Epikon::Protocol::Protocol * m_connection;
    Epikon::Server::Server * m_server;

    EpikonPlayer *p1, *p2;
    EpikonGameScene * m_scene;
    void buildGameView();

};

#endif // EPIKONMAINWINDOW_H
