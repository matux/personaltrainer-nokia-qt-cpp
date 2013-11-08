#ifndef EXERCISES_H
#define EXERCISES_H

#include <QObject>
#include <QtXml>

class Exercise;

#include "SIKit/xml/siixmlhandlerdelegate.h"

class ExerciseManager : public QObject, public SIIXmlHandlerDelegate
{
    Q_OBJECT
public:
    static ExerciseManager &instance();

    inline QList<Exercise *> const &list() const { return m_exercises; }

    void load();
    void elementFound(QObject *element);

signals:

public slots:

private:
    ExerciseManager(QObject *parent = NULL);
    ExerciseManager(ExerciseManager const &, QObject *parent = NULL) {}
    ExerciseManager &operator =(ExerciseManager const &);
    ~ExerciseManager();

    QList<Exercise *> m_exercises;

};

#endif // EXERCISES_H
