#ifndef LISTWIDGETITEMWITHROUTINE_H
#define LISTWIDGETITEMWITHROUTINE_H

#include <QListWidgetItem>
#include "model/routines/routineelement.h"

class ListWidgetItemWithRoutine : public QListWidgetItem
{
public:
    explicit ListWidgetItemWithRoutine(QListWidget *view = 0);

    inline RoutineElement const &routineElement() const { return *m_routineElement; }
    inline void setRoutineElement(const RoutineElement &element) { m_routineElement = &element; }

signals:

public slots:

private:
    const RoutineElement *m_routineElement;

};

#endif // LISTWIDGETITEMWITHROUTINE_H
