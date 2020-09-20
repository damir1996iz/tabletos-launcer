#include "i3ipc.h"

std::string get_i3socket(void)
{
    std::array<char,128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> file(popen("i3 --get-socketpath", "r"), pclose);
    if(file == nullptr)
    {
        qDebug() <<"Error";
    }
    while (fgets(buffer.data(), buffer.size(), file.get()) != nullptr) {
            result += buffer.data();
    }
    result.erase(std::remove(result.begin(),result.end(),'\n'),result.end());
    return result;
}

i3ipc::i3ipc()
{
    socket = new QLocalSocket();

    QObject::connect(socket,SIGNAL(connected()),this,SLOT(slot_connected()));
    socket->connectToServer(QString::fromStdString(get_i3socket()));

    socket->waitForConnected();
}

void i3ipc::exec_command(QString command)
{
    if (socket->bytesAvailable() > 0)
    {
        socket->readAll();
    }
    QByteArray b;
    QDataStream s(&b, QIODevice::WriteOnly);
    s.setByteOrder(QDataStream::LittleEndian);

    s.writeRawData(I3_IPC_MAGIC, qstrlen(I3_IPC_MAGIC));
    s << (quint32) command.size();
    s << (quint32) I3_IPC_MESSAGE_TYPE_RUN_COMMAND;
    s.writeRawData(command.toLocal8Bit().data(), command.size());

    socket->write(b);
    socket->waitForBytesWritten();

    socket->waitForReadyRead();

    QByteArray answer;
    if (socket->bytesAvailable() > 0)
    {
        answer = socket->readAll();
    }
    answer.remove(0,14);
//TODO:
    auto str = static_cast<std::string>(answer);
    str.erase(std::remove(str.begin(), str.end(), '['), str.end());
    str.erase(std::remove(str.begin(), str.end(), ']'), str.end());
    auto reply = nlohmann::json::parse(str);
    auto t = static_cast<bool>(reply["success"]);
}

QJsonObject i3ipc::read()
{
    return (*(new QJsonObject()));
}

void i3ipc::slot_connected()
{
    qDebug()<<"Connected";
}
