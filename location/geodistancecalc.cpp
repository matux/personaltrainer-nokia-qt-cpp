#include "geodistancecalc.h"
#include "mainwindow.h"

#include <QtGui>
#include <iostream>

#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double deg2rad(double deg)
{
  return (deg * M_PI / 180);
}
double rad2deg(double rad)
{
  return (rad * 180 / M_PI);
}


GeoDistanceCalc &GeoDistanceCalc::instance()
{
    static GeoDistanceCalc theInstance;
    return theInstance;
}

GeoDistanceCalc::GeoDistanceCalc(QObject *parent)
    :QObject(parent),
    m_geoPositionInfoSource(NULL),
    lastGeoPositionInfo(NULL),
    sourceGeoCoordinate(NULL),
    snapshotGeoCoordinate(NULL),
    m_fakeTimer(NULL),
    m_distanceInMeters(0),
    m_timeElapsedInSecondsSinceSnapshot(0),
    m_started(false),
    m_paused(false),
    m_acquired(false)
{
    m_satellitesInUse = 0;
    m_optimumSatelliteConnectionReached = false;
    m_satelliteWarningIssued = false;
    m_gpsAvailable = true;
    m_firstSnapshot = false;
    m_acquisitionTimedout = false;
    m_maxSpeed = 0;
    m_timeoutCounter = 0;

    //method = GeoDistanceCalc::DELAYED;
    method = GeoDistanceCalc::STRAIGHT;

#ifdef _DEBUG
    qDebug("DEBUG MODE");
#else
    qDebug("NOT DEBUG MODE");
#endif

#ifdef _RELEASE
    qDebug("RELEASE MODE");
#else
    qDebug("NOT RELEASE MODE");
#endif

    qDebug("Creating GeoDistanceCalc...");
#ifdef _ENABLE_LOCATION_API
    qDebug("GeoDistanceCalc::_ENABLE_LOCATION_API set");
    m_geoPositionInfoSource = QGeoPositionInfoSource::createDefaultSource(this);
    m_geoSatelliteInfoSource = QGeoSatelliteInfoSource::createDefaultSource(this);
#else
    m_geoPositionInfoSource = NULL;
    m_geoSatelliteInfoSource = NULL;
#endif
#ifdef _FAKE_LOCATION_API
    qDebug("GeoDistanceCalc::_FAKE_LOCATION_API set");
#endif

    qDebug("m_geoPositionInfoSource is %p", m_geoPositionInfoSource);

    if( m_geoPositionInfoSource )
    {
        qDebug("m_geoPositionInfoSource is valid");
#ifdef _ENABLE_LOCATION_API
        m_geoPositionInfoSource->setUpdateInterval(2000); // time in milliseconds
        m_geoPositionInfoSource->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        connect(m_geoPositionInfoSource, SIGNAL(updateTimeout()), this, SLOT(updateTimeout()));
        m_geoSatelliteInfoSource->startUpdates();
        connect(m_geoSatelliteInfoSource, SIGNAL(satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &)), this, SLOT(satellitesUpdated(const QList<QGeoSatelliteInfo> &)));
#endif

        reset();
        startSilent();

        qDebug("Creating GeoDistanceCalc... Done!");
    }
    else
    {
#ifdef _FAKE_LOCATION_API
        qDebug("Creating GeoDistanceCalc... NOT VALID! --> We will fake the info!");

        m_fakeTimer = new QTimer();
        if( method == GeoDistanceCalc::STRAIGHT )
            m_fakeTimer->setInterval(2000); // 2 seconds
        else if( method == GeoDistanceCalc::DELAYED )
            m_fakeTimer->setInterval(20000); // 20 seconds
        m_fakeTimer->setSingleShot(false);
        connect(m_fakeTimer, SIGNAL(timeout()), this, SLOT(positionUpdatedFake()));

        reset();
        startSilent();

        return;
#endif

    }

    startAcquisitionTimeout();
}

GeoDistanceCalc::~GeoDistanceCalc()
{

}

