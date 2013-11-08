#ifndef SIACTIVITYINDICATOR_H
#define SIACTIVITYINDICATOR_H

#include <SIKit/SIView.h>
#include <QLabel>
#include <QMovie>

class SIActivityIndicator : public SIView
{
    Q_OBJECT
public:
    explicit SIActivityIndicator(const QString &animationPath, QWidget *parent = 0);
    explicit SIActivityIndicator(const QString &animationPath, QSize size, QWidget *parent = 0);
    virtual ~SIActivityIndicator();

signals:

public slots:
    void start();
    void stop();

private:
    QPointer<QLabel> m_container;
    QPointer<QMovie> m_animation;

    void init(const QString &animationPath, const QSize &size);

};

#endif // SIACTIVITYINDICATOR_H
