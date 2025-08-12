#ifndef FERNVIEW_H
#define FERNVIEW_H

#include <QWidget>
#include <QVector>
#include <QSlider>
#include <QLabel>
#include <QTimer>
#include <QPainterPath>
#include "fernmodel.h"

class FernView : public QWidget {
    Q_OBJECT

public:
    FernView(QWidget *parent = nullptr);
    ~FernView();

    void paintEvent(QPaintEvent *event) override;
    void setPoints(const QVector<FernModel::Point>& newPoints);

signals:
    void probabilitiesChanged(double p1, double p2, double p3, double p4);

private slots:
    void updateRotation();

private:
    QVector<FernModel::Point> points;
    QSlider *stemSlider, *leavesSlider, *branchesSlider, *tipsSlider, *scaleSlider, *speedAnimationSlider;
    QLabel *stemLabel, *leavesLabel, *branchesLabel, *tipsLabel, *scaleLabel, *speedAnimationLabel;
    double scaleFactor;
    double rotationAngleY;
    double rotationAngleX;
    double speedAni;
    QTimer *rotationTimer;
};

#endif // FERNVIEW_H