void GeoDistanceCalc::startAcquisitionTimeout()
{
    QTimer *gpsAcquiredTimer = new QTimer();
    //gpsAcquiredTimer->setInterval(5000); // 5 seconds
    //gpsAcquiredTimer->setInterval(300000); // 5 minutes
    gpsAcquiredTimer->setInterval(120000); // 2 minutes
    gpsAcquiredTimer->setSingleShot(true);
    gpsAcquiredTimer->start();
    connect(gpsAcquiredTimer, SIGNAL(timeout()), this, SLOT(gpsAcquiredTimeout()));

}

void GeoDistanceCalc::startSilent()
{
    if( m_started ) return;

    qDebug("GeoDistanceCalc::startSilent()");
    if( !m_geoPositionInfoSource )
    {
#ifdef _FAKE_LOCATION_API
        m_fakeTimer->start();
#endif
    }
    else
    {
#ifdef _ENABLE_LOCATION_API
        m_geoPositionInfoSource->startUpdates();
        connect(m_geoPositionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));
#endif
    }

    m_started = true;
    pause();

}

void GeoDistanceCalc::resume()
{
    qDebug("GeoDistanceCalc::start()");
    m_paused = false;
}

void GeoDistanceCalc::start()
{
    qDebug("GeoDistanceCalc::start()");
    reset();

    if( !m_started )
        startSilent();

    m_paused = false;

}

void GeoDistanceCalc::stop()
{
    qDebug("GeoDistanceCalc::stop()");
    if( !m_geoPositionInfoSource )
    {
#ifdef _FAKE_LOCATION_API
        if( m_fakeTimer )
            m_fakeTimer->stop();
#endif
    }
    else
    {
#ifdef _ENABLE_LOCATION_API
        m_geoPositionInfoSource->stopUpdates();
        disconnect(m_geoPositionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));
#endif
    }

    m_started = false;
    m_paused = false;

}

void GeoDistanceCalc::pause()
{
    qDebug("GeoDistanceCalc::pause()");
    m_paused = true;
}

void GeoDistanceCalc::reset()
{
    qDebug("GeoDistanceCalc::reset()");
    m_distanceInMeters = 0;
    m_maxSpeed = 0;
    m_timeElapsedInSeconds = 0;
    m_timeElapsedInSecondsSinceSnapshot = 0;
#ifdef _ENABLE_LOCATION_API
    delete snapshotGeoCoordinate;
    delete lastGeoPositionInfo;
    snapshotGeoCoordinate = NULL;
    lastGeoPositionInfo = NULL;
#endif
}

void GeoDistanceCalc::restart()
{
    qDebug("GeoDistanceCalc::restart()");
    stop();
    reset();
    startSilent();
    start();
}

double GeoDistanceCalc::distanceTo(const QGeoCoordinate &from, const QGeoCoordinate &to)
{
#ifdef _ENABLE_LOCATION_API
    double R = 6371; // 3960 for miles
    double latd = deg2rad(to.latitude() - from.latitude());
    double lond = deg2rad(to.longitude() - from.longitude());
    double a = sin(latd / 2.f) * sin(latd / 2.f) +
               cos(deg2rad(from.latitude())) * cos(deg2rad(to.latitude())) *
               sin(lond / 2.f) * sin(lond / 2.f);
    double c = 2.f * asin(std::min((double)1.f, sqrt(a)));
    double d = R * c;

    return d * 1000.f;
#else
    return 0.f;
#endif
}

void GeoDistanceCalc::satellitesUpdated(const QList<QGeoSatelliteInfo> &satellites)
{
    m_satellitesInUse = satellites.count();

    //std::cout << "satellites updated with count " << m_satellitesInUse << std::endl;

    if( m_optimumSatelliteConnectionReached )
    {
        if( m_satellitesInUse < 4 )
        {
            if( !m_satelliteWarningIssued )
                showMessage("Baja señal de satélite.");
            m_satelliteWarningIssued = true;
            m_optimumSatelliteConnectionReached = false;
        }
    }
    else
    {
        if( m_satellitesInUse >= 4 )
            m_optimumSatelliteConnectionReached = true;
    }

}

