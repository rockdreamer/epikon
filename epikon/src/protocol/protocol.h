#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>

namespace Epikon {
namespace Protocol {

class Protocol : public QObject
{
Q_OBJECT
public:
    explicit Protocol(QObject *parent = 0);

signals:

public slots:

};

} // namespace Protocol
} // namespace Epikon

#endif // PROTOCOL_H
