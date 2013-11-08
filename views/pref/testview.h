#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <SIKit/SIKit.h>

class HeaderView;

class TestView : public SIView
{
    Q_OBJECT
public:
    explicit TestView(QWidget *parent = 0);
    virtual ~TestView();

    inline void setHeaderView(HeaderView *headerView) { m_headerView = headerView; }

signals:

private slots:
    void startPressed();
    void pausePressed();
    void skipPressed();

    void timerUpdated();
    void gpsTimerCheck();

protected:
    void showEvent(QShowEvent *);

private:
    void destroyTimer();

    HeaderView *m_headerView;

    SIButton *m_startButton;
    SIButton *m_pauseButton;

    QLabel *m_labelDistance;
    QLabel *m_labelTime;
    QLabel *m_labelGPS;

    QTimer *m_counterTimer;
    QTime m_startSnapshotTime;
    QTime m_chronometer;

    int m_fireNextPhraseTime;
    bool m_firstTime;
    bool m_showTestMessage;

};

#endif // TESTVIEW_H
