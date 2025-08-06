#include "ferncontroller.h"
#include <QTimer>

FernController::FernController(FernModel& model, FernView& view, QObject *parent)
    : QObject(parent), model(model), view(view) {

    connect(&view, &FernView::probabilitiesChanged, this, &FernController::updateProbabilities);
}

void FernController::generateFern() {
    QVector<FernModel::Point> points;
    FernModel::Point currentPoint{0, 0};

    for (int i = 0; i < 100000; ++i) {
        currentPoint = model.calculateNextPoint(currentPoint);
        points.append(currentPoint);
    }

    view.setPoints(points);
}

void FernController::updateProbabilities(double p1, double p2, double p3, double p4) {
    model.setProbabilities(p1, p2, p3, p4);
    generateFern();
}
