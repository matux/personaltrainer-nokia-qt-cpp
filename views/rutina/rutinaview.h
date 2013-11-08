#ifndef RUTINAVIEW_H
#define RUTINAVIEW_H

#include <SIKit/SIKit.h>

#include <qmediaplayer.h>

class Routine;

class RutinaView : public SIView
{
    Q_OBJECT
public:
    explicit RutinaView(QWidget *parent = 0);
    virtual ~RutinaView();

signals:

private slots:
    void startPressed();
    void exerciseSelected(QListWidgetItem *);

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:
    SIButton *m_startButton;
    QLabel *m_labelPlan;
    QLabel *m_labelLevel;
    QLabel *m_labelRutina;
    QListWidget *m_listWidget;

    QMediaPlayer *player;

};

#endif // RUTINAVIEW_H
