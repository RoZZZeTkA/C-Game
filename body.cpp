#include "body.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2 * Pi;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}
