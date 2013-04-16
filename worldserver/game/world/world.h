#ifndef WORLD_H
#define WORLD_H

#include <QtCore>
#include "worldserver.h"
#include "logs/log.h"
#include "configuration/configmgr.h"

class World
{
public:
    static World* Instance()
    {
        static QMutex mutex;
        if(!m_instance)
        {
            mutex.lock();
            m_instance = new World;
            mutex.unlock();
        }
        return m_instance;
    }

    static void Close()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_instance;
        mutex.unlock();
    }

    bool IsRunning() { return m_is_running; }
    bool StartServer();

private:
    World();
    ~World();

    static World* m_instance;

    WorldServer m_worldServer;
    bool m_is_running;
};

#endif
