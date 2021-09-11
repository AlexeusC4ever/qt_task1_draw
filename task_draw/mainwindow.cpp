#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    data = new DataDialog;

    m_pButtonFind = new QPushButton(QString::fromLocal8Bit("&Clear"));

    m_areaForPaint = new PaintArea;
    m_areaForPaint->setAttribute(Qt::WA_NoSystemBackground, true);
    m_areaForPaint->setMinimumSize(500, 500);
    connect(m_pButtonFind, SIGNAL(clicked()), m_areaForPaint, SLOT(clearPixMap()));

    QVBoxLayout *pLayoutMain = new QVBoxLayout;
    pLayoutMain->addWidget(m_areaForPaint);
    pLayoutMain->addWidget(m_pButtonFind);

    showWidget = new QWidget;
    showWidget->setLayout(pLayoutMain);
    setCentralWidget(showWidget);

    connect(data->okButton, SIGNAL(accepted()), this, SLOT(sendDataToPixMap()));

    setWindowTitle(QString::fromLocal8Bit("&task_draw"));

    QMenu *pMenuFile = menuBar()->addMenu(tr("&File"));
    QAction *pActionFile = pMenuFile->addAction(
                tr("&Close"),
                this,
                SLOT(open()));
    connect(pActionFile, SIGNAL(triggered()), this, SLOT(close()));

    QMenu *pMenuData = menuBar()->addMenu(tr("&View"));
    QAction *pActionData = pMenuData->addAction(
                tr("&Data panel"),
                this,
                SLOT(open()));
    connect(pActionData, SIGNAL(triggered()), data, SLOT(show()));

    QMessageBox *help = new QMessageBox;


    QMenu *pMenuHelp = menuBar()->addMenu(tr("&Help"));
    QAction *pActionHelp = pMenuHelp->addAction(
                tr("&About"),
                this,
                SLOT(open()));
    connect(pActionHelp, SIGNAL(triggered()), help, SLOT(show()));

//    m_pActionSeparator = pMenuFile->addSeparator();
//    m_pActionSeparator->setVisible(false);
}

void MainWindow::sendDataToPixMap()
{
    if(data->x_LineEdit->text().isEmpty() ||
            data->y_LineEdit->text().isEmpty() ||
            data->m_pLineEditAngle->text().isEmpty() ||
            data->m_pLineEditMount->text().isEmpty() ||
            data->m_pLineEditCoef->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"), tr("&All fields must be filled in"));
        return;
    }



    m_areaForPaint->drawMirrorLine(data->x_LineEdit->text(),
                                   data->y_LineEdit->text(),
                                   data->m_pLineEditAngle->text(),
                                   data->m_pLineEditMount->text(),
                                   data->m_pLineEditCoef->text());
}

void MainWindow::open()
{

}

MainWindow::~MainWindow()
{

}

