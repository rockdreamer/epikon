#ifndef EPIKONPROTOCOLCOMMAND_H
#define EPIKONPROTOCOLCOMMAND_H

#include <QDataStream>
#include <QTcpSocket>
#include <QTime>

namespace Epikon{
    namespace Protocol {
        enum CommandType{
            HELLO = 0,
            SERVERMESSAGE=1,
            ATTACK=10
        };

        class Command
        {
        public:
            inline Command(){};
            void sendToSocket(QTcpSocket* socket);
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
        protected:
            enum CommandType m_type;
        };

        class Hello: public Command
        {
        public:
            inline Hello(){};
            QString id() {return m_id;};
            void setId(const QString& id) {m_id=id;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;

        protected:
        private:
            QString m_id;
        };

        class Attack: public Command
        {
        public:
            inline Attack(){};
            quint16 fromPlanet(){return m_fromplanet;};
            quint16 toPlanet(){return m_toplanet;};
            quint16 fromPlayer(){return m_fromplayer;};
            quint16 toPlayer(){return m_toplayer;};
            quint16 numShips(){return m_numships;};
            QTime sendTime(){return m_sendtime;};
            void setFromPlanet( quint16 fromPlanet ){ m_fromplanet= fromPlanet;};
            void setToPlanet( quint16 toPlanet ){m_toplanet = toPlanet;};
            void setFromPlayer( quint16 fromPlayer ){m_fromplayer = fromPlayer;};
            void setNumShips( quint16 numShips ){ m_numships= numShips;};
            void setToPlayer( quint16 toPlayer ){m_toplayer = toPlayer;};

            void setSendTime(QTime sendTime){ m_sendtime= sendTime;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;

        protected:
        private:
            quint16 m_fromplanet,m_toplanet,m_fromplayer,m_toplayer,m_numships;
            QTime m_sendtime;
        };
    }
}
QDataStream & operator<< (QDataStream& stream, const Epikon::Protocol::CommandType& cmd);
QDataStream & operator>> (QDataStream& stream, Epikon::Protocol::CommandType& cmd);
QDataStream & operator<< (QDataStream& stream, const Epikon::Protocol::Command& cmd);
QDataStream & operator>> (QDataStream& stream, Epikon::Protocol::Command& cmd);
#endif // EPIKONPROTOCOLCOMMAND_H