#ifndef PREFVIEW_H
#define PREFVIEW_H

#include <SIKit/SIKit.h>

class PrefView : public SIView
{
    Q_OBJECT
public:
    explicit PrefView(QWidget *parent = 0);
    virtual ~PrefView();

signals:

public slots:
    void objetivoPressed();
    void nuevoUsuarioPressed();
    void sincroDatosPressed();
    void videoIntroPressed();

    void videoEnded();

};

#endif // PREFVIEW_H
