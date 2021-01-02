#ifndef APPLICATIONLAUNCER_H
#define APPLICATIONLAUNCER_H

#include "appicon/applicationicon.h"
#include "i3ipc.h"

class ApplicationLauncer
{
public:
    ApplicationLauncer();
    static bool exec(QString cmd, bool terminal, i3::i3ipc* ipc);
    static bool exec(QString cmd, bool terminal, i3::i3ipc* ipc, int num_of_workspace);
};

#endif // APPLICATIONLAUNCER_H
