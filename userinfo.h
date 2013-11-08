#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>
#include <QMap>

class QSettings;
class Routine;

class UserInfo : public QObject
{
    Q_OBJECT
public:
    enum Gender {
        G_MALE,
        G_FEMALE,
    };
    enum Level {
        L_BEGINNER,
        L_INTERMEDIATE,
        L_ADVANCED
    };

public:
    explicit UserInfo(QObject *parent = 0);

    void loadFromSettings(const QSettings &settings);
    void saveToSettings(QSettings &settings) const;

    Level resolveLevel() const;
    QString levelStr() const;
    QString planName() const;
    QString objectiveStr() const;
    QString homeTownKey() const;
    Routine const &currentRoutine() const;

    inline QMap<QString, int> &townMap() { return m_townMap; }

    inline QString const &fullName() const { return m_fullName; }
    inline QString const &eMail() const { return m_eMail; }
    inline QString const &homeTown() const { return m_homeTown; }
    inline QString const &weight() const { return m_weight; }
    inline QString const &height() const { return m_height; }
    inline QString const &password() const { return m_password; }
    inline int age() const { return m_age; }
    inline Gender gender() const { return m_gender; }
    inline int objectiveIndex() const { return m_objectiveIndex; }
    inline int metersCoveredInTest() const { return m_metersCoveredInTest; }
    inline int currentRoutineNumber(int plan) const { return m_currentRoutineNumber[plan]; }
    inline Level level(int plan) const { return m_currentLevel[plan]; }

    inline void setFullName(const QString &fullName) { m_fullName = fullName; }
    inline void setEMail(const QString &eMail) { m_eMail = eMail; }
    inline void setHomeTown(const QString &homeTown) { m_homeTown = homeTown; }
    inline void setWeight(const QString &weight) { m_weight = weight; }
    inline void setHeight(const QString &height) { m_height = height; }
    inline void setPassword(const QString &password) { m_password = password; }
    inline void setAge(int age) { m_age = age; }
    inline void setGender(Gender gender) { m_gender = gender; }
    inline void setObjectiveIndex(int objectiveIndex) { m_objectiveIndex = objectiveIndex; }
    inline void setMetersCoveredInTest(int metersCoveredInTest) { m_metersCoveredInTest = metersCoveredInTest; }
    inline void setCurrentRoutineNumber(int plan, int currentRoutineNumber) { m_currentRoutineNumber[plan] = currentRoutineNumber; }
    inline void setLevel(int plan, Level level) { m_currentLevel[plan] = level; }

    void resetRoutines();

    void _print();

signals:

public slots:

private:
    QString m_fullName;
    QString m_eMail;
    QString m_homeTown;
    QString m_weight;
    QString m_height;
    QString m_mail;
    QString m_password;
    int m_age;
    Gender m_gender;
    int m_objectiveIndex;
    int m_metersCoveredInTest;
    int m_currentRoutineNumber[4];
    Level m_currentLevel[4];

    QMap<QString, int> m_townMap;

};

#endif // USERINFO_H
