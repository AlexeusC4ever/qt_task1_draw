#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "paintArea.h"
#include "datadialog.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendDataToPixMap();
    void open();

private:
    DataDialog *data;
    QPushButton *m_pButtonFind;
    PaintArea *m_areaForPaint;
    QWidget *showWidget;
    QAction *m_pActionSeparator;
};  // class MainWindow

#endif // MAINWINDOW_H
