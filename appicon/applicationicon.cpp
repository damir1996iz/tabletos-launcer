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
        applicationInfo.insert("Exec",str);

        QDirIterator it("/usr/share/icons",QStringList()<<(file.value("Icon").toString()+".*"),QDir::Files,QDirIterator::Subdirectories);
        str = "";
        while(it.hasNext())
        {
            str = it.filePath();
            if(str.contains("64x64"))
            {
                break;
            }
            it.next();
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

    QPixmap icon(applicationInfo["IconPath"]);
    lbl_icon->setPixmap(icon);

    layout->addWidget(lbl_icon);
    layout->addWidget(lbl_text);
}

void ApplicationIcon::mousePressEvent(QMouseEvent *event)
{
    clickTimer->start(2000);
}

void ApplicationIcon::mouseReleaseEvent(QMouseEvent *event)
{
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