void GeoDistanceCalc::positionUpdatedFake()
{
    //qDebug("positionUpdatedFake(), isPaused: %d", (int)m_paused);

    if( !m_acquired )
        emit gpsAcquired();

    m_acquired = true;
    m_gpsAvailable = true;
    m_acquisitionTimedout = false;

    m_timeoutCounter = 0;

    if( !m_paused )
    {
        m_speed = 4;
        m_maxSpeed = m_speed;
        if( method == GeoDistanceCalc::STRAIGHT )
            m_distanceInMeters += m_speed;
        else if( method == GeoDistanceCalc::DELAYED )
            m_distanceInMeters += m_speed * 10;
    }

}

void GeoDistanceCalc::positionUpdated(const QGeoPositionInfo &geoPositionInfo)
{
#ifdef _ENABLE_LOCATION_API
    //qDebug("GeoDistanceCalc::positionUpdated");

    m_timeoutCounter = 0;

    if( !m_acquired )
        emit gpsAcquired();

    m_acquired = true;
    m_gpsAvailable = true;
    m_acquisitionTimedout = false;

    if( !m_geoPositionInfoSource ) return;

    if( !geoPositionInfo.isValid() /*|| m_paused*/ )
    {
        if( !geoPositionInfo.isValid() )
            qDebug("geoPositionInfo is invalid");
        //if( m_paused )
        //    qWarning("geoPositionInfo is paused");
        return;
    }

    //const QGeoPositionInfo &lastGeoPositionInfo = m_geoPositionInfoSource->lastKnownPosition(true);
    if( lastGeoPositionInfo )
    {
        // Get the delta time
        const QTime &lastTime = lastGeoPositionInfo->timestamp().time();
        const QTime &currentTime = geoPositionInfo.timestamp().time();
        int lastSeconds = lastTime.second() + (lastTime.minute() * 60);
        int currentSeconds = currentTime.second() + (currentTime.minute() * 60);

        int timeDelta = currentSeconds - lastSeconds;
        m_timeElapsedInSeconds += timeDelta;
        m_timeElapsedInSecondsSinceSnapshot += timeDelta;

        //std::cout << "timeDelta is " << timeDelta << " and timeElapsed is " << m_timeElapsedInSecondsSinceSnapshot << std::endl;

        // Get our current accuracy
        m_accuracy = geoPositionInfo.attribute(QGeoPositionInfo::HorizontalAccuracy);
        //if( m_accuracy > 50 )
        //    return;

        // Get the speed
        m_speed = fabs(geoPositionInfo.attribute(QGeoPositionInfo::GroundSpeed));
        if( m_speed < 1 )
            m_speed = 0;
        if( m_speed > m_maxSpeed )
            m_maxSpeed = m_speed;

        // Update the distance
        const QGeoCoordinate &lastCoordinate = lastGeoPositionInfo->coordinate();
        const QGeoCoordinate &currentCoordinate = geoPositionInfo.coordinate();

        //double meanDelta = distanceTo(currentCoordinate, lastCoordinate);
        double meanDelta = currentCoordinate.distanceTo(lastCoordinate);
        if( !m_paused )
        {
            if( method == GeoDistanceCalc::STRAIGHT )
            {
                float d = m_speed * timeDelta;
                if( d > 0)
                    m_distanceInMeters += d;
                if( m_distanceInMeters < 0 )
                    m_distanceInMeters = 0;
            }
            else if( method == GeoDistanceCalc::DELAYED )
            {
                if( m_timeElapsedInSecondsSinceSnapshot >= 20 )
                {
                    m_timeElapsedInSecondsSinceSnapshot = 0;
                    double meanDelta = currentCoordinate.distanceTo(*snapshotGeoCoordinate);
                            //distanceTo(currentCoordinate, *snapshotGeoCoordinate);

                    //std::cout << "meanDelta is " << meanDelta << std::endl;

                    if( meanDelta >= 40 /*&& m_accuracy < 50*/ )
                    {
                        //m_timeElapsedInSecondsSinceSnapshot = 0;
                        snapshotGeoCoordinate = new QGeoCoordinate(currentCoordinate);
                        m_distanceInMeters += meanDelta;
                    }
                }
            }

        }

        if( m_firstSnapshot )
            m_firstSnapshot = false;

        //qDebug(QString().sprintf("%f' %f' / %.2f / t:%ds d:%.2f",
        //                         currentCoordinate.latitude(), currentCoordinate.longitude(), meanDelta,
        //                         m_timeElapsedInSeconds, m_distanceInMeters));
        qDebug(QString().sprintf("%f' %f' / %.2f / %.2f / %.1fm/s d:%.2f",
                                 currentCoordinate.latitude(), currentCoordinate.longitude(), meanDelta, m_accuracy, m_speed, m_distanceInMeters).toAscii().constData());

        delete lastGeoPositionInfo;
        lastGeoPositionInfo = new QGeoPositionInfo(geoPositionInfo);

    }
    else
    {
        // If the last known position is invalid, its because this is the first update we got
        const QGeoCoordinate &currentCoordinate = geoPositionInfo.coordinate();
        qDebug(QString().sprintf(">>> Location (First time) %f' %f' t: %ds d: %.2f", currentCoordinate.longitude(), currentCoordinate.latitude(), m_timeElapsedInSeconds, m_distanceInMeters).toAscii().constData());
        lastGeoPositionInfo = new QGeoPositionInfo(geoPositionInfo);
        sourceGeoCoordinate = new QGeoCoordinate(lastGeoPositionInfo->coordinate());

        snapshotGeoCoordinate = new QGeoCoordinate(*sourceGeoCoordinate);

        m_timeElapsedInSecondsSinceSnapshot = 0;
        m_firstSnapshot = true;

    }
#endif
}

