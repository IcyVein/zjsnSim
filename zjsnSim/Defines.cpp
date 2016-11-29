#include "Defines.h"

double courseCoef(COURSE course)
{
    switch (course)
    {
    case TAdv:
        return 1.15;
        break;
    case InSame:
        return 1.00;
        break;
    case InReverse:
        return 0.80;
        break;
    case TDisadv:
        return 0.65;
        break;
    default:
        return 0.0;
        break;
    }
}

double formationCoef(FORMATION formation, STAGE stage)
{
    if (stage != Night)
    {
        switch (formation)
        {
        case single:
            return 1.0;
            break;
        case complex:
            return 0.8;
            break;
        case wheel:
            return 0.75;
            break;
        case trapezoid:
            return 1.0;
            break;
        case horizontal:
            return 0.8;
            break;
        default:
            return 0;
            break;
        }
    }
    else
    {
        switch (formation)
        {
        case single:
            return 1.1;
            break;
        case complex:
            return 0.9;
            break;
        case wheel:
            return 1.0;
            break;
        case trapezoid:
            return 1.0;
            break;
        case horizontal:
            return 1.0;
            break;
        default:
            return 0;
            break;
        }
    }
}