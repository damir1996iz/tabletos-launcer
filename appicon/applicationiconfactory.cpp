#include "applicationiconfactory.h"

ApplicationIconFactory::ApplicationIconFactory()
{

}

std::vector<std::unique_ptr<ApplicationIcon>> ApplicationIconFactory::generateIcons(QString path)
{
    std::vector<std::unique_ptr<ApplicationIcon>> result;
    QDirIterator it(path,QDir::Files);
    while(it.hasNext())
    {
        if(!it.filePath().contains(".desktop"))
        {
            it.next();
            continue;
        }
        auto appIcon = std::make_unique<ApplicationIcon>();
        appIcon->loadIconInfoFromFile(it.filePath());
        result.push_back(std::move(appIcon));
        it.next();
    }
    return result;
}

