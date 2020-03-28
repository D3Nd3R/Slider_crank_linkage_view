#include "crank_widget.hpp"

#include <QtGlobal>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>


#include <algorithm>
#include <math.h>
#include <type_traits>

//for angle == 0 crank goes on TOP
const double SHIFT_ANGLE = -90.;

template<class In,class Res>
Res floatPointToIntegral(In val){
    static_assert (std::is_integral<Res>::value, "floatPointToIntegral return value mast be integral");
    static_assert (std::is_floating_point<In>::value, "floatPointToIntegral input value mast be floating point");
    return static_cast<Res>(std::round(val));
}

double degToRad(double deg){
    return (deg*M_PI)/180.;
}

using  doubleToInt = decltype(floatPointToIntegral<double,int>(0));

CrankWidget::CrankWidget(QWidget *parent) : QWidget(parent)
{

}

QColor CrankWidget::backgrounColor() const
{
    return m_backgrounColor;
}

QColor CrankWidget::circleColor() const
{
    return m_circleColor;
}

double CrankWidget::crankAngle() const
{
    return m_crankAngle;
}

QColor CrankWidget::crankColor() const
{
    return m_crankColor;
}

void CrankWidget::setBackgrounColor(QColor backgrounColor)
{
    if (m_backgrounColor == backgrounColor)
        return;

    m_backgrounColor = backgrounColor;
    emit backgrounColorChanged(m_backgrounColor);
    repaint();
}

void CrankWidget::setCircleColor(QColor circleColor)
{
    if (m_circleColor == circleColor)
        return;

    m_circleColor = circleColor;
    emit circleColorChanged(m_circleColor);
    repaint();
}

void CrankWidget::setCrankAngle(double crankAngle)
{
    if (qFuzzyCompare(m_crankAngle, crankAngle))
        return;

    m_crankAngle = crankAngle;
    emit crankAngleChanged(m_crankAngle);
    repaint();
}

void CrankWidget::setCrankAngleInt(int crankAngle)
{
    setCrankAngle(static_cast<double>(crankAngle));
}

void CrankWidget::setCrankColor(QColor crankColor)
{
    if (m_crankColor == crankColor)
        return;

    m_crankColor = crankColor;
    emit crankColorChanged(m_crankColor);
}

void CrankWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QBrush noBrush(QColor(),Qt::BrushStyle::NoBrush);

    QBrush br(backgrounColor());

    painter.fillRect(0,0,width(),height(),br);

    //draw circle
    const int minSideSize {std::min(width(),height())};
    const int margin {floatPointToIntegral<double,int>(minSideSize * 0.03)};
    const int minSideThird {floatPointToIntegral<double, int>((minSideSize)/ 3.)};

    //find center of circle
    const int heightReal {height() - 2*margin};
    const QPoint circleCenter {doubleToInt(width() / 2),
                doubleToInt((5./6.)*heightReal + margin)};
    const int circleRadius {doubleToInt(minSideThird * 0.5)};
    const int rodLength{circleRadius * 2};
    Q_UNUSED(rodLength);

    const double angleRad {degToRad(crankAngle() + SHIFT_ANGLE)};
    const QPoint crankEndPos{doubleToInt(circleCenter.x() + (circleRadius * std::cos(angleRad))),
                doubleToInt(circleCenter.y() + (circleRadius * std::sin(angleRad)))};


    //draw crank radius and rod
    painter.setBrush(crankColor());
    painter.setPen(QPen(crankColor(),5));
    painter.drawLine(circleCenter,crankEndPos);


    // Draw crank circle and it's center
    painter.setBrush(noBrush);
    QPen circlePen(circleColor(), 5);
    painter.setPen(circlePen);
    painter.drawEllipse(circleCenter,circleRadius,circleRadius);

    painter.setBrush(circleColor());
    painter.drawEllipse(circleCenter, doubleToInt(circleRadius * 0.1),
                        doubleToInt(circleRadius * 0.1));

    QWidget::paintEvent(event);
}

void CrankWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePress " << event->pos();
}
