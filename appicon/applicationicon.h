#ifndef APPLICATIONICON_H
#define APPLICATIONICON_H

#include <QSettings>
#include <QMap>
#include <QDirIterator>
#include <QDebug>
#include <QTimer>

#include <QtGui>
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>

class ApplicationIcon : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* layout;
    QLabel* lbl_icon;
    QLabel* lbl_text;

    QMap<QString,QString> applicationInfo;

    QTimer* clickTimer;
public:
    ApplicationIcon(QWidget *parent = nullptr);
    void loadIconInfoFromFile(QString filepath);
    void initIconAndText();
    QString getCommand();
    bool isTerminal();

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void slot_clickTimer(void);
signals:
    void clicked(ApplicationIcon* sender);
    void long_clicked(ApplicationIcon* sender);
};

#endif // APPLICATIONICON_H
