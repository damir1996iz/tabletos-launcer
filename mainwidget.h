#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QProcess>
#include <QScrollArea>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QScroller>
#include <QMenu>

#include "i3ipc.h"
#include "appicon/applicationiconfactory.h"
#include "applauncer/applicationlauncer.h"
#include "workspaceswidget/workspaceswidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* mainLayout;
    QScrollArea* scrollArea;
    QWidget* innerWidget;
    QGridLayout* gridLayout;

    std::vector<std::unique_ptr<ApplicationIcon>> icons;
    ApplicationLauncer* launcher;
    WorkspacesWidget* widget;
    i3::i3ipc* ipc;

    std::unique_ptr<QMenu> popupMenu;
    QVector<QAction *> actions;
public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
public slots:
    void itemClicked(ApplicationIcon* icon);
    void itemLongClicked(ApplicationIcon* icon);
    void popupMenuClicked(int i);
};
#endif // MAINWIDGET_H
