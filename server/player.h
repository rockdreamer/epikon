#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

namespace Epikon {
namespace Server {

class Player : public QObject
{
Q_OBJECT
public:
    Player();
};

} // namespace Server
} // namespace Epikon

#endif // PLAYER_H
