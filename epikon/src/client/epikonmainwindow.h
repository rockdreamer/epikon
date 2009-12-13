#ifndef EPIKONMAINWINDOW_H
#define EPIKONMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class EpikonMainWindow;
}
namespace Epikon {
    namespace Client {
        class Game;
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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::EpikonMainWindow *ui;
    Epikon::Client::Game * m_game;
    EpikonPlayer *p1, *p2;
    EpikonGameScene * m_scene;
    void buildGameView();

};

#endif // EPIKONMAINWINDOW_H
