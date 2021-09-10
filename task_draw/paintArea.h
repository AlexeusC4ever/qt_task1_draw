#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>

enum SIDE
{
    UP, RIGHT, DOWN, LEFT
};

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = nullptr);

public slots:
    void clearPixMap();
    void drawMirrorLine(QString x_,
                        QString y_,
                        QString angle_,
                        QString mount_,
                        QString coef_);

protected:
    void resizeEvent(QResizeEvent* pEvent) override;
    void paintEvent(QPaintEvent* pEvent) override;

private:
    std::pair<double, double> findPoint(double x, double y, double& angle, double coef);
    void printNumber(SIDE side,
                     std::pair<double, double> newPoint,
                     QString cstrC, QPainter& painter);

    QPixmap m_Pixmap;
    QRect m_Rect;
    int padding;

};

#endif // PAINTAREA_H
