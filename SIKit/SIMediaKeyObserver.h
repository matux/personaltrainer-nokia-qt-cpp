#ifndef MEDIAKEYSOBSERVER_H_
#define MEDIAKEYSOBSERVER_H_

//#ifdef Q_OS_SYMBIAN
#ifdef _DEVICE_BUILD__
#include <remconcoreapi.h>
#include <remconcoreapitargetobserver.h>
#include <remconcoreapitarget.h>
#include <remconinterfaceselector.h>
#include <aknappui.h>
#endif

#include <QObject>

class SIMediaKeyObserver : public QObject
#ifdef Q_OS_SYMBIAN__
        , public MRemConCoreApiTargetObserver
#endif
{
    Q_OBJECT

public:

    enum MediaKeys
    {
        EVolIncKey,
        EVolDecKey,
        EPlayPauseKey,
        EStopKey,
        EBackwardKey,
        EForwardKey,
        EFastForwardKey,
        EFastRewindKey
    };

    SIMediaKeyObserver(QObject *parent = 0);
    virtual ~SIMediaKeyObserver();

protected: // From public MRemConCoreApiTargetObserver
#ifdef Q_OS_SYMBIAN__
    void MrccatoCommand(TRemConCoreApiOperationId aOperationId, TRemConCoreApiButtonAction aButtonAct);
    void MrccatoPlay(TRemConCoreApiPlaybackSpeed /*aSpeed*/, TRemConCoreApiButtonAction /*aButtonAct*/) {};
    void MrccatoTuneFunction(TBool /*aTwoPart*/, TUint /*aMajorChannel*/, TUint /*aMinorChannel*/, TRemConCoreApiButtonAction /*aButtonAct*/) {};
    void MrccatoSelectDiskFunction(TUint /*aDisk*/, TRemConCoreApiButtonAction /*aButtonAct*/) {};
    void MrccatoSelectAvInputFunction(TUint8 /*aAvInputSignalNumber*/, TRemConCoreApiButtonAction /*aButtonAct*/) {};
    void MrccatoSelectAudioInputFunction(TUint8 /*aAudioInputSignalNumber*/, TRemConCoreApiButtonAction /*aButtonAct*/) {};
#endif
Q_SIGNALS:
    void mediaKeyPressed(SIMediaKeyObserver::MediaKeys key);

private:
#ifdef Q_OS_SYMBIAN__
    CRemConInterfaceSelector* iInterfaceSelector;
    CRemConCoreApiTarget*     iCoreTarget;
#endif
};

#endif
