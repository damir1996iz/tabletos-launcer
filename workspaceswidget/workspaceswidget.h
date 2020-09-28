#ifndef WORKSPACESWIDGET_H
#define WORKSPACESWIDGET_H

#include "i3ipc.h"

#include <QWidget>
#include <QListWidget>
#include <QGridLayout>

#include <QDebug>
#include <memory>

class WorkspacesWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout* gridLayout;

    QList<std::unique_ptr<QListWidget>> WorkspaceViews;
public:
    QWidget* backWidget;
    i3::i3ipc* i3ipc;

    explicit WorkspacesWidget(i3::i3ipc* ipc, QWidget *parent = nullptr);
signals:

};

#endif // WORKSPACESWIDGET_H
