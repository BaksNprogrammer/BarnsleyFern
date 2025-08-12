#include "fernmodel.h"
#include <QRandomGenerator>

FernModel::Point FernModel::calculateNextPoint(const Point& current) {
    double r = QRandomGenerator::global()->generateDouble();
    Point nextPoint;

    if (r < probability1) {
        nextPoint.x = 0;
        nextPoint.y = 0.16 * current.y;
    } else if (r < probability2) {
        nextPoint.x = 0.85 * current.x + 0.04 * current.y;
        nextPoint.y = -0.04 * current.x + 0.85 * current.y + 1.6;
    } else if (r < probability3) {
        nextPoint.x = 0.2 * current.x - 0.26 * current.y;
        nextPoint.y = 0.23 * current.x + 0.22 * current.y + 1.6;
    } else {
        nextPoint.x = -0.15 * current.x + 0.28 * current.y;
        nextPoint.y = 0.26 * current.x + 0.24 * current.y + 0.44;
    }


    nextPoint.z = 0.1 * nextPoint.x;

    return nextPoint;
}
