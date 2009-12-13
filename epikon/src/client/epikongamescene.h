#ifndef EPIKONGAMESCENE_H
#define EPIKONGAMESCENE_H

#include <QGraphicsScene>

namespace Epikon {
    namespace Client {
        class Game;
    }
}class EpikonPlanet;
class EpikonPlayer;

class EpikonGameScene : public QGraphicsScene
{
Q_OBJECT
public:
    explicit EpikonGameScene(QObject *parent = 0);
    void setGame(Epikon::Client::Game *game);
signals:
    void attack(EpikonPlanet& from, EpikonPlanet& to, EpikonPlayer& player);
public slots:
    void onSelectionChange();
private:
    Epikon::Client::Game * m_game;
    void drawInitialScene();
    QList<QGraphicsItem *> currentSelection, previousSelection;
};

#endif // EPIKONGAMESCENE_H
