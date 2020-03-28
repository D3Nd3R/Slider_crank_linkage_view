#ifndef CRANKWIDGET_HPP
#define CRANKWIDGET_HPP

#include <QWidget>

class CrankWidget : public QWidget
{
    Q_OBJECT

    QColor m_backgrounColor{0,0,0};
    QColor m_circleColor{255,0,0};
    QColor m_crankColor{0,255,0};
    double m_crankAngle{0.};
    double m_crankPhaseShift{0.};

public:
    explicit CrankWidget(QWidget *parent = nullptr);


    Q_PROPERTY(QColor backgrounColor READ backgrounColor WRITE setBackgrounColor NOTIFY backgrounColorChanged)
    Q_PROPERTY(QColor circleColor READ circleColor WRITE setCircleColor NOTIFY circleColorChanged)
    Q_PROPERTY(QColor crankColor READ crankColor WRITE setCrankColor NOTIFY crankColorChanged)

    Q_PROPERTY(double crankAngle READ crankAngle WRITE setCrankAngleInt NOTIFY crankAngleChanged)
    Q_PROPERTY(double crankPhaseShift READ crankPhaseShift WRITE setCrankPhaseShift NOTIFY crankPhaseShiftChanged)

    QColor backgrounColor() const;
    QColor circleColor() const;
    double crankAngle() const;
    QColor crankColor() const;

    double crankPhaseShift() const;

public slots:
    void setBackgrounColor(QColor backgrounColor);
    void setCircleColor(QColor circleColor);
    void setCrankAngle(double crankAngle);
    void setCrankAngleInt(int crankAngle);
    void setCrankColor(QColor crankColor);

    void setCrankPhaseShift(double crankPhaseShift);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:

    void backgrounColorChanged(QColor backgrounColor);
    void circleColorChanged(QColor circleColor);
    void crankAngleChanged(double crankAngle);
    void crankColorChanged(QColor crankColor);
    void crankPhaseShiftChanged(double crankPhaseShift);
};

#endif // CRANKWIDGET_HPP
