#ifndef DATADIALOG_H
#define DATADIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QDialogButtonBox;

class DataDialog : public QDialog
{
    Q_OBJECT

public:
    DataDialog();
    QLabel *x_label;
    QLineEdit *x_LineEdit;
    QLabel *y_label;
    QLineEdit *y_LineEdit;
    QLabel *m_pLabelMount;
    QLineEdit *m_pLineEditMount;
    QLabel *m_pLabelAngle;
    QLineEdit *m_pLineEditAngle;
    QLabel *m_pLabelCoef;
    QLineEdit *m_pLineEditCoef;
    QDialogButtonBox *okButton;
};

#endif // DATADIALOG_H
