#include "network.h"
#include "model/globaldataobject.h"
#include "model/userinfo.h"
#include "model/planinfo.h"

#include <QtNetwork>
#include <QUrl>
#include <QtXml>
#include <QCryptographicHash>
#include <QMessageBox>

#include <QDir>
#include <QFile>
#include <QTextStream>

#ifdef _DEVICE_BUILD
#include <CommDbConnPref.h>
#include <CommDb.h>		// CCommsDatabase
#endif

static Network *theInstance = NULL;

Network &Network::instanceA()
{
    if( !theInstance )
        theInstance = new Network();
    return *theInstance;
}

Network::Network(QObject *parent)
    :QObject(parent),
    m_requestCode(Network::RC_NONE),
    m_nextStep(Network::RC_NONE),
    registerAndSyncStep(0)
{
    qDebug("Creating Network Object");
    networkManager = NULL;
    m_initialized = false;
    m_internetAvailable = false;
    m_internetAvailableInitialized = false;
}

Network::~Network()
{

}

bool Network::internetAvailable()
{
#ifdef _DEVICE_BUILD

    if( !m_internetAvailableInitialized )
    {
        qDebug("CHECKING FOR INTERNET ACCESS...");

        m_internetAvailableInitialized = true;
        TFileName iapName;
        TUint32 iapID;
        TInt err;

        // open the IAP communications database
        qDebug("\tOPENING IAP COMMUNICATIONS DATABASE...");
        CCommsDatabase *commDB = CCommsDatabase::NewL();
        CleanupStack::PushL(commDB);

        // Open the IAP table
        qDebug("\tOPENING IAP TABLE...");
        int accessDetected = 0;
        CCommsDbTableView* view = commDB->OpenTableLC(TPtrC(IAP));

        // Point to the first entry
        if( view->GotoFirstRecord() == KErrNone )
        {
            do
            {
                view->ReadTextL(TPtrC(COMMDB_NAME), iapName);
                view->ReadUintL(TPtrC(COMMDB_ID), iapID);

                // Store name and ID to where you want to
                accessDetected++;
                qDebug("\tDETECTED ACCESS %d", iapID);

            } while (err = view->GotoNextRecord(), err == KErrNone);

            qDebug("\tAMOUNT OF ACCESS DETECTED: %d", accessDetected);
            if( accessDetected > 0 )
                m_internetAvailable = true;

            if( !m_internetAvailable )
            {
                qDebug("\tNO INTERNET AVAILABLE...");
                m_internetAvailable = false;
            }

        }
        else
        {
            qDebug("\tNO INTERNET AVAILABLE...");
            m_internetAvailable = false;
        }

        CleanupStack::PopAndDestroy(); // view
        CleanupStack::PopAndDestroy(); // commDB

    }

    return m_internetAvailable;

#else

    return true;

#endif
}

bool Network::initialize(RequestCode nextStep)
{
    qDebug("Network::initialize()");
    if( !internetAvailable() )
        return false;

    qDebug("Network::initialize() creating networkManager");

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(httpRequestDone(QNetworkReply *)));
    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,const QList<QSslError>&)), this, SLOT(sslErrors(QNetworkReply*,const QList<QSslError>&)));

    m_requestCode = Network::RC_SERVERURL;
    m_nextStep = nextStep;

    //networkManager->get(QNetworkRequest(QUrl("http://staging.dicot.dyndns.org:83/ford/fordpersonaltrainer/getfullurl.asp")));
    // QA
    QNetworkRequest networkRequest = QNetworkRequest(QUrl("https://qamg.ar.ford.com/fordpersonaltrainer/getfullurl.asp"));
    networkRequest.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    networkManager->get(networkRequest);

    // PRODUCCION
    //QNetworkRequest networkRequest = QNetworkRequest(QUrl("https://www.ford.com.ar/fordpersonaltrainer/getfullurl.asp"));
    //networkRequest.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    //networkManager->get(networkRequest);

    qDebug("Network::initialize() creating networkManager done");

    return true;
}

