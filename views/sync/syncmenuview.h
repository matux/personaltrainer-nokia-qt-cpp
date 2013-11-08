#ifndef SYNCMENUVIEW_H
#define SYNCMENUVIEW_H

#include <SIKit/SIKit.h>

class SyncMenuView : public SIView
{
    Q_OBJECT
public:
    explicit SyncMenuView(QWidget *parent = 0);
    virtual ~SyncMenuView();

signals:

public slots:
    void showLegal();
    void acceptPressed();

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

};

#endif // SYNCMENUVIEW_H
