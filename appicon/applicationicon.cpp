#include "applicationicon.h"

ApplicationIcon::ApplicationIcon(QWidget *parent) : QWidget(parent)
{
    clickTimer = new QTimer();
    connect(clickTimer,SIGNAL(timeout()),this,SLOT(slot_clickTimer()));
}

void ApplicationIcon::loadIconInfoFromFile(QString filepath)
{
    QSettings file(filepath,QSettings::IniFormat);
    file.beginGroup("Desktop Entry");
        applicationInfo.insert("Name",file.value("Name").toString());

        auto str = file.value("Exec").toString();
        str.remove(QRegExp(" %."));
        auto exec_cmds = str.split(" ");
        applicationInfo.insert("Exec",exec_cmds[0]);
        str = str.remove(exec_cmds[0]+" ");
        applicationInfo.insert("Args",str);

        QDirIterator it("/usr/share/icons",QStringList()<<(file.value("Icon").toString()+".*"),QDir::Files,QDirIterator::Subdirectories);
        icons.clear();
        while(it.hasNext())
        {
            if(!it.filePath().isEmpty())
                icons.append(it.filePath());
            it.next();
        }

        if(icons.empty())
        {
            //TODO: Add empty icon
            icons.append("/usr/share/icons/hicolor/64x64/apps/software-properties.png");
        }

        applicationInfo.insert("IconPath",str);

        applicationInfo.insert("Terminal",file.value("Terminal").toString());

        file.endGroup();
}

void ApplicationIcon::initIconAndText()
{
    layout = new QVBoxLayout();

    this->setLayout(layout);
    this->setFixedSize(80,150);

    lbl_text = new QLabel();
    lbl_text->setFixedSize(80,86);
    lbl_text->setText(applicationInfo["Name"]);
    lbl_text->setWordWrap(true);
    lbl_text->setAlignment(Qt::AlignHCenter);

    lbl_icon = new QLabel();
    lbl_icon->setFixedSize(80,64);
    lbl_icon->setAlignment(Qt::AlignHCenter);

    auto icon_pth = std::find_if (icons.begin(),icons.end(),[](QString s){return s.contains("64x64");});
    if(icon_pth != icons.end())
    {
        QPixmap icon(*icon_pth);
        lbl_icon->setPixmap(icon);
    }
    else
    {
        QPixmap icon(icons[0]);
        lbl_icon->setPixmap(icon.scaled(64,64,Qt::KeepAspectRatio));
    }

    layout->addWidget(lbl_icon);
    layout->addWidget(lbl_text);
}

QString ApplicationIcon::getCommand()
{
    return applicationInfo["Exec"];
}

bool ApplicationIcon::isTerminal()
{
    return applicationInfo["Terminal"]=="true"?true:false;
}

QStringList ApplicationIcon::getArgs()
{
    return applicationInfo["Args"].split(" ");
}

void ApplicationIcon::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    clickTimer->start(2000);
}

void ApplicationIcon::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);

    if(clickTimer->isActive())
    {
        clickTimer->stop();
        emit clicked(this);
    }
}

void ApplicationIcon::slot_clickTimer()
{
    clickTimer->stop();
    emit long_clicked(this);
}
