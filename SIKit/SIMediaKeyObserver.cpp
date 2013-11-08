#include "SIMediaKeyObserver.h"

SIMediaKeyObserver::SIMediaKeyObserver(QObject *parent)
    :QObject(parent)
{
#ifdef Q_OS_SYMBIAN__
    iInterfaceSelector = CRemConInterfaceSelector::NewL();
    iCoreTarget = CRemConCoreApiTarget::NewL(*iInterfaceSelector, *this);
    iInterfaceSelector->OpenTargetL();
#endif
}

SIMediaKeyObserver::~SIMediaKeyObserver()
{
#ifdef Q_OS_SYMBIAN__
    if( iInterfaceSelector )
        delete iInterfaceSelector;
#endif
}

#ifdef Q_OS_SYMBIAN__
void SIMediaKeyObserver::MrccatoCommand(TRemConCoreApiOperationId aOperationId, TRemConCoreApiButtonAction aButtonAct)
{
    TRequestStatus status;
    switch(aOperationId)
    {
    case ERemConCoreApiPausePlayFunction:
            {
            if (aButtonAct == ERemConCoreApiButtonClick)
                emit mediaKeyPressed(SIMediaKeyObserver::EPlayPauseKey);

            //Send the response back to Remcon server
            iCoreTarget->PausePlayFunctionResponse(status, KErrNone);
            User::WaitForRequest(status);
            break;
            }

    case ERemConCoreApiStop:
            {
    if (aButtonAct == ERemConCoreApiButtonClick)
        emit mediaKeyPressed(SIMediaKeyObserver::EStopKey);
            iCoreTarget->StopResponse(status, KErrNone);
            User::WaitForRequest(status);
            break;
            }
    case ERemConCoreApiRewind:
            {
    if (aButtonAct == ERemConCoreApiButtonClick)
        emit mediaKeyPressed(SIMediaKeyObserver::EFastRewindKey);
            iCoreTarget->RewindResponse(status, KErrNone);
            User::WaitForRequest(status);
            break;
            }
    case ERemConCoreApiForward:
            {
    if (aButtonAct == ERemConCoreApiButtonClick)
        emit mediaKeyPressed(SIMediaKeyObserver::EForwardKey);
            iCoreTarget->ForwardResponse(status, KErrNone);
            User::WaitForRequest(status);
            break;
            }
    case ERemConCoreApiVolumeUp:
            {
    if (aButtonAct == ERemConCoreApiButtonClick)
        emit mediaKeyPressed(SIMediaKeyObserver::EVolIncKey);
            iCoreTarget->VolumeUpResponse(status, KErrNone);
            User::WaitForRequest(status);

            break;
            }
    case ERemConCoreApiVolumeDown:
            {
    if (aButtonAct == ERemConCoreApiButtonClick)
        emit mediaKeyPressed(SIMediaKeyObserver::EVolDecKey);
            iCoreTarget->VolumeDownResponse(status, KErrNone);
            User::WaitForRequest(status);
            break;
            }
    case ERemConCoreApiFastForward:
            {
    if (aButtonAct == ERemConCoreApiButtonClick)
        emit mediaKeyPressed(SIMediaKeyObserver::EFastForwardKey);
            iCoreTarget->FastForwardResponse(status, KErrNone);
            User::WaitForRequest(status);
            break;
            }
    case ERemConCoreApiBackward:
            {
    if (aButtonAct == ERemConCoreApiButtonClick)
        emit mediaKeyPressed(SIMediaKeyObserver::EBackwardKey);
            iCoreTarget->BackwardResponse(status, KErrNone);
            User::WaitForRequest(status);
            break;
            }
    default:
            break;
    }
}
#endif
