#ifndef SYNCVIEW_H
#define SYNCVIEW_H

#include <SIKit/SIKit.h>

class SyncView : public SIView
{
    Q_OBJECT
public:
    explicit SyncView(QWidget *parent = 0);
    virtual ~SyncView();

signals:

public slots:
    void skipPressed();

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:
    void showMessage(const QString &msg);

};

#endif // SYNCVIEW_H
