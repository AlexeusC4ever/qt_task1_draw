#include <QtWidgets>
#include "datadialog.h"

DataDialog::DataDialog()
{
    m_pLabelMount = new QLabel(QString::fromLocal8Bit("&Mount:"));
    m_pLineEditMount = new QLineEdit;
    m_pLabelMount->setBuddy(m_pLineEditMount);

    m_pLabelAngle = new QLabel(QString::fromLocal8Bit("&Angle:"));
    m_pLineEditAngle = new QLineEdit;
    m_pLabelAngle->setBuddy(m_pLineEditAngle);

    x_label = new QLabel(QString::fromLocal8Bit("X:"));
    x_LineEdit = new QLineEdit;
    x_label->setBuddy(x_LineEdit);

    y_label = new QLabel(QString::fromLocal8Bit("Y:"));
    y_LineEdit = new QLineEdit;
    y_label->setBuddy(y_LineEdit);


    m_pLabelCoef = new QLabel(QString::fromLocal8Bit("&Ref coefficient"));
    m_pLineEditCoef = new QLineEdit;
    m_pLabelCoef->setBuddy(m_pLineEditCoef);

    x_LineEdit->setText("12");
    y_LineEdit->setText("21");
    m_pLineEditAngle->setText("45");
    m_pLineEditMount->setText("45");
    m_pLineEditCoef->setText("0.98");

    okButton = new QDialogButtonBox(QDialogButtonBox::Ok);
    connect(okButton, SIGNAL(accepted()), this, SLOT(close()));

    QVBoxLayout *pLabelsLayout = new QVBoxLayout;
    pLabelsLayout->addWidget(x_label);
    pLabelsLayout->addWidget(y_label);
    pLabelsLayout->addWidget(m_pLabelMount);
    pLabelsLayout->addWidget(m_pLabelCoef);
    pLabelsLayout->addWidget(m_pLabelAngle);

    QVBoxLayout *pEditsLayout = new QVBoxLayout;
    pEditsLayout->addWidget(x_LineEdit);
    pEditsLayout->addWidget(y_LineEdit);
    pEditsLayout->addWidget(m_pLineEditMount);
    pEditsLayout->addWidget(m_pLineEditCoef);
    pEditsLayout->addWidget(m_pLineEditAngle);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(pLabelsLayout);
    mainLayout->addLayout(pEditsLayout);
    mainLayout->addWidget(okButton);

    setLayout(mainLayout);
}

