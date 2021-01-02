#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    ipc = new i3::i3ipc();

    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    scrollArea = new QScrollArea(this);
    mainLayout->addWidget(scrollArea);
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollArea->setWidgetResizable( true );
    QScroller::grabGesture(scrollArea, QScroller::LeftMouseButtonGesture);

    innerWidget = new QWidget();
    scrollArea->setWidget(innerWidget);

    gridLayout = new QGridLayout();
    innerWidget->setLayout(gridLayout);

    icons = ApplicationIconFactory::generateIcons("/usr/share/applications");
    auto i = 0;
    for(auto& item:icons)
    {
        item->initIconAndText();
        item->setParent(this);
        gridLayout->addWidget(item.get(),i/5,i%5);

        i++;

        connect(item.get(),SIGNAL(clicked(ApplicationIcon *)),this,SLOT(itemClicked(ApplicationIcon *)));
        connect(item.get(),SIGNAL(long_clicked(ApplicationIcon *)),this,SLOT(itemLongClicked(ApplicationIcon *)));
    }

    popupMenu = std::make_unique<QMenu>("Select Workspace menu", this);
    for(char i = 1;i<=10;i++)
    {
        QAction* tmp = new QAction("Open in workspace #"+ QString::number(i), this);
        connect(tmp,&QAction::triggered,this,[this,i]{popupMenuClicked(i);});
        actions.append(tmp);
    }

    for(auto &a:actions)
    {
        popupMenu->addAction(a);
    }
}

MainWidget::~MainWidget()
{
}

void MainWidget::itemClicked(ApplicationIcon *icon)
{
//    qDebug()<<"Start application:";
//    qDebug()<<icon->isTerminal();
//    qDebug()<<icon->getCommand();
    ApplicationLauncer::exec(icon->getCommand(),icon->isTerminal(),ipc);
}

void MainWidget::itemLongClicked(ApplicationIcon *icon)
{
    selectedIcon = icon;
    popupMenu->exec(mapToGlobal(cursor().pos()));
}

void MainWidget::popupMenuClicked(int i)
{
    ApplicationLauncer::exec(selectedIcon->getCommand(),selectedIcon->isTerminal(),ipc,i);
}

