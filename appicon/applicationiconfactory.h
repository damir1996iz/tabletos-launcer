#ifndef APPLICATIONICONFACTORY_H
#define APPLICATIONICONFACTORY_H

#include "applicationicon.h"
#include <vector>
#include <memory>

class ApplicationIconFactory
{
public:
    ApplicationIconFactory();
    static std::vector<std::unique_ptr<ApplicationIcon>> generateIcons(QString path);
};

#endif // APPLICATIONICONFACTORY_H