QDomDocument Network::generateUserXML()
{
    UserInfo &userInfo = GlobalDataObject::instance().userInfo();

    // Generate the MD5 hash from the password
    QByteArray hashedPassword = QCryptographicHash::hash(QString(userInfo.password()).toAscii(), QCryptographicHash::Md5).toHex();
    qDebug("Hashed Password is %s", hashedPassword.constData());

    // We need to build our XML with the user information
    QDomDocument doc("");
    doc.appendChild(doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\" "));
    QDomElement rootElement = doc.createElement("request");
    doc.appendChild(rootElement);
        QDomElement loginElement = doc.createElement("login");
        rootElement.appendChild(loginElement);
            QDomElement deEmailL = doc.createElement("email");
            deEmailL.appendChild(doc.createTextNode(userInfo.eMail()));
            loginElement.appendChild(deEmailL);
            QDomElement dePassL = doc.createElement("pass");
            dePassL.appendChild(doc.createTextNode(hashedPassword));
            loginElement.appendChild(dePassL);
        QDomElement deUser = doc.createElement("usuario");
        rootElement.appendChild(deUser);
            QDomElement userNameElement = doc.createElement("nombre");
            deUser.appendChild(userNameElement);
                QDomCDATASection userNameData = doc.createCDATASection(userInfo.fullName());
                userNameElement.appendChild(userNameData);
            QDomElement emailElement = doc.createElement("email");
            emailElement.appendChild(doc.createTextNode(userInfo.eMail()));
            deUser.appendChild(emailElement);
            QDomElement passElement = doc.createElement("pass");
            passElement.appendChild(doc.createTextNode(hashedPassword));
            deUser.appendChild(passElement);
            QDomElement provinciaElement = doc.createElement("provincia");
            provinciaElement.appendChild(doc.createTextNode(userInfo.homeTownKey()));
            deUser.appendChild(provinciaElement);
            QDomElement pesoElement = doc.createElement("peso");
            pesoElement.appendChild(doc.createTextNode(userInfo.weight()));
            deUser.appendChild(pesoElement);
            QDomElement alturaElement = doc.createElement("altura");
            alturaElement.appendChild(doc.createTextNode(userInfo.height()));
            deUser.appendChild(alturaElement);
            QDomElement edadElement = doc.createElement("edad");
            edadElement.appendChild(doc.createTextNode(QString().sprintf("%d",userInfo.age())));
            deUser.appendChild(edadElement);
            QDomElement sexoElement = doc.createElement("sexo");
            sexoElement.appendChild(doc.createTextNode(userInfo.gender()==UserInfo::G_MALE?"M":"F"));
            deUser.appendChild(sexoElement);
            QDomElement dispElement = doc.createElement("disponibilidad");
            dispElement.appendChild(doc.createTextNode("3"));
            deUser.appendChild(dispElement);
            QDomElement objElement = doc.createElement("objetivo");
            objElement.appendChild(doc.createTextNode(QString().sprintf("%d", userInfo.objectiveIndex() + 1)));
            deUser.appendChild(objElement);
            QDomElement resultElement = doc.createElement("resultado");
            resultElement.appendChild(doc.createTextNode(QString().sprintf("%d",(int)userInfo.level(userInfo.objectiveIndex()) + 1)));
            deUser.appendChild(resultElement);

    return doc;
}

