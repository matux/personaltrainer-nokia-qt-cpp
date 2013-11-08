#ifndef ROUTINEELEMENT_H
#define ROUTINEELEMENT_H

#include <QObject>

class RoutineElement : public QObject
{
    Q_OBJECT
public:
    explicit RoutineElement(QObject *parent = 0);
    virtual ~RoutineElement() = 0;

    virtual QString const type() const = 0;
    virtual QString const name() const = 0;

    inline int id() const { return m_id; }
    inline void setId(const int id) { m_id = id; }

signals:

public slots:

private:
    int m_id;

};

#endif // ROUTINEELEMENT_H
