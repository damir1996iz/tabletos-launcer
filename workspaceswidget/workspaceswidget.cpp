#include "workspaceswidget.h"

WorkspacesWidget::WorkspacesWidget(i3::i3ipc* ipc,QWidget *parent) : QWidget(parent)
{
    gridLayout = new QGridLayout();
    setLayout(gridLayout);

    auto Tree = ipc->getTree();

    int i = 0;
    for(auto& w:Tree)
    {
        QListWidget *lst = new QListWidget();
        lst->addItems(w.applictionTitles);
        gridLayout->addWidget(lst,i%2,i/2);
        i++;
    }
}
