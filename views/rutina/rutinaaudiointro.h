#ifndef RUTINAAUDIOINTRO_H
#define RUTINAAUDIOINTRO_H

#include <SIKit/SIKit.h>

#include <qmediaplayer.h>

class RutinaAudioIntro : public SIView
{
    Q_OBJECT
public:
    explicit RutinaAudioIntro(QWidget *parent = 0);
    virtual ~RutinaAudioIntro();

signals:

private slots:
    void startRoutine();
    void reachedEndOfMedia();

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:
    int m_voxStep;

    QMediaPlayer *player;

};

#endif // RUTINAAUDIOINTRO_H
