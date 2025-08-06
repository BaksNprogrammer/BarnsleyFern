#ifndef FERNCONTROLLER_H
#define FERNCONTROLLER_H

#include <QObject>
#include "fernmodel.h"
#include "fernview.h"

class FernController : public QObject {
    Q_OBJECT

public:
    FernController(FernModel& model, FernView& view, QObject *parent = nullptr);

public slots:
    void generateFern();
    void updateProbabilities(double p1, double p2, double p3, double p4);

private:
    FernModel& model;
    FernView& view;
};

#endif // FERNCONTROLLER_H
