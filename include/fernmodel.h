#ifndef FERNMODEL_H
#define FERNMODEL_H

#include <QVector>

class FernModel {
public:
    struct Point {
        double x;
        double y;
        double z;
    };

    FernModel(double p1 = 0.01, double p2 = 0.86, double p3 = 0.93, double p4 = 1.0)
        : probability1(p1), probability2(p2), probability3(p3), probability4(p4) {}

    void setProbabilities(double p1, double p2, double p3, double p4) {
        probability1 = p1;
        probability2 = p2;
        probability3 = p3;
        probability4 = p4;
    }

    Point calculateNextPoint(const Point& current);

private:
    double probability1;
    double probability2;
    double probability3;
    double probability4;
};

#endif // FERNMODEL_H
