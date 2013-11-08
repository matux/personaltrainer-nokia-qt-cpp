#include "qfreestyleapplication.h"

#include "time.h"

#include "SIKit/SIKit.h"

// Needed Symbian specific headers
#ifdef Q_OS_SYMBIAN
#include <eikenv.h>
#include <eikappui.h>
#include <aknenv.h>
#include <aknappui.h>
#endif

#include "mainwindow.h"

QFreestyleApplication::QFreestyleApplication(int &argc, char **argv)
    :QApplication(argc, argv)
{
    // Initialize random seed
    srand(time(NULL));

    // Set some base settings
    setOrganizationName("Ford");
    setOrganizationDomain("fordpersonaltrainer.com.ar");
    setApplicationName("Personal Trainer");

    // Symbian specific code to lock orientation
    #ifdef Q_OS_SYMBIAN
    CAknAppUi *appUi = dynamic_cast<CAknAppUi *>(CEikonEnv::Static()->AppUi());
    QT_TRAP_THROWING(appUi ->SetOrientationL(CAknAppUi::EAppUiOrientationPortrait));
    //TRAPD(error, if( appUi ) { appUi->SetOrientationL(CAknAppUi::EAppUiOrientationPortrait); } );
    #endif

}

int QFreestyleApplication::start()
{
    //QStringList list = QStyleFactory::keys();
    //for (int i = 0; i < list.size(); ++i)
    //    qDebug("%s", list.at(i).toLocal8Bit().constData());

    MainWindow mainWindow;
    mainWindow.setAttribute(Qt::WA_QuitOnClose, true);
    mainWindow.showFullScreen();

    // Start main loop
    return QApplication::exec();
}

#ifdef Q_OS_SYMBIAN

bool QFreestyleApplication::symbianEventFilter(const QSymbianEvent *event)
{
    if( event->type() == QSymbianEvent::WindowServerEvent )
    {
        // Get the event type: types are defined in TEventCode
        const TWsEvent *iWsEvent = event->windowServerEvent();
        TInt eventType = iWsEvent->Type(); // Process event

        qDebug("QApplication::symbianEventFilter() Type: %d / %d", (int)event->type(), eventType);

        switch( eventType )
        {
        // 11, 21, 1000, 271064886
        case EEventFocusGroupChanged:
        case EEventFocusLost:
        case EEventWindowVisibilityChanged:
            if( SIMediaPlayer::videoIsPlaying )
            {
                qDebug("QApplication::symbianEventFilter: EEventWindowVisibilityChanged");
                SIMediaPlayer::instance().stopAll();
                SIMediaPlayer::instance().mediaStatusChanged(QMediaPlayer::EndOfMedia);
            }
            break;
        case EEventKeyUp:
            qDebug("QApplication::symbianEventFilter: EEventKeyUp");
            break;
        default:
            return QApplication::symbianEventFilter(event);

        }

    }
    else
        return QApplication::symbianEventFilter(event);
}

#endif

