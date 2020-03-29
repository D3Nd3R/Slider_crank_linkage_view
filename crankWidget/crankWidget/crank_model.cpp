#include "crank_model.hpp"
#include <cmath>

const double SHIFT_ANGLE = -90.;

template<class In,class Res>
static Res floatPointToIntegral(In val){
    static_assert (std::is_integral<Res>::value,
            "floatPointToIntegral return value mast be integral");
    static_assert (std::is_floating_point<In>::value,
            "floatPointToIntegral input value mast be floating point");
    return static_cast<Res>(std::round(val));
}
using  doubleToInt = decltype(floatPointToIntegral<double,int>(0));

static double degToRad(double deg){
    return (deg*M_PI)/180.;
}
#if 0
static double euclidDist(const QPoint &lhs, const QPoint &rhs){
    return std::sqrt(std::pow(lhs.x() - rhs.x(),2) +
                     std::pow(lhs.y() - rhs.y(),2));
}
#endif
/**
 * @brief calcPistonPosition x = r*cos(A) + sqrt(L^2 - (r*sin(A)^2)
 * @param angle = A
 * @param circleRadius = r
 * @param rodLength L
 * @return x
 */
static double calcPistonPosition(double angle, double circleRadius, double rodLength){
    return circleRadius * std::cos(angle) +
            std::sqrt(std::pow(rodLength, 2) - std::pow(circleRadius * std::sin(angle), 2));
}



bool CrankModel::updateParams(int width,int height, double angle, double phase)
{
    if (width <= 0 || height <= 0) return false;


    const int minSideSize {std::min(width,height)};
    const int margin {floatPointToIntegral<double,int>(minSideSize * 0.03)};
    const int minSideThird {floatPointToIntegral<double, int>((minSideSize)/ 3.)};


    const int heightReal {height - 2*margin};
    circleCenter = {doubleToInt(width / 2),
                    doubleToInt((5./6.)*heightReal + margin)};
    circleRadius = doubleToInt(minSideThird * 0.5);
    const int rodLength{doubleToInt(circleRadius * 2.5)};

    const double angleRad {degToRad(angle + SHIFT_ANGLE + phase)};
    crankEndPos = {doubleToInt(circleCenter.x() + (circleRadius * std::cos(angleRad))),
                   doubleToInt(circleCenter.y() + (circleRadius * std::sin(angleRad)))};

    pistonPin = {circleCenter.x(), circleCenter.y() -
                 doubleToInt(calcPistonPosition(degToRad(angle + phase),
                 circleRadius,
                 rodLength))};

    pistonSize = {doubleToInt(circleRadius * .5), circleRadius};
    return true;
}
QPoint CrankModel::getCircleCenter() const noexcept
{
    return circleCenter;
}

int CrankModel::getCircleRadius() const noexcept
{
    return circleRadius;
}

QPoint CrankModel::getCrankEndPos() const noexcept
{
    return crankEndPos;
}

QPoint CrankModel::getPistonPin() const noexcept
{
    return pistonPin;
}

QSize CrankModel::getPistonSize() const noexcept
{
    return pistonSize;
}


