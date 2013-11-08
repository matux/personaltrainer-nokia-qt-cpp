#ifndef ROUTINEMANAGER_H
#define ROUTINEMANAGER_H

#include <QObject>
#include <QtXml>

class Plan;
class Routine;

class RoutineManager : public QObject
{
    Q_OBJECT
public:
    static RoutineManager &instance();

    inline QList<Plan *> &plans() { return m_plans; }

    Routine const &routine(int planIndex, int planLevel, int routineNumber);

    QString figureFilename(int exerciseId);
    QString levelName(int planIndex, int levelIndex);
    QString planName(int index);

    void load();

signals:

public slots:

private:
    RoutineManager(QObject *parent = NULL);
    RoutineManager(RoutineManager const &, QObject *parent = NULL) {}
    RoutineManager &operator =(RoutineManager const &);
    ~RoutineManager();

    QList<Plan *> m_plans;

};

#endif // ROUTINEMANAGER_H
