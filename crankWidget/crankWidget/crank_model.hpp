#ifndef CRANKMODEL_HPP
#define CRANKMODEL_HPP

#include <QPoint>
#include <QSize>

class CrankModel
{
public:
    CrankModel() = default;

    bool updateParams(int width, int height, double angle, double phase);

    QPoint getCircleCenter() const noexcept;
    int getCircleRadius() const noexcept;

    QPoint getCrankEndPos() const noexcept;
    QPoint getPistonPin() const noexcept;
    QSize getPistonSize() const noexcept;

private:
    QPoint circleCenter{-1,-1};
    int circleRadius{0};

    QPoint crankEndPos{-1,-1};
    QPoint pistonPin{-1,-1};

    QSize pistonSize{-1,-1};
};

#endif // CRANKMODEL_HPP