QDomDocument Network::generateSyncXML()
{
    UserInfo &userInfo = GlobalDataObject::instance().userInfo();
    PlanInfo **planInfo = GlobalDataObject::instance().planInfoFull();

    // Generate the MD5 hash from the password
    QByteArray hashedPassword = QCryptographicHash::hash(QString(userInfo.password()).toAscii(), QCryptographicHash::Md5).toHex();
    qDebug("Hashed Password is %s", hashedPassword.constData());

    // We need to build our XML based on the plan information
    QDomDocument doc("");
    doc.appendChild(doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\" "));
    QDomElement rootElement = doc.createElement("request");
    doc.appendChild(rootElement);
    {
        QDomElement loginElement = doc.createElement("login");
        rootElement.appendChild(loginElement);
        {
            QDomElement deEmailL = doc.createElement("email");
            deEmailL.appendChild(doc.createTextNode(userInfo.eMail()));
            loginElement.appendChild(deEmailL);
            QDomElement dePassL = doc.createElement("pass");
            dePassL.appendChild(doc.createTextNode(hashedPassword));
            loginElement.appendChild(dePassL);
        }
        QDomElement userElement = doc.createElement("usuario");
        rootElement.appendChild(userElement);
        {
            QDomElement deObj = doc.createElement("objetivo");
            deObj.appendChild(doc.createTextNode(QString().sprintf("%d", userInfo.objectiveIndex() + 1)));
            userElement.appendChild(deObj);
            QDomElement deRes = doc.createElement("resultado");
            deRes.appendChild(doc.createTextNode(QString().sprintf("%d",(int)userInfo.level(userInfo.objectiveIndex()) + 1)));
            userElement.appendChild(deRes);
        }
        QDomElement deTrain = doc.createElement("entrenamiento");
        rootElement.appendChild(deTrain);
        {
            //for( int i = 0; i < PLAN_COUNT; ++i )
            //{
                int objetivo = userInfo.objectiveIndex();

                if( planInfo[objetivo]->routineInfoList().count() > 0 )
                {
                    // Check if there're actual routines done
                    bool goAhead = false;
                    for( int j = 0; j < planInfo[objetivo]->routineInfoList().count() && !goAhead; ++j )
                    {
                        PlanInfo::RoutineInfo &routineInfo = *planInfo[objetivo]->routineInfoList().at(j);
                        goAhead = routineInfo.routineDone;
                    }

                    if( goAhead )
                    {
                        QDomElement loginElement = doc.createElement("plan");
                        loginElement.setAttribute("id", planInfo[objetivo]->planId() + 1);
                        deTrain.appendChild(loginElement);

                        for( int j = 0; j < planInfo[objetivo]->routineInfoList().count(); ++j )
                        {
                            PlanInfo::RoutineInfo &routineInfo = *planInfo[objetivo]->routineInfoList().at(j);

                            //if( routineInfo.routineDone )
                            //{
                                QDomElement routineElement = doc.createElement("rutina");
                                routineElement.setAttribute("id", routineInfo.id);
                                routineElement.setAttribute("fecha", routineInfo.date.toString("yyyy-MM-dd"));
                                routineElement.setAttribute("hora", routineInfo.time);
                                loginElement.appendChild(routineElement);

                                for( int e = 0; e < routineInfo.exerciseInfo.count(); ++e )
                                {
                                    PlanInfo::ExerciseInfo &exerciseInfo = *routineInfo.exerciseInfo.at(e);
                                    QDomElement exerciseElement = doc.createElement("ejercicio");
                                    exerciseElement.setAttribute("id", exerciseInfo.id);
                                    exerciseElement.setAttribute("tiempo", exerciseInfo.time);
                                    exerciseElement.setAttribute("distancia", exerciseInfo.distance);
                                    exerciseElement.setAttribute("calorias", exerciseInfo.calories);
                                    routineElement.appendChild(exerciseElement);
                                }

                            //}

                        }

                    }
                    else
                        return QDomDocument();

                }
            //}
        }
    }

    return doc;

}

