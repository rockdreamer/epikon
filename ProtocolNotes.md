# Introduction #

The interaction between two remote players happens through an intermediate server.

The server can be enabled on one of the player's clients but it can also be brought up on a standalone fashion.

Clients connect to the server and through this protocol obtain:
  * Lag time
  * Imperfect Authentication
  * Game and Player initiation
  * Game command exchange
  * (future) Chat messages

# Protocol Base Details #

The Protocol is a two way predefined message exchange mechanism based on the Qt class QDataStream.

Details on the QDataStream format can be found on the [Documentation Site](Qt.md)