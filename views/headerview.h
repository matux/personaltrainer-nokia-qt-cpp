#ifndef HEADERVIEW_H
#define HEADERVIEW_H

#include <SIKit/SIKit.h>

class HeaderView : public SIView
{
    Q_OBJECT
public:
    explicit HeaderView(QWidget *parent = 0);
    explicit HeaderView(const QString &titleImageFilename, QWidget *parent);
    virtual ~HeaderView();

    //inline void setTitlePixmap(QPixmap *pixmap) { m_titlePixmap = pixmap; }
    void setTitleImageFilename(const QString &fileName);
    inline QPixmap const &titlePixmap() const { return *m_titlePixmap; }

    inline SIButton &backButton() { return *m_backButton; }
    inline SIButton &homeButton() { return *m_homeButton; }

    inline void setUserInteractionEnabled(bool value) { m_userInteraction = value; }

signals:
    void homePressed();

private slots:
    void homePressedSlot();
    void backPressedSlot();

protected:
    void paintEvent(QPaintEvent *paintEvent);

private:
    void initUi();

    bool m_userInteraction;

    SIButton *m_backButton;
    SIButton *m_homeButton;

    QPixmap *m_titlePixmap;

};

#endif // HEADERVIEW_H
