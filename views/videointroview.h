#ifndef VIDEOINTROVIEW_H
#define VIDEOINTROVIEW_H

#include <SIKit/SIKit.h>

class VideoIntroView : public SIView
{
    Q_OBJECT
public:
    explicit VideoIntroView(QWidget *parent = 0);
    virtual ~VideoIntroView();

    void introVideoEnded();

signals:

public slots:

};

#endif // VIDEOINTROVIEW_H
