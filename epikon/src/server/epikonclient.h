#ifndef EPIKONCLIENT_H
#define EPIKONCLIENT_H

#include <QThread>
#include <QTcpSocket>

class EpikonClient : public QThread
{
Q_OBJECT
public:
    explicit EpikonClient(QObject *parent = 0);
    void run();

    inline void setSocketDescriptor(int descriptor) {m_descriptor = descriptor;};
signals:
    void socketError(QTcpSocket::SocketError socketError);

public slots:

private:
    int m_descriptor;
};

#endif // EPIKONCLIENT_H
