#ifndef TRAINERDETAILEDVIEW_H
#define TRAINERDETAILEDVIEW_H

#include <SIKit/SIKit.h>
#include <QWidget>

class Exercise;

class TrainerDetailedView : public SIView
{
    Q_OBJECT
public:
    explicit TrainerDetailedView(QWidget *parent = 0);
    explicit TrainerDetailedView(Exercise *exercise, QWidget *parent = 0);
    virtual ~TrainerDetailedView();

    //inline void setExercise(Exercise *exercise) { m_exercise = exercise; initDetail(); }
    inline Exercise const &exercise() const { return *m_exercise; }

signals:

public slots:

protected:
    void showEvent(QShowEvent *);

private:
    void initUi();
    void initDetail(QWidget *centralWidget);

    QWidget *m_centralWidget;

    Exercise *m_exercise;

};

#endif // TRAINERDETAILEDVIEW_H
