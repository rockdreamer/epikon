#ifndef EPIKONPROTOCOLCOMMAND_H
#define EPIKONPROTOCOLCOMMAND_H

#include <QDataStream>
#include <QTcpSocket>
#include <QTime>

namespace Epikon{
    namespace Protocol {
        enum CommandType{
            /* First message */
            HELLO = 0,
            /* Notifications from server */
            SERVERMESSAGE=1,
            /* Game Handling: client requests new game*/
            CREATEGAME=2,
            /* Game Handling: client requests game list */
            GETGAMELIST=3,
            /* Game Handling: client requests to join an existing game */
            JOINGAME=4,
            /* Game Handling: server sends game definition to client */
            GAMEDEFINITION=5,
            /* User Handling: user data for game */
            GAMEUSER=6,
            /* User Handling: user picture definition */
            USERPICTURE=7,
            /* User Handling: user planet svg definition */
            USERPLANET=8,
            /* User Handling: user attack svg definition */
            USERATTACK=9,
            /* Game Handling: server sends data for the map */
            GAMEMAP=10,
            /* Game Handling: game is started */
            GAMESTART=11,
            /* Game Action: client attacks */
            ATTACK=12
        };

        class Command
        {
        public:
            inline Command():m_sendtime( QTime::currentTime ()),m_servertime(m_sendtime){};
            void sendToSocket(QTcpSocket* socket) const;
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
            QTime sendTime(){return m_sendtime;};
            void setSendTime(QTime sendTime){ m_sendtime= sendTime;};
            QTime serverTime(){return m_servertime;};
            void setServerTime(QTime serverTime){ m_servertime= serverTime;};

        protected:
            enum CommandType m_type;
            QTime m_sendtime, m_servertime;
        };

        class Hello: public Command
        {
        public:
            Hello(){m_type=HELLO;};
            QString id() {return m_id;};
            void setId(const QString& id) {m_id=id;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;

        protected:
        private:
            QString m_id;
        };

        class ServerMessage: public Command
        {
        public:
            ServerMessage(){m_type=SERVERMESSAGE;};
            QString text() {return m_text;};
            void setText(const QString& text) {m_text=text;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;

        protected:
        private:
            QString m_text;
        };

        class CreateGame: public Command
        {
        public:
            CreateGame(){m_type=CREATEGAME;};
            quint16 planets() {return m_planets;};
            void setPlanets(const quint16 planets) {m_planets=planets;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
        protected:
        private:
            quint16 m_planets;
        };

        class GetGameList: public Command
        {
        public:
            GetGameList(){m_type=GETGAMELIST;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
        protected:
        private:
        };

        class JoinGame: public Command
        {
        public:
            JoinGame(){m_type=JOINGAME;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
        protected:
        private:
        };

        class GameDefinition: public Command
        {
        public:
            GameDefinition(){m_type=GAMEDEFINITION;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
        protected:
        private:
        };

        class GameStart: public Command
        {
        public:
            GameStart(){m_type=GAMESTART;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
        protected:
        private:
        };

        class GameUser: public Command
        {
        public:
            GameUser(){m_type=GAMEUSER;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
        protected:
        private:
        };

        class UserPicture: public Command
        {
        public:
            UserPicture(){m_type=USERPICTURE;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
        protected:
        private:
        };

        class UserPlanet: public Command
        {
        public:
            UserPlanet(){m_type=USERPLANET;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
        protected:
        private:
        };

        class UserAttack: public Command
        {
        public:
            UserAttack(){m_type=USERATTACK;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
        protected:
        private:
        };

        class GameMap: public Command
        {
        public:
            GameMap(){m_type=GAMEMAP;};
            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;
        protected:
        private:
        };

        class Attack: public Command
        {
        public:
            Attack(){m_type=ATTACK;};
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

            virtual void readFromDataStream(QDataStream& stream);
            virtual void writeToDataStream(QDataStream& stream) const;

        protected:
        private:
            quint16 m_fromplanet,m_toplanet,m_fromplayer,m_toplayer,m_numships;

        };
    }
}
QDataStream & operator<< (QDataStream& stream, const enum Epikon::Protocol::CommandType& cmd);
QDataStream & operator>> (QDataStream& stream, enum Epikon::Protocol::CommandType& cmd);
QDataStream & operator<< (QDataStream& stream, const Epikon::Protocol::Command& cmd);
QDataStream & operator>> (QDataStream& stream, Epikon::Protocol::Command& cmd);
#endif // EPIKONPROTOCOLCOMMAND_H