bool Network::registerUser()
{
    /*if( m_serviceUrl.isEmpty() )
    {
        qDebug("Network::registerUser(): serviceUrl is empty, initialize() first.");
        return false;
    }*/

    if( !m_initialized )
        return initialize(m_requestCode == Network::RC_REGISTERANDSYNC ? Network::RC_REGISTERANDSYNC : Network::RC_REGISTERUSER);
    /*
        if( ! )
        {
            showMessage("Ha ocurrido un error en la transacción con el servidor. Por favor, vuelva a intentar.");

            docXML = generateUserXML();
            outputXMLToFile("informacion_usuario.xml");
            docXML = generateSyncXML();
            outputXMLToFile("informacion_sincronizacion.xml");

            showMessage("Tu archivo de registro y sincronización para la Web de Personal Trainer fue grabado en el Memory Card de tu Nokia en la carpeta \"Others\\PersonalTrainer\"");

            return false;
        }
    */
    m_requestCode = Network::RC_REGISTERUSER;

    // Reset the Global variable that indicates if the user was registered
    // if a user was registered already, we want to indicate the contrary
    // so a new one can be registered
    GlobalDataObject::instance().setUserRegistered(false);

    docXML = generateUserXML();

    // Create cookie
    //QList<QNetworkCookie> cookieList;
    //QNetworkCookie cookie("_trainer_session", "BAh7czoPc2Vzc2lvbl9pZCIlNjRjYjgwZGY1NWRhMjk5MTg2ODU0NDJkZDI0NDlhMzM6EF9jc3JmX3Rva2VuIjFEYnVZRW9GeEJ1bThtQkdva3BOK1JzZmJGc0NQRlNOWnE2dndpa244VGlvPQ%3D%3D--5dfff501e5fdb1b97b1b680e496e662c84dd2d61");
    //cookieList.append(cookie);

    // Build Body
    //QByteArray postBody;
    QString postBody;
    QUrl params;
    params.addQueryItem("request", docXML.toString());
    postBody.append(params.toString());
    postBody.remove(0,1);
    postBody.replace('\n', "");
    postBody.replace('\t', "");
    postBody.replace("> ", ">");
    postBody.replace(" <", "<");
    postBody.replace(" ", "%20");
    /*
    QString postBody;
    postBody.append("--0xKhTmLbOuNdArY\n");
    postBody.append("Content-Disposition: form-data; name=\"request\"");
    postBody.append(doc.toByteArray());
    postBody.append("--0xKhTmLbOuNdArY--");
    */

    // Build Header
    QUrl url(m_serviceUrl + "registrar_perfilcompleto.asp");
    QNetworkRequest networkRequest(url);
    networkRequest.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    //networkRequest.setRawHeader("User-Agent", "Personal Trainer 1.0 (Nokia Device; Symbian OS; en_US)");
    //networkRequest.setRawHeader("User-Agent", "User Agent");
    //networkRequest.setRawHeader("Host", "staging.dicot.dyndns.org");
    //networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=0xKhTmLbOuNdArY");
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    //networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "plain/text");
    //networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");
    //networkRequest.setRawHeader("Accept-Encoding", "gzip");
    //networkRequest.setRawHeader("Content-Length", QString().sprintf("%d", postBody.length()).toUtf8());
    //networkRequest.setHeader(QNetworkRequest::CookieHeader, cookieList);
    //networkRequest.setRawHeader("Cookie", "_trainer_session=BAh7czoPc2Vzc2lvbl9pZCIlNjRjYjgwZGY1NWRhMjk5MTg2ODU0NDJkZDI0NDlhMzM6EF9jc3JmX3Rva2VuIjFEYnVZRW9GeEJ1bThtQkdva3BOK1JzZmJGc0NQRlNOWnE2dndpa244VGlvPQ%3D%3D--5dfff501e5fdb1b97b1b680e496e662c84dd2d61");

    QByteArray finalData = postBody.toUtf8(); //postBody.toAscii().toPercentEncoding("<>=?@',[]!/");
    qDebug("Network::httpRequestDone(): \nURL: %s\n\nBODY:\n%s\nLENGTH: %d", url.toString().toAscii().constData(), finalData.constData(), finalData.length());

    // POST
    networkManager->post(networkRequest, finalData); //.toUtf8()

    return true;

}

bool Network::syncUser()
{
    /*if( m_serviceUrl.isEmpty() )
    {
        qDebug("Network::syncUser(): serviceUrl is empty, initialize() first.");
        return false;
    }*/

    if( !m_initialized )
        return initialize(Network::RC_SYNCUSER);
    /*
        if( !initialize(Network::RC_SYNCUSER) )
        {
            showMessage("Ha ocurrido un error en la transacción con el servidor. Por favor, vuelva a intentar.");

            docXML = generateUserXML();
            outputXMLToFile("informacion_usuario.xml");
            docXML = generateSyncXML();
            outputXMLToFile("informacion_sincronizacion.xml");

            showMessage("Tu archivo de registro y sincronización para la Web de Personal Trainer fue grabado en el Memory Card de tu Nokia en la carpeta \"Others\\PersonalTrainer\"");

            return false;
        }
    */

    docXML = generateSyncXML();

    if( docXML.toString().isEmpty() )
        return false;

    m_requestCode = Network::RC_SYNCUSER;

    // Create cookie
    //QList<QNetworkCookie> cookieList;
    //QNetworkCookie cookie("_trainer_session", "BAh7czoPc2Vzc2lvbl9pZCIlNjRjYjgwZGY1NWRhMjk5MTg2ODU0NDJkZDI0NDlhMzM6EF9jc3JmX3Rva2VuIjFEYnVZRW9GeEJ1bThtQkdva3BOK1JzZmJGc0NQRlNOWnE2dndpa244VGlvPQ%3D%3D--5dfff501e5fdb1b97b1b680e496e662c84dd2d61");
    //cookieList.append(cookie);

    // Build Body
    //QByteArray postBody;
    QString postBody;
    //QUrl params;
    //params.addQueryItem("request", docXML.toString());
    postBody.append("request=");
    postBody.append(docXML.toString());
    //postBody.remove(0,1);
    postBody.replace('\n', "");
    postBody.replace('\t', "");
    postBody.replace("> ", ">");
    postBody.replace(" <", "<");
    postBody.replace(" ", "%20");
    /*
    QString postBody;
    postBody.append("--0xKhTmLbOuNdArY\n");
    postBody.append("Content-Disposition: form-data; name=\"request\"\n");
    postBody.append(docXML.toByteArray());
    postBody.append("--0xKhTmLbOuNdArY--");
    */
    // Build Header
    QUrl url(m_serviceUrl + "sincronizar_sesion.asp");
    QNetworkRequest networkRequest(url);
    networkRequest.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    /*
    QNetworkRequest networkRequest(url);
    networkRequest.setRawHeader("User-Agent", "Personal Trainer 1.0 (Nokia Device; Symbian OS; en_US)");
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=0xKhTmLbOuNdArY");
    networkRequest.setRawHeader("Accept-Encoding", "gzip");
    networkRequest.setRawHeader("Content-Length", QString().sprintf("%d", postBody.length()).toAscii());
    //networkRequest.setHeader(QNetworkRequest::CookieHeader, cookieList);
    networkRequest.setRawHeader("Cookie", "_trainer_session=BAh7czoPc2Vzc2lvbl9pZCIlNjRjYjgwZGY1NWRhMjk5MTg2ODU0NDJkZDI0NDlhMzM6EF9jc3JmX3Rva2VuIjFEYnVZRW9GeEJ1bThtQkdva3BOK1JzZmJGc0NQRlNOWnE2dndpa244VGlvPQ%3D%3D--5dfff501e5fdb1b97b1b680e496e662c84dd2d61");
    */
    QByteArray finalData = postBody.toUtf8(); //postBody.toAscii().toPercentEncoding("<>=?@',[]!/");
    qDebug("Network::httpRequestDone(): \nURL: %s\n\nBODY:\n%s\nLENGTH: %d", url.toString().toAscii().constData(), finalData.constData(), finalData.length());

    // POST
    networkManager->post(networkRequest, finalData); //.toUtf8()

    return true;
}

