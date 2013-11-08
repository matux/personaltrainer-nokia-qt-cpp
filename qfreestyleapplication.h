#ifndef QFREESTYLEAPPLICATION_H
#define QFREESTYLEAPPLICATION_H

#include <QApplication>
#include <QSymbianEvent>

class QFreestyleApplication : public QApplication
{
    Q_OBJECT
public:
    QFreestyleApplication(int &argc, char **argv);

#ifdef Q_OS_SYMBIAN
    bool symbianEventFilter(const QSymbianEvent *event);
#endif

    int start();

signals:

public slots:

};

#endif // QFREESTYLEAPPLICATION_H
