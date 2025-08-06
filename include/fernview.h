#ifndef FERNVIEW_H
#define FERNVIEW_H

#include <QWidget>
#include <QVector>
#include <QSlider>
#include <QLabel>
#include "fernmodel.h"

class FernView : public QWidget {
    Q_OBJECT

public:
    FernView(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void setPoints(const QVector<FernModel::Point>& newPoints);

signals:
    void probabilitiesChanged(double p1, double p2, double p3, double p4);

private:
    QVector<FernModel::Point> points;
    QSlider *slider1, *slider2, *slider3, *slider4, *scaleSlider;
    QLabel *label1, *label2, *label3, *label4, *scaleLabel;
    double scaleFactor;
};

#endif // FERNVIEW_H
