#ifndef APPLICATIONLAUNCER_H
#define APPLICATIONLAUNCER_H

#include "appicon/applicationicon.h"
#include "i3ipc.h"

class ApplicationLauncer
{
public:
    ApplicationLauncer();
    static bool exec(QString cmd, bool terminal, i3::i3ipc* ipc);
};

#endif // APPLICATIONLAUNCER_H