bool Network::registerAndSync()
{
    registerAndSyncStep = 0;
    m_requestCode = Network::RC_REGISTERANDSYNC;
    registerUser();
    if( m_requestCode != Network::RC_SERVERURL )
        m_requestCode = Network::RC_REGISTERANDSYNC;

    return true;
}

void Network::sslErrors(QNetworkReply *networkReply, const QList<QSslError> &sslErrorList)
{
    qDebug("Network::sslErrors(QNetworkReply *networkReply, const QList<QSslError> &sslErrorList)");
    networkReply->ignoreSslErrors();

}

bool Network::checkResponse(const QDomDocument &response)
{
    int errorCod = 0;
    QString errorDesc("");
    for( int i = 0; i < response.documentElement().childNodes().count() /*&& !(bool)errorCod*/; ++i )
    {
        QDomElement e = response.documentElement().childNodes().at(i).toElement();
        QString ed = e.tagName();
        if( ed.compare("error_cod") == 0 )
            errorCod = e.text().toInt();
        else if( ed.compare("error_desc") == 0 )
        {
            QDomCDATASection cdata = e.firstChild().toCDATASection();
            errorDesc = cdata.data();
        }

    }

    if( errorCod != 0 )
        showMessage(QString().sprintf("Ha ocurrido un error en la transacción con el servidor código: %d, '%s'. Por favor, vuelva a intentar.", errorCod, errorDesc.toUtf8().constData()));

    return !(bool)errorCod;
}

