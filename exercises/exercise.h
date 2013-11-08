#ifndef EXERCISE_H
#define EXERCISE_H

#include <QtCore>

class Exercise : public QObject
{
    Q_OBJECT
public:
    explicit Exercise(QObject *parent = NULL);
    explicit Exercise(const QString &name, const QString &description, const QString &titleFilename, const QString &figureFilename, QObject *parent = NULL);
    virtual ~Exercise();

    // Getters
    inline QString const &name() const { return m_name; }
    inline QString const &description() const { return m_description; }
    inline QString const &titleFilename() const { return m_titleFilename; }
    inline QString const &figureFilename() const { return m_figureFilename; }
    inline int id() const { return m_id; }

    inline bool requiresGPS() const { return m_requiresGPS; }
    inline bool showsDistance() const { return m_showsDistance; }
    inline bool showsTime() const { return m_showsTime; }
    inline bool showsReps() const { return m_showsReps; }
    inline bool showsSteps() const { return m_showsSteps; }

    // Setters
    inline void setName(const QString &name) { m_name = name; }
    inline void setDescription(const QString &description) { m_description = description; }
    inline void setTitleFilename(const QString &titleFilename) { m_titleFilename = titleFilename; }
    inline void setFigureFilename(const QString &figureFilename) { m_figureFilename = figureFilename; }
    inline void setId(int id) { m_id = id; }

    inline void setProperties(const bool requiresGPS = true, const bool showsDistance = true,
                              const bool showsTime = true, const bool showsReps = false,
                              const bool showsSteps = false);
    inline void setRequiresGPS(const bool requiresGPS) { m_requiresGPS = requiresGPS; }
    inline void setShowsDistance(const bool showsDistance) { m_showsDistance = showsDistance; }
    inline void setShowsTime(const bool showsTime) { m_showsTime = showsTime; }
    inline void setShowsReps(const bool showsReps) { m_showsReps = showsReps; }
    inline void setShowsSteps(const bool showsSteps) { m_showsSteps = showsSteps; }

    void _print();

signals:

public slots:

private:
    int m_id;
    QString m_name;
    QString m_description;
    QString m_titleFilename;
    QString m_figureFilename;

    bool m_requiresGPS;
    bool m_showsDistance;
    bool m_showsTime;
    bool m_showsReps;
    bool m_showsSteps;

};

inline void Exercise::setProperties(const bool requiresGPS, const bool showsDistance,
                          const bool showsTime, const bool showsReps,
                          const bool showsSteps)
{
    setRequiresGPS(requiresGPS);
    setShowsDistance(showsDistance);
    setShowsTime(showsTime);
    setShowsReps(showsReps);
    setShowsSteps(showsSteps);
}

#endif // EXERCISE_H
