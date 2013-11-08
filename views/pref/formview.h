#ifndef FORMVIEW_H
#define FORMVIEW_H

#include <SIKit/SIKit.h>

class HeaderView;
class FormObjectiveView;

class FormView : public SIView
{
    Q_OBJECT
public:
    explicit FormView(QWidget *parent = 0);
    virtual ~FormView();

    static FormView *instanceA();

    HeaderView *headerView() const { return m_headerView; }

    inline void setProcessOnlyForm(const bool v) { m_processOnlyForm = v; }
    inline void setHeaderView(HeaderView *headerView) { m_headerView = headerView; }

    void pushObjectiveView(FormObjectiveView *view);

signals:

public slots:
    void pressedOk();
    void weightEditingFinished();
    void heightEditingFinished();
    void ageEditingFinished();

protected:
    void showEvent(QShowEvent *);

private:
    HeaderView *m_headerView;

    QScrollArea *m_scrollArea;
    QLabel *addLabel(QVBoxLayout *formLayout, const QString &labelText, QWidget *parent);
    QLineEdit *addTextInput(QVBoxLayout *formLayout, const QString &labelText, QWidget *parent);
    QCheckBox *addCheckInput(QHBoxLayout *checkLayout, const QString &labelText, QWidget *parent);
    QComboBox *addComboInput(QVBoxLayout *formLayout, const QString &labelText, QWidget *parent);

    QLineEdit *fullName;
    QLineEdit *eMail;
    QComboBox *homeTown;
    QLineEdit *weight;
    QLineEdit *height;
    QLineEdit *password;
    QLineEdit *password2;
    QLineEdit *age;
    QCheckBox *male;
    QCheckBox *female;

    SIButton *okButton;

    bool m_showFormWarning;
    bool m_processOnlyForm;

};

#endif // FORMVIEW_H

