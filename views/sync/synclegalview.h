#ifndef SYNCLEGALVIEW_H
#define SYNCLEGALVIEW_H

#include <SIKit/SIKit.h>

class SyncLegalView : public SIView
{
    Q_OBJECT
public:
    explicit SyncLegalView(QWidget *parent = 0);
    virtual ~SyncLegalView();

signals:

public slots:
    void acceptPressed();

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

};

#endif // SYNCLEGALVIEW_H
