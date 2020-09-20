#ifndef APPLICATIONLAUNCER_H
#define APPLICATIONLAUNCER_H

#include "appicon/applicationicon.h"

class ApplicationLauncer
{
public:
    ApplicationLauncer();
    static bool exec(QString cmd,bool terminal);
};

#endif // APPLICATIONLAUNCER_H
