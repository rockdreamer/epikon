#ifndef EPIKONGAMESCENE_H
#define EPIKONGAMESCENE_H

#include <QGraphicsScene>

class EpikonGame;
class EpikonGameScene : public QGraphicsScene
{
Q_OBJECT
public:
    explicit EpikonGameScene(QObject *parent = 0);
    void setGame(EpikonGame *game);
signals:

public slots:
    void onSelectionChange();
private:
    EpikonGame * m_game;
    void drawInitialScene();
    QList<QGraphicsItem *> currentSelection, previousSelection;
};

#endif // EPIKONGAMESCENE_H
