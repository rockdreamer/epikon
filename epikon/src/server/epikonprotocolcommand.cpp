#include "epikonprotocolcommand.h"

void Epikon::Protocol::Command::sendToSocket(QTcpSocket* socket)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out << (quint16)0;
    writeToDataStream(out);
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    socket->write(block);
}

void Epikon::Protocol::Command::readFromDataStream(QDataStream& stream)
{
}

void Epikon::Protocol::Command::writeToDataStream(QDataStream& stream) const
{
}

void Epikon::Protocol::Hello::readFromDataStream(QDataStream& stream)
{
    Command::readFromDataStream(stream);
    stream >> m_id;
}

void Epikon::Protocol::Hello::writeToDataStream(QDataStream& stream) const
{
    Command::writeToDataStream(stream);
    stream << m_id;
}

void Epikon::Protocol::Attack::readFromDataStream(QDataStream& stream)
{
    Command::readFromDataStream(stream);
    stream >>  m_fromplanet >> m_toplanet >> m_fromplayer >> m_toplayer >> m_numships >>  m_sendtime;
}

void Epikon::Protocol::Attack::writeToDataStream(QDataStream& stream) const
{
    Command::writeToDataStream(stream);
    stream <<  m_fromplanet << m_toplanet << m_fromplayer << m_toplayer << m_numships <<  m_sendtime;
}

QDataStream & operator<< (QDataStream& stream, const Epikon::Protocol::CommandType& cmd){
    stream << (quint16&) cmd;
    return stream;
}

QDataStream & operator>> (QDataStream& stream, Epikon::Protocol::CommandType& cmd){
    stream >> (quint16&) cmd;
    return stream;
}

QDataStream & operator<< (QDataStream& stream, const Epikon::Protocol::Command& cmd){
    cmd.writeToDataStream(stream);
    return stream;
}

QDataStream & operator>> (QDataStream& stream, Epikon::Protocol::Command& cmd){
    return stream;
}
