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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::EpikonMainWindow *ui;
    Epikon::Client::Game * m_game;
    Epikon::Client::NetworkGame * m_netgame;
    Epikon::Client::Connection * m_connection;

    EpikonPlayer *p1, *p2;
    EpikonGameScene * m_scene;
    void buildGameView();

};

#endif // EPIKONMAINWINDOW_H
