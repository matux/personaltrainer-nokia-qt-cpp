#ifndef GEODISTANCECALC_H
#define GEODISTANCECALC_H

#include <QObject>

#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>
#include <QGeoSatelliteInfoSource>
#include <QGeoSatelliteInfo>
#include <QTimer>

#ifdef _DEVICE_BUILD
#define _ENABLE_LOCATION_API
#endif

using namespace QtMobility;

class GeoDistanceCalc : public QObject
{
    Q_OBJECT
public:
    static GeoDistanceCalc &instance();

    void startSilent();
    void resume();
    void start();
    void stop();
    void pause();
    void reset();
    void restart();

    inline qreal maxSpeed() const { return m_maxSpeed; }
    inline qreal currentSpeed() const { return m_speed; }
    inline qreal distanceInMeters() const { return m_distanceInMeters; }
    inline float distanceInKM() const { return (m_distanceInMeters / 1000.f); }

    double distanceTo(const QGeoCoordinate &from, const QGeoCoordinate &to);

    bool gpsAvailable();
    inline bool acquired() const { return m_acquired; }
    inline bool isPaused() const { return m_paused; }

signals:
    void gpsAcquired();
    void acquisitionTimedout();

private slots:
    void positionUpdated(const QGeoPositionInfo &geoPositionInfo);
    void satellitesUpdated(const QList<QGeoSatelliteInfo> &satellites);
    void positionUpdatedFake();
    void updateTimeout();

    void gpsAcquiredTimeout();

private:
    GeoDistanceCalc(QObject *parent = NULL);
    GeoDistanceCalc(GeoDistanceCalc const &, QObject *parent = NULL) {}
    GeoDistanceCalc &operator =(GeoDistanceCalc const &);
    ~GeoDistanceCalc();

    typedef enum _Method
    {
        STRAIGHT,
        DELAYED
    } Method;
    Method method;

    QGeoPositionInfoSource *m_geoPositionInfoSource;
    QGeoPositionInfo *lastGeoPositionInfo;
    QGeoSatelliteInfoSource *m_geoSatelliteInfoSource;
    QGeoSatelliteInfo *m_geoSatelliteInfo;
    QGeoCoordinate *sourceGeoCoordinate;
    QGeoCoordinate *snapshotGeoCoordinate;

    QTimer *m_fakeTimer;

    double m_accuracy;
    double m_maxSpeed;
    double m_speed;
    double m_distanceInMeters;
    int m_timeElapsedInSeconds;
    int m_timeElapsedInSecondsSinceSnapshot;
    int m_timeoutCounter;
    int m_satellitesInUse;
    bool m_firstSnapshot;

    bool m_started;
    bool m_paused;
    bool m_acquired;
    bool m_gpsAvailable;
    bool m_acquisitionTimedout;
    bool m_optimumSatelliteConnectionReached;
    bool m_satelliteWarningIssued;

    void startAcquisitionTimeout();
    void showMessage(const QString &msg);

    void _qDebug(const QString &);

};

#endif // GEODISTANCECALC_H
