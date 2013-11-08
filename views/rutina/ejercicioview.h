#ifndef EJERCICIOVIEW_H
#define EJERCICIOVIEW_H

#include <SIKit/SIKit.h>

class HeaderView;
class RoutineExercise;
class RoutineExerciseComposition;

class EjercicioView : public SIView
{
    Q_OBJECT
public:
    explicit EjercicioView(int exerciseNumber, bool autoInitUi = true, QWidget *parent = 0);
    virtual ~EjercicioView();

    void initUi();
    void initControlPanel();

    inline void setPasadaNumber(int n) { m_pasadaNumber = n; }
    inline void setSubExerciseNumber(int n) { m_subExerciseNumber = n; }
    inline void setRoutineComposition(const RoutineExerciseComposition *routineComposition) { m_routineComposition = routineComposition; }
    inline void setSessionChronometer(const QTime &chronometer) { m_sessionChronometer = chronometer; }

signals:

private slots:
    void startPressed();
    void pausePressed();

    void figurePressed();

    void nextExercise();

    void timerShowFinishedButton();
    void timerUpdated();
    void sessionTimerUpdated();
    void gpsTimerCheck();

    void reachedEndOfMedia();

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QShowEvent *);

private:
    void destroyTimer();
    void destroySessionTimer();

    int m_exerciseNumber;
    int m_subExerciseNumber;
    int m_pasadaNumber;
    const RoutineExercise *m_routineExercise;
    const RoutineExerciseComposition *m_routineComposition;

    SIButton *m_startButton;
    SIButton *m_pauseButton;
    SIButton *m_finishedButton;

    QLabel *m_labelPanel;
    QLabel *m_labelDistanceLabel;
    QLabel *m_labelDistance;
    QLabel *m_labelTimeLabel;
    QLabel *m_labelTime;
    QLabel *m_labelRepsLabel;
    QLabel *m_labelReps;
    QLabel *m_labelSessionTimeLabel;
    QLabel *m_labelSessionTime;
    QLabel *m_labelStepsLabel;
    QLabel *m_labelSteps;
    QLabel *m_labelGPS;

    QTimer *m_counterTimer;
    QTimer *m_sessionTimer;
    QTimer *m_finishedButtonTimer;
    QTime m_startSnapshotTime;
    QTime m_sessionSnapshotTime;
    QTime m_chronometer;
    QTime m_sessionChronometer;

    bool m_willShowFinishedButton;
    bool m_countSessionTime;
    int m_fireNextPhraseTime;
    int m_voxStep;

    QMutex mutex;
};

#endif // EJERCICIOVIEW_H
