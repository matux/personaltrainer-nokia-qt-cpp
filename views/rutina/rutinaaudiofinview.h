#ifndef RUTINAAUDIOFINVIEW_H
#define RUTINAAUDIOFINVIEW_H

#include <SIKit/SIKit.h>

#include <qmediaplayer.h>

class RutinaAudioFinView : public SIView
{
    Q_OBJECT
public:
    explicit RutinaAudioFinView(QWidget *parent = 0);
    virtual ~RutinaAudioFinView();

    QTime *sessionTime;

signals:

private slots:
    void endRoutine();

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:
    QMediaPlayer *player;

    bool m_showLevelEnd;
    bool m_showPlanEnd;
};

#endif // RUTINAAUDIOFINVIEW_H
