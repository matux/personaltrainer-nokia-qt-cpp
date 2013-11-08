#include "formview.h"
#include "model/globaldataobject.h"
#include "model/userinfo.h"
#include "views/headerview.h"
#include "mainwindow.h"
#include "testview.h"
#include "formobjectiveview.h"

#include <QSound>

static FormView *m_instance = NULL;

FormView *FormView::instanceA()
{
    return m_instance;
}

FormView::FormView(QWidget *parent)
    :SIView(parent),
    m_headerView(NULL),
    m_scrollArea(NULL),
    fullName(NULL),
    eMail(NULL),
    homeTown(NULL),
    weight(NULL),
    height(NULL),
    password(NULL),
    password2(NULL),
    age(NULL),
    male(NULL),
    female(NULL),
    okButton(NULL),
    m_showFormWarning(true)
{
    m_processOnlyForm = false;

    setObjectName(QString().sprintf("FormView%p", parent));

    // Create UI
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), 436);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(436);

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/fondo_base.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(436);

    QWidget *layoutContainer = new QWidget();
    layoutContainer->setObjectName("formLayoutContainer");
    layoutContainer->setStyleSheet(QString("QWidget#formLayoutContainer { background-color: rgba(255,0,0,0); }"));
    //layoutContainer->resize(QApplication::desktop()->width(), 800);
    layoutContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layoutContainer->setMinimumWidth(QApplication::desktop()->width());
    layoutContainer->setMinimumHeight(436);

    QVBoxLayout *formLayout = new QVBoxLayout(layoutContainer);
    formLayout->setSpacing(0);
    formLayout->setContentsMargins(12, 4, 0, 0);

    formLayout->addItem(new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Minimum));

    /********************************************************************/

    fullName = addTextInput(formLayout, "NOMBRE Y APELLIDO", centralWidget);
    formLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));
    homeTown = addComboInput(formLayout, "LUGAR DE RESIDENCIA", centralWidget);
    formLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));
    weight = addTextInput(formLayout, "PESO (kg)", centralWidget);
    formLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));
    height = addTextInput(formLayout, "ALTURA (cm)", centralWidget);
    formLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));
    age = addTextInput(formLayout, "EDAD", centralWidget);
    formLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));

    addLabel(formLayout, "SEXO", centralWidget);
    QHBoxLayout *checkLayout = new QHBoxLayout;
    checkLayout->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    formLayout->addLayout(checkLayout);
    male = addCheckInput(checkLayout, "MASCULINO", centralWidget);
    checkLayout->addItem(new QSpacerItem(10, 1, QSizePolicy::Minimum, QSizePolicy::Minimum));
    female = addCheckInput(checkLayout, "FEMENINO", centralWidget);
    formLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));

    eMail = addTextInput(formLayout, "E-MAIL", centralWidget);
    formLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));
    password = addTextInput(formLayout, "CONTRASEÑA", centralWidget);
    formLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));
    password2 = addTextInput(formLayout, "REPETIR CONTRASEÑA", centralWidget);

    /*********/
    weight->setMaxLength(3);
    //connect(weight, SIGNAL(editingFinished()), this, SLOT(weightEditingFinished()));
    weight->setValidator(new QIntValidator(this));
    height->setMaxLength(3);
    //connect(height, SIGNAL(editingFinished()), this, SLOT(heightEditingFinished()));
    height->setValidator(new QIntValidator(this));
    age->setMaxLength(2);
    //connect(age, SIGNAL(editingFinished()), this, SLOT(ageEditingFinished()));
    age->setValidator(new QIntValidator(this));
    male->setChecked(true);
    password->setEchoMode(QLineEdit::Password);
    password2->setEchoMode(QLineEdit::Password);

    /********************************************************************/

    formLayout->addItem(new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Minimum));

    okButton = new SIButton(centralWidget);
    okButton->setObjectName(QString::fromUtf8("okButton"));
    okButton->setText(QString::fromUtf8("ACEPTAR"));
    //okButton->setGeometry(0, 0, 320, 48);
    okButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    okButton->setMinimumSize(320, 48);
    okButton->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    okButton->setNormalStatePix(":/images/res/legal_bot_aceptar.png");
    okButton->setPressedStatePix(":/images/res/legal_bot_aceptar_pressed.png");
    connect(okButton, SIGNAL(clicked()), this, SLOT(pressedOk()));
    formLayout->addWidget(okButton);

    m_scrollArea = new QScrollArea(centralWidget);
    m_scrollArea->setObjectName(QString("formViewScrollArea"));
    m_scrollArea->setStyleSheet(QString("QScrollArea#formViewScrollArea { background-color: rgba(255, 0, 0, 0); }"));
    m_scrollArea->setWidgetResizable(false);
    m_scrollArea->setWidget(layoutContainer);
    m_scrollArea->setGeometry(QRect(0, 0, 350, 436));
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_instance = this;

}

FormView::~FormView()
{

}

void FormView::weightEditingFinished()
{
    weight->setText(QString::number(weight->text().toInt()));
}

void FormView::heightEditingFinished()
{
    height->setText(QString::number(weight->text().toInt()));
}

void FormView::ageEditingFinished()
{
    age->setText(QString::number(weight->text().toInt()));
}

