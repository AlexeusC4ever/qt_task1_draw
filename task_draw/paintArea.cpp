#include "paintArea.h"
#include <QtWidgets>

std::pair<double, double> PaintArea::findPoint(double x, double y,
                                               double& angle, double coef)
{
    std::pair<int, int> case1(x, y);
    std::pair<int, int> case2(x, y);
    double radAngle = angle * 0.0175;

    int width = m_Rect.width() + padding;
    int height = m_Rect.height() + padding;

    int quarter = 0;

    if (angle >= 0 && angle < 90)
    {
        quarter = 1;
        case1.first = width - 1;
        case1.second = y - (width - x - 1) * std::tan(radAngle);
        case2.second = padding;
        case2.first = x + y / std::tan(radAngle);
    }

    else if (angle >= 90 && angle < 180)
    {
        quarter = 2;
        case1.first = padding;
        case1.second = y - x * std::tan(M_PI - radAngle);
        case2.second = padding;
        case2.first = x - y / std::tan(M_PI - radAngle);
    }

    else if (angle >= 180 && angle < 270)
    {
        quarter = 3;
        case1.first = padding;
        case1.second = y + x * std::tan(radAngle - M_PI);
        case2.second = height - 1;
        case2.first = x - (height - 1 - y) / std::tan(radAngle - M_PI);
    }

    else if (angle >= 270 && angle < 360)
    {
        quarter = 4;
        case1.first = width - 1;
        case1.second = y + (width - 1 - x) * std::tan(2 * M_PI - radAngle);
        case2.second = height - 1;
        case2.first = x + (height - 1 - y) / std::tan(2 * M_PI - radAngle);
    }

    angle *= coef;

    if(case1.first >= padding && case1.first < width &&
            case1.second >= padding && case1.second < height)
    {
        switch(quarter)
        {
        case(1):
            angle = 180 - angle;
            break;
        case(2):
            angle = 180 - angle;
            break;
        case(3):
            angle = 540 - angle;
            break;
        case(4):
            angle = 540 - angle;
            break;
        }
       qDebug() << "----" << case1.first << "----" << case1.second << "----" << angle;
        return case1;
    }
    else{
        angle = 360 - angle;
        qDebug() << "----" << case2.first << "----" << case2.second << "----" << angle;
        return case2;
    }
}

SIDE findSide(std::pair<double, double> a, int width, int padding)
{
    SIDE side;

    if(a.first == padding) side = SIDE::LEFT;
    else if(a.second == padding) side = SIDE::UP;
    else if(a.first == width - 1 + padding) side = SIDE::RIGHT;
    else side = SIDE::DOWN;

    return side;
}

void PaintArea::printNumber(SIDE side,
                            std::pair<double, double> newPoint,
                            QString cstrC, QPainter& painter)
{
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    QPoint point;
    switch(side)
    {
        case(SIDE::DOWN):
            point = QPoint(newPoint.first,
                           newPoint.second + 0.7 *  padding);
        break;
        case(SIDE::UP):
            point = QPoint(newPoint.first,
                           newPoint.second - 0.3 * padding);
        break;
        case(SIDE::LEFT):
            point = QPoint(newPoint.first - 0.7 * padding,
                           newPoint.second);
        break;
        case(SIDE::RIGHT):
            point = QPoint(newPoint.first + 0.3 * padding,
                           newPoint.second);
        break;
    }

    const int cnFlags = Qt::TextSingleLine;

    //    QRect rectText(point, QSize(padding, padding));
    //    painter.drawRect(rectText);
    //    rectText.adjust(point.x(), point.y(), point.x(), point.y());
    //    painter.drawText(rectText, Qt::AlignCenter, cstrC);

    painter.drawText(point, cstrC);
}

void PaintArea::drawMirrorLine(QString x_, QString y_,
                               QString angle_, QString mount_, QString coef_)
{
    quint32 counter = 1;

    int x = std::stoi(x_.toStdString());
    int y = std::stoi(y_.toStdString());
    double angle = std::stod(angle_.toStdString());
    int mount = std::stoi(mount_.toStdString());
    double coef = std::stod(coef_.toStdString());

    int realx = x + padding;
    int realy = y + padding;

    if(coef > 1 || coef < 0){
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("&Ref coeficient"
                             " should be less than 1 and more than 0"));
        return;
    }

    QPainter painter(&m_Pixmap);
    QBrush brush(Qt::red, Qt::SolidPattern);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::red);
    painter.setBrush(brush);

    std::pair<double, double> newPoint = findPoint(realx, realy, angle, coef);

    SIDE side = findSide(newPoint, m_Rect.width(), padding);

    QString cstrC = QString::fromLocal8Bit(std::to_string(counter++));

    painter.drawLine(realx, realy, newPoint.first, newPoint.second);

    QColor redChange;
    QFont font("Arial", 8);
    painter.setFont(font);

    for(size_t i = 0; i < mount; ++i)
    {
        redChange = painter.pen().color();
        printNumber(side, newPoint, cstrC, painter);

        realx = newPoint.first;
        realy = newPoint.second;

        newPoint = findPoint(newPoint.first, newPoint.second, angle, coef);

        redChange.setRgb(redChange.red() * coef, 0, 0);
        painter.setPen(redChange);

        painter.drawLine(realx, realy, newPoint.first, newPoint.second);

        side = findSide(newPoint, m_Rect.width(), padding);

        cstrC = QString::fromLocal8Bit(std::to_string(counter++));
    }

    update();
}

void PaintArea::paintEvent(QPaintEvent* pEvent)
{   
    qDebug() << "PAINT()";
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
}

void PaintArea::resizeEvent(QResizeEvent* pEvent)
{
//    m_Pixmap.scaled(pEvent->size().width(),pEvent->size().height() ,Qt::KeepAspectRatio);

    qDebug() << "RESIZE()";
    m_Pixmap = QPixmap(pEvent->size());
    m_Rect = QRect(QPoint(padding, padding),
                   QSize(m_Pixmap.width() - 2 * padding,
                         m_Pixmap.height() - 2 * padding));

    m_Pixmap.fill(Qt::white);

    QPainter painter(&m_Pixmap);

    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap);
    QBrush brush(Qt::white, Qt::SolidPattern);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(pen);
    painter.setBrush(brush);

    painter.drawRect(m_Rect);
}

void PaintArea::clearPixMap()
{
    resizeEvent(new QResizeEvent(m_Pixmap.size(), m_Pixmap.size()));
    update();
}

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    padding = 20;
}
