#ifndef I3IPC_H
#define I3IPC_H

#include <string>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>
#include <algorithm>
#include <regex>

#include <QDebug>
#include <QLocalSocket>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>

#include "json/json.hpp"

#include <i3/ipc.h>

class i3ipc: public QObject
{
    Q_OBJECT
private:
    QLocalSocket* socket;
public:
    i3ipc();
    QJsonObject read();
    void exec_command(QString command);
private slots:
    void slot_connected();
};

#endif // I3IPC_H
