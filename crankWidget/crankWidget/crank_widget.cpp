#include "crank_widget.hpp"

#include <QtGlobal>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>


#include <algorithm>
#include <math.h>
#include <type_traits>


template<class In,class Res>
static Res floatPointToIntegral(In val){
    static_assert (std::is_integral<Res>::value, "floatPointToIntegral return value mast be integral");
    static_assert (std::is_floating_point<In>::value, "floatPointToIntegral input value mast be floating point");
    return static_cast<Res>(std::round(val));
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

double CrankWidget::crankPhaseShift() const
{
    return m_crankPhaseShift;
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
    repaint();
}

void CrankWidget::setCrankPhaseShift(double crankPhaseShift)
{
    if (qFuzzyCompare(m_crankPhaseShift, crankPhaseShift))
        return;

    m_crankPhaseShift = crankPhaseShift;
    emit crankPhaseShiftChanged(m_crankPhaseShift);
    repaint();
}

void CrankWidget::addCrankAngle(double angle)
{
    setCrankAngle(crankAngle() + angle);
}

void CrankWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QBrush noBrush(QColor(),Qt::BrushStyle::NoBrush);

    QBrush br(backgrounColor());

    painter.fillRect(0,0,width(),height(),br);

    crankModel.updateParams(width(),height(),crankAngle(),crankPhaseShift());

    //draw crank radius and rod
    painter.setBrush(crankColor());
    painter.setPen(QPen(crankColor(),5));
    painter.drawLine(crankModel.getCircleCenter(),crankModel.getCrankEndPos());
    painter.drawLine(crankModel.getCrankEndPos(),crankModel.getPistonPin());

    painter.drawRect(crankModel.getPistonPin().x() - crankModel.getPistonSize().width() / 2,
                     crankModel.getPistonPin().y() - crankModel.getPistonSize().height(),
                     crankModel.getPistonSize().width(), crankModel.getPistonSize().height());

    // Draw crank circle and it's center
    painter.setBrush(noBrush);
    QPen circlePen(circleColor(), 5);
    painter.setPen(circlePen);
    painter.drawEllipse(crankModel.getCircleCenter(),
                        crankModel.getCircleRadius(),crankModel.getCircleRadius());

    painter.setBrush(circleColor());
    painter.drawEllipse(crankModel.getCircleCenter(),
                        doubleToInt(crankModel.getCircleRadius() * 0.1),
                        doubleToInt(crankModel.getCircleRadius() * 0.1));

    QWidget::paintEvent(event);
}

void CrankWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePress " << event->pos();
}
