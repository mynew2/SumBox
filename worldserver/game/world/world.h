#ifndef WORLD_H
#define WORLD_H

#include <QtCore>
#include "worldserver.h"
#include "logs/log.h"
#include "configuration/configmgr.h"
#include "utils/singleton.h"

class WorldSession;

struct sRaceStartInfos
{
    quint8 race;
    quint16 map_id;
    quint16 cell_id;
};

typedef QList<WorldSession*> SessionList;

class World : public Singleton<World>
{
public:
    World();
    ~World();

    bool Initialize();
    bool IsRunning() { return m_is_running; }

    void AddSession(WorldSession* session);
    void RemoveSession(WorldSession* session);

    void LoadRaceStartInfos();
    sRaceStartInfos GetRaceStartInfos(quint8 race);

private:
    bool m_is_running;
    SessionList m_sessions;
    QMap<quint8, sRaceStartInfos> m_raceStartInfos;
};

#endif
