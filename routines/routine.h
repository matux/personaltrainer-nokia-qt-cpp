#ifndef ROUTINE_H
#define ROUTINE_H

#include <QObject>

class RoutineElement;

class Routine : public QObject
{
    Q_OBJECT
public:
    explicit Routine(QObject *parent = 0);
    virtual ~Routine();

    int addExercise(RoutineElement *routineElement);
    inline RoutineElement const &exerciseAt(int i) const { return *(m_exerciseList.at(i)); }

    inline int exerciseCountWithoutComposition() const { return m_exerciseList.count(); }
    int exerciseCount() const;

    inline int id() const { return m_id; }
    inline void setId(const int id) { m_id = id; }

signals:

public slots:

private:
    int m_id;
    int m_cachedCount;

    void cacheExerciseCount();

    QList<RoutineElement *> m_exerciseList;

};

#endif // ROUTINE_H
