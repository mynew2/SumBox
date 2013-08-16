#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "packets/worldpacket.h"
#include "databases/database.h"
#include "queues/worldqueue.h"
#include "define.h"
#include "servers/SocketReader.h"
#include "game/world/objects/Account.h"

class WorldPacket;

class WorldSession : private SocketReader
{
    Q_OBJECT
public:
    WorldSession(QTcpSocket* socket);
    ~WorldSession();

    QString GetIp() const
    {
        return m_socket->peerAddress().toString();
    }
    void SendPacket(WorldPacket packet);

    // Default handlers
    void HandleNULL(QString& /*packet*/) {}
    void HandleServerSide(QString& /*packet*/) {} // SMSG packets
    void HandleBeforeAuth(QString& /*packet*/) {} // CMSG packets before client auth (WorldSession don't exist at this moment)

    // Handlers
    void HandleQueue(QString& packet);
    void HandleTicketResponse(QString& packet);     // Vérifie la clé de connection et initialise les détails compte :
    void HandleRegionalVersion(QString& packet);    // ?
    void HandleListGifts(QString& packet);          // Gère la liste des cadeaux du compte. A faire
    void HandleKey(QString& packet);                // Stocke la clé de cryptage renseignée par le client
    void HandleCharactersList(QString& packet);     // Met en file d'attente :
    void HandleSendCharacterList(QString& packet);  // Gère la liste des personnages du serveur actuel
    void HandleRandomPseudo(QString& packet);       // Génère un pseudo aléatoire
    void HandleCreatePerso(QString& packet);        // Crée un nouveau perso

    void SendCharacterList();

public slots:
    void OnClose();

private:
    Account* m_account;
    ClientState m_state;
    QString m_ticket; // Avant connection

    virtual void ProcessPacket(QString packet);
};

#endif // WORLDSESSION_H
