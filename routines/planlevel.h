#ifndef PLANLEVEL_H
#define PLANLEVEL_H

#include <QObject>

class Routine;

class PlanLevel : public QObject
{
    Q_OBJECT
public:
    explicit PlanLevel(QObject *parent = 0);
    virtual ~PlanLevel();

    int addRoutine(Routine *routine);
    inline Routine const &routineAt(int i) const { return *(m_routineList.at(i)); }
    inline int const routineCount() const { return m_routineList.count(); }

    inline QString const name() const { return m_name; }
    inline void setName(const QString &name) { m_name = name; }

signals:

public slots:

private:
    QString m_name;

    QList<Routine *> m_routineList;

};

#endif // PLANLEVEL_H
