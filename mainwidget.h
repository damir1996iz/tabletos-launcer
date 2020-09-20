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

#include "i3ipc.h"
#include "appicon/applicationiconfactory.h"

class MainWidget : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* mainLayout;
    QScrollArea* scrollArea;
    QWidget* innerWidget;
    QGridLayout* gridLayout;

    std::vector<std::unique_ptr<ApplicationIcon>> icons;
public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
};
#endif // MAINWIDGET_H
