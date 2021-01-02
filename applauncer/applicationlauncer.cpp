#include "applicationlauncer.h"

ApplicationLauncer::ApplicationLauncer()
{

}

bool ApplicationLauncer::exec(QString cmd, bool terminal, i3::i3ipc* ipc)
{
    auto workspaces = ipc->getTree();
    auto w = i3::workspace::find_minapps(workspaces);
    ipc->exec_command("workspace "+w.name);

    if(terminal)
    {
        return QProcess::startDetached("xterm", QStringList()<< cmd);
    }
    else
    {
        return QProcess::startDetached(cmd, QStringList()<<"");
    }
}

bool ApplicationLauncer::exec(QString cmd, bool terminal, i3::i3ipc* ipc, int num_of_workspace)
{
    ipc->exec_command("workspace "+QString::number(num_of_workspace));

    if(terminal)
    {
        return QProcess::startDetached("xterm", QStringList()<< cmd);
    }
    else
    {
        return QProcess::startDetached(cmd, QStringList()<<"");
    }
}


