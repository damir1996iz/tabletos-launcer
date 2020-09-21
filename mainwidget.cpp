#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << this->height() << "::" << this->width();

    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    scrollArea = new QScrollArea(this);
    mainLayout->addWidget(scrollArea);
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollArea->setWidgetResizable( true );

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
    }
}

MainWidget::~MainWidget()
{
}

