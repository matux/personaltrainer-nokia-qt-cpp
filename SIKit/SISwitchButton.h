#ifndef SISWITCHBUTTON_H
#define SISWITCHBUTTON_H

#include "SIButton.h"

class SISwitchButton : public SIButton
{
    Q_OBJECT
public:
    enum State {
        ON,
        OFF
    };

    explicit SISwitchButton(QWidget *parent = 0);
    virtual ~SISwitchButton();

    inline State state() const { return m_state; }
    inline void setState(const State &state) { m_state = state; }
    void switchState();

signals:
    void stateSwitched();

public slots:

protected:
    virtual void paintEvent(QPaintEvent *paintEvent);

    virtual void mousePressEvent(QMouseEvent *event);

private:
    State m_state;

};

/*inline SISwitchButton::State SISwitchButton::State::operator !()
{
    return (m_state == SISwitchButton::ON) ? SISwitchButton::OFF : SISwitchButton::ON;
}*/

#endif // SISWITCHBUTTON_H
