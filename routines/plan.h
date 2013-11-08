#ifndef PLAN_H
#define PLAN_H

#include <QObject>

class PlanLevel;

class Plan : public QObject
{
    Q_OBJECT
public:
    explicit Plan(QObject *parent = 0);
    virtual ~Plan();

    inline PlanLevel const &beginnerLevel() const { return *m_beginnerLevel; }
    inline PlanLevel const &intermediateLevel() const { return *m_intermediateLevel; }
    inline PlanLevel const &advancedLevel() const { return *m_advancedLevel; }

    PlanLevel const &levelAt(int index) const;

    void setBeginnerLevel(PlanLevel *beginnerLevel);
    void setIntermediateLevel(PlanLevel *intermediateLevel);
    void setAdvancedLevel(PlanLevel *advancedLevel);

    inline bool hasBeginnerLevel() const { return m_beginnerLevel != NULL; }
    inline bool hasIntermediateLevel() const { return m_intermediateLevel != NULL; }
    inline bool hasAdvancedLevel() const { return m_advancedLevel != NULL; }

    inline QString const name() const { return m_name; }
    inline void setName(const QString &name) { m_name = name; }

signals:

public slots:

private:
    QString m_name;

    PlanLevel *m_beginnerLevel;
    PlanLevel *m_intermediateLevel;
    PlanLevel *m_advancedLevel;

};

#endif // PLAN_H
