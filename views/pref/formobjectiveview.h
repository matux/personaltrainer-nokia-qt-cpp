#ifndef FORMOBJECTIVEVIEW_H
#define FORMOBJECTIVEVIEW_H

#include <SIKit/SIKit.h>

class HeaderView;

class FormObjectiveView : public SIView
{
    Q_OBJECT
public:
    explicit FormObjectiveView(QWidget *parent = 0);
    virtual ~FormObjectiveView();

    static FormObjectiveView *instanceA();

    inline void setProcessOnlyForm(const bool v) { m_processOnlyForm = v; }
    inline void setHeaderView(HeaderView *headerView) { m_headerView = headerView; }

signals:

public slots:
    void pressedOk();
    void objOneSwitched();
    void objTwoSwitched();
    void objThreeSwitched();
    void objFourSwitched();

    void reachedEndOfMedia();

protected:
    void showEvent(QShowEvent *);

private:
    HeaderView *m_headerView;

    SISwitchButton *addSwitchButton(QVBoxLayout *formLayout, const QString &buttonPixName, QWidget *parent);

    SISwitchButton *objOne;
    SISwitchButton *objTwo;
    SISwitchButton *objThree;
    SISwitchButton *objFour;

    bool m_processOnlyForm;

};

#endif // FORMOBJECTIVEVIEW_H
