#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QDomDocument>

class QNetworkAccessManager;
class QNetworkReply;
class QSslError;

#ifdef _DEVICE_BUILD
#include <eikenv.h>
#include <eikappui.h>
#include <aknenv.h>
#include <aknappui.h>

class TIapData
{
public:
        TBuf<128> iName;
        TUint32 iIap;

};
#endif

class Network : public QObject
{
    Q_OBJECT
public:
    enum RequestCode
    {
        RC_NONE,
        RC_SERVERURL,
        RC_REGISTERUSER,
        RC_REGISTERANDSYNC,
        RC_SYNCUSER
    };

public:
    static Network &instanceA();
    virtual ~Network();

    bool initialize(RequestCode nextStep);
    bool registerUser();
    bool registerAndSync();
    bool syncUser();

    bool internetAvailable();

signals:
    void finished();

public slots:
    void httpRequestDone(QNetworkReply *);
    void sslErrors(QNetworkReply*, const QList<QSslError> &);

private:
    explicit Network(QObject *parent = 0);
    Network(Network const &, QObject *parent = 0) {}
    Network &operator =(Network const &);

    void outputXMLToFile(const QString &filename);

    bool checkResponse(const QDomDocument &response);
    QDomDocument generateUserXML();
    QDomDocument generateSyncXML();
    void showMessage(const QString &msg);

    RequestCode m_requestCode;
    RequestCode m_nextStep;
    QNetworkAccessManager *networkManager;
    QString m_serviceUrl;

    int registerAndSyncStep;
    bool m_initialized;
    bool m_internetAvailableInitialized;
    bool m_internetAvailable;

    QDomDocument docXML;
};

#endif // NETWORK_H
