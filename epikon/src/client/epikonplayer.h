#ifndef EPIKONPLAYER_H
#define EPIKONPLAYER_H

#include <QObject>

class EpikonPlanet;
class QSvgRenderer;

class EpikonPlayer : public QObject
{
      Q_OBJECT
      Q_PROPERTY(QString name READ name WRITE setName)
      Q_PROPERTY(int remainingShips READ remainingShips WRITE setRemainingShips)
      Q_PROPERTY(int remainingPlanets READ remainingPlanets WRITE setRemainingPlanets)

public:
      explicit EpikonPlayer(QObject *parent = 0);

      QString name() {return m_name;};
      void setName(const QString& in) {m_name=in;};

      int remainingShips() {return m_remainingShips;};
      void setRemainingShips(int in) {m_remainingShips=in;};

      int remainingPlanets() {return m_remainingPlanets;};
      void setRemainingPlanets(int in) {m_remainingPlanets=in;};

      QSvgRenderer *planetRenderer() {return m_planetrenderer;};
      void setPlanet(const QString& filename);
  public slots:
      void capturedPlanet(EpikonPlanet* planet);
      void lostPlanet(EpikonPlanet* planet);
      void generatedShips(int num);
      void lostShips(int num);
  signals:
      void lost();
  private:
      QString m_name;
      int m_remainingShips, m_remainingPlanets;
      QSvgRenderer *m_planetrenderer;

};

#endif // EPIKONPLAYER_H