void FormView::showEvent(QShowEvent *)
{
    navigationController()->tabBar()->setUserInteractionEnabled(m_processOnlyForm);
    m_scrollArea->ensureVisible(0,0,0,0);

    m_headerView->backButton().setHidden(!m_processOnlyForm);
    m_headerView->homeButton().setHidden(true);
    m_headerView->setTitleImageFilename(":/images/res/header_titulo_miperfil.png");
    m_headerView->repaint();

#ifdef _DEVICE_BUILD
    //m_showFormWarning = false;
    emit okButton->click();
    //m_showFormWarning = true;
    m_scrollArea->setFocus();
    okButton->setFocus();
#endif

}

QLabel *FormView::addLabel(QVBoxLayout *formLayout, const QString &labelText, QWidget *parent)
{
    QLabel *label = new QLabel(parent);
    label->setObjectName(QString().sprintf("FormLabel%p", label));
    label->resize(300, 15);
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    label->setText(labelText);
    label->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 19px \"AvantGardeMdITCTT\"; }").arg(label->objectName()));
    formLayout->addWidget(label);

    return label;
}

QLineEdit *FormView::addTextInput(QVBoxLayout *formLayout, const QString &labelText, QWidget *parent)
{
    addLabel(formLayout, labelText, parent);

    QLineEdit *lineEdit = new QLineEdit(parent);
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
    lineEdit->setSizePolicy(sizePolicy);
    lineEdit->setMinimumSize(QSize(311, 73));
    lineEdit->setObjectName(QString().sprintf("FormLineEdit%p", lineEdit));
    lineEdit->setTextMargins(10, 0, 20, 0);
    lineEdit->setStyleSheet(QString("QLineEdit#%1 { color: rgb(255,255,255); font: 75 19px \"AvantGardeMdITCTT\"; background-image: url(:/images/res/formulario_base.png); }").arg(lineEdit->objectName()));
    formLayout->addWidget(lineEdit);

    return lineEdit;

}

QCheckBox *FormView::addCheckInput(QHBoxLayout *checkLayout, const QString &labelText, QWidget *parent)
{
    QCheckBox *checkBox = new QCheckBox(parent);
    checkBox->setObjectName(QString().sprintf("CheckBox%p", checkBox));
    checkBox->resize(200, 15);
    checkBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    checkBox->setText(labelText);
    checkBox->setStyleSheet(QString("QCheckBox#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 19px \"AvantGardeMdITCTT\"; }").arg(checkBox->objectName()));
    checkBox->setAutoExclusive(true);
    checkLayout->addWidget(checkBox);

    return checkBox;

}

QComboBox *FormView::addComboInput(QVBoxLayout *formLayout, const QString &labelText, QWidget *parent)
{
    addLabel(formLayout, labelText, parent);

    formLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));

    QComboBox *comboBox = new QComboBox(parent);
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
    comboBox->setSizePolicy(sizePolicy);
    comboBox->setMinimumSize(QSize(311, 32));
    comboBox->setObjectName(QString().sprintf("ComboBox%p", comboBox));
    comboBox->setStyleSheet(QString("QComboBox#%1 { color: rgb(222,222,222); background-image: url(:/images/res/comboBack.png); font: 75 19px \"AvantGardeMdITCTT\"; }").arg(comboBox->objectName()));
    formLayout->addWidget(comboBox);

    comboBox->insertItems(0, QStringList(GlobalDataObject::instance().userInfo().townMap().keys()));
    comboBox->setCurrentIndex(1);
    comboBox->setMaxVisibleItems(5);

    return comboBox;

}

void FormView::pressedOk()
{
    if( !m_showFormWarning )
        return;

    if( fullName->text().toLower().compare("dd9") != 0 ) // dd9 for debugging purposes, so we are not forced to fill the form each time
    {
        if( fullName->text().isEmpty() || eMail->text().isEmpty() || weight->text().isEmpty() || height->text().isEmpty() || password->text().isEmpty() || password2->text().isEmpty() || age->text().isEmpty() )
        {
            QMessageBox msgBox;
            msgBox.setText("Por favor, completá todos los campos del formulario!");
            msgBox.exec();
            return;
        }

        if( password->text().compare(password2->text()) != 0 )
        {
            QMessageBox msgBox;
            msgBox.setText("Ambas contraseñas deben ser iguales!");
            msgBox.exec();
            return;
        }

    }

    GlobalDataObject::instance().userInfo().setFullName(fullName->text());
    GlobalDataObject::instance().userInfo().setEMail(eMail->text());
    GlobalDataObject::instance().userInfo().setHomeTown(homeTown->currentText());
    GlobalDataObject::instance().userInfo().setWeight(weight->text());
    GlobalDataObject::instance().userInfo().setHeight(height->text());
    GlobalDataObject::instance().userInfo().setAge(age->text().toInt());
    GlobalDataObject::instance().userInfo().setGender(male->isChecked()?UserInfo::G_MALE:UserInfo::G_FEMALE);
    GlobalDataObject::instance().userInfo().setPassword(password->text());

    //GlobalDataObject::instance().saveApplicationSettings();

    // push next view
    pushObjectiveView(new FormObjectiveView());

}

void FormView::pushObjectiveView(FormObjectiveView *view)
{
    view->setHeaderView(m_headerView);
    navigationController()->pushView(view);

}