void Network::httpRequestDone(QNetworkReply *reply)
{
    QString response(reply->readAll());
    qDebug("Network::httpRequestDone(): %s : Error: (%d) %s", response.toAscii().constData(), reply->error(), reply->errorString().toAscii().constData());

    if( reply->error() != 0 )
    {
        showMessage("Ha ocurrido un error en la transacción con el servidor. Por favor, vuelva a intentar.");

        docXML = generateUserXML();
        outputXMLToFile("informacion_usuario.xml");
        docXML = generateSyncXML();
        outputXMLToFile("informacion_sincronizacion.xml");

        showMessage("Tu archivo de registro y sincronización para la Web de Personal Trainer fue grabado en el Memory Card de tu Nokia en la carpeta \"Others\\PersonalTrainer\"");

        emit finished();
    }
    else
    {
        QDomDocument doc("");
        doc.setContent(response);

        switch( m_requestCode )
        {
        case Network::RC_SERVERURL:
            m_requestCode = Network::RC_NONE;

            if( checkResponse(doc) )
            {
                m_initialized = true;
                m_serviceUrl = doc.documentElement().firstChildElement().text();
                qDebug("Network::httpRequestDone : Network::RC_SERVERURL: %s", m_serviceUrl.toAscii().constData());

                if( m_nextStep != Network::RC_NONE )
                {
                    if( m_nextStep == Network::RC_REGISTERUSER )
                        registerUser();
                    else if( m_nextStep == Network::RC_SYNCUSER )
                        syncUser();
                    else if( m_nextStep == Network::RC_REGISTERANDSYNC )
                        registerAndSync();
                }
            }
            break;
        case Network::RC_REGISTERUSER:
            m_requestCode = Network::RC_NONE;

            qDebug("Network::httpRequestDone : Network::RC_REGISTERUSER: %s", response.toAscii().constData());
            if( checkResponse(doc) )
            {
                GlobalDataObject::instance().setUserRegistered(true);
                GlobalDataObject::instance().saveApplicationSettings();

                // Do nothing
                showMessage("Tu usuario fue registrado con éxito!");
            }
            else
            {
                outputXMLToFile("informacion_usuario.xml");

                showMessage("Tu archivo de registro y sincronización para la Web de Personal Trainer fue grabado en el Memory Card de tu Nokia en la carpeta \"Others\\PersonalTrainer\"");
            }

            emit finished();
            break;
        case Network::RC_SYNCUSER:
            m_requestCode = Network::RC_NONE;

            qDebug("Network::httpRequestDone : Network::RC_SYNCUSER: %s", response.toAscii().constData());
            if( checkResponse(doc) )
            {
                // Response was ok, reset planInfo data
                GlobalDataObject::instance().planInfo(GlobalDataObject::instance().userInfo().objectiveIndex()).reset();
                GlobalDataObject::instance().saveApplicationSettings();
                showMessage("La sincronización fue un éxito!");
            }
            else
            {
                outputXMLToFile("informacion_sincronizacion.xml");

                showMessage("Tu archivo de registro y sincronización para la Web de Personal Trainer fue grabado en el Memory Card de tu Nokia en la carpeta \"Others\\PersonalTrainer\"");
            }

            emit finished();
            break;
        case Network::RC_REGISTERANDSYNC:
            m_requestCode = Network::RC_NONE;

            qDebug("Network::httpRequestDone : Network::RC_REGISTERANDSYNC: %s", response.toAscii().constData());
            if( checkResponse(doc) )
            {
                if( registerAndSyncStep == 0 )
                {
                    GlobalDataObject::instance().setUserRegistered(true);
                    GlobalDataObject::instance().saveApplicationSettings();

                    registerAndSyncStep++;
                    syncUser();
                }
                else
                {
                    // Response was ok, reset planInfo data
                    GlobalDataObject::instance().planInfo(GlobalDataObject::instance().userInfo().objectiveIndex()).reset();
                    GlobalDataObject::instance().saveApplicationSettings();
                    showMessage("El registro de tu usuario y la sincronización de rutinas fueron un éxito!");
                    registerAndSyncStep = 0;

                    emit finished();
                }
            }
            else
            {
                docXML = generateUserXML();
                outputXMLToFile("informacion_usuario.xml");
                docXML = generateSyncXML();
                outputXMLToFile("informacion_sincronizacion.xml");

                showMessage("Tu archivo de registro y sincronización para la Web de Personal Trainer fue grabado en el Memory Card de tu Nokia en la carpeta \"Others\\PersonalTrainer\"");

                emit finished();
            }

            break;
        default:
            qDebug("Network::httpRequestDone : INVALID REQUEST CODE: %d", m_requestCode);
            m_requestCode = Network::RC_NONE;

            emit finished();
            break;
        }
    }

}

void Network::outputXMLToFile(const QString &filename)
{
#ifdef _SIMULATOR_BUILD
    QDir dir;
    dir.mkpath("c://Others//PersonalTrainer//");
    QFile file(QString("c://Others//PersonalTrainer//%1").arg(filename));
#else
    QDir dir;
    dir.mkpath("e://Others//PersonalTrainer//");
    QFile file(QString("e://Others//PersonalTrainer//%1").arg(filename));
#endif
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << docXML.toString();

}

void Network::showMessage(const QString &msg)
{
#ifdef _SIMULATOR_BUILD
        qWarning("\n>>>>>>>>>>>>>>>>>> %s\n", msg.toAscii().constData());
#else
        QMessageBox msgBox;
        msgBox.setText(msg);
        msgBox.exec();
#endif

}