void GeoDistanceCalc::updateTimeout()
{
    qDebug("GeoDistanceCalc::updateTimeout()");
/*
    //if( ++m_timeoutCounter == 10 ) // This doesn't have any effect, only one updateTimeout is thrown every one positionUpdated
    //{
        //showMessage("Se ha perdido la señal del GPS. Se intentará retomar la conexión.");

        disconnect(m_geoPositionInfoSource, SIGNAL(updateTimeout()), this, SLOT(updateTimeout()));
        disconnect(m_geoPositionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));
        m_geoPositionInfoSource->stopUpdates();

        m_geoPositionInfoSource = QGeoPositionInfoSource::createDefaultSource(this);
        m_geoPositionInfoSource->setUpdateInterval(2000); // time in milliseconds
        m_geoPositionInfoSource->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        connect(m_geoPositionInfoSource, SIGNAL(updateTimeout()), this, SLOT(updateTimeout()));
        connect(m_geoPositionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));
        m_geoPositionInfoSource->startUpdates();

        startAcquisitionTimeout();
    //}
*/
}

void GeoDistanceCalc::_qDebug(const QString &t)
{
    //MainWindow::theTextEdit->setPlainText(MainWindow::theTextEdit->toPlainText().append(t).append("\n"));
    //MainWindow::theTextEdit->verticalScrollBar()->setValue(MainWindow::theTextEdit->verticalScrollBar()->maximum());
}


void GeoDistanceCalc::gpsAcquiredTimeout()
{
    if( !m_acquired )
    {
        qDebug("GPS TIME OUT -----------> NO GPS FOUND!!!!");

#ifdef _FAKE_LOCATION_API
        stop();

        m_geoPositionInfoSource = NULL;

        qDebug("Creating GeoDistanceCalc... NOT VALID! --> We will fake the info!");

        m_fakeTimer = new QTimer();
        m_fakeTimer->setInterval(20000);
        m_fakeTimer->setSingleShot(false);
        connect(m_fakeTimer, SIGNAL(timeout()), this, SLOT(positionUpdatedFake()));

        reset();
        startSilent();

        m_gpsAvailable = false;

#endif
        emit acquisitionTimedout();

        m_acquisitionTimedout = true;

    }

}

bool GeoDistanceCalc::gpsAvailable()
{
#ifdef _ENABLE_LOCATION_API
    if( m_acquired )
        return true;
    else
    {
        qDebug("GPS AVAILABILITY: %d", (int)m_gpsAvailable);
        return m_gpsAvailable;
    }

#else
    return false;
#endif
}

void GeoDistanceCalc::showMessage(const QString &msg)
{
#ifdef _SIMULATOR_BUILD
        qWarning("\n>>>>>>>>>>>>>>>>>> %s\n", msg.toAscii().constData());
#else
        QMessageBox msgBox;
        msgBox.setText(msg);
        msgBox.exec();
#endif

}
