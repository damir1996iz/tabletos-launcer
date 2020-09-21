#include "applicationlauncer.h"

ApplicationLauncer::ApplicationLauncer()
{

}

bool ApplicationLauncer::exec(QString cmd, bool terminal)
{
    if(terminal)
    {
        return QProcess::startDetached("xtrerm "+cmd, QStringList()<<"");
    }
    else
    {
        return QProcess::startDetached(cmd, QStringList()<<"");
    }
}
