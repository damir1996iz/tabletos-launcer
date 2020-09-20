#include "applicationlauncer.h"

ApplicationLauncer::ApplicationLauncer()
{

}

bool ApplicationLauncer::exec(QString cmd, bool terminal)
{
    if(terminal)
    {

    }
    else
    {
        QProcess::startDetached(cmd);
    }
}
