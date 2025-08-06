#include "fernview.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

FernView::FernView(QWidget *parent) : QWidget(parent), scaleFactor(50) {
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    // Создаем ползунки для вероятностей
    slider1 = new QSlider(Qt::Horizontal, this);
    slider2 = new QSlider(Qt::Horizontal, this);
    slider3 = new QSlider(Qt::Horizontal, this);
    slider4 = new QSlider(Qt::Horizontal, this);

    slider1->setRange(0, 100);
    slider2->setRange(0, 100);
    slider3->setRange(0, 100);
    slider4->setRange(0, 100);

    slider1->setValue(1);
    slider2->setValue(86);
    slider3->setValue(93);
    slider4->setValue(100);

    // Создаем метки для отображения значений вероятностей
    label1 = new QLabel("Probability 1: 0.01", this);
    label2 = new QLabel("Probability 2: 0.86", this);
    label3 = new QLabel("Probability 3: 0.93", this);
    label4 = new QLabel("Probability 4: 1.00", this);

    // Создаем ползунок для масштабирования
    scaleSlider = new QSlider(Qt::Horizontal, this);
    scaleSlider->setRange(10, 300);
    scaleSlider->setValue(scaleFactor);

    // Создаем метку для отображения значения масштаба
    scaleLabel = new QLabel(QString("Scale: %1").arg(scaleFactor), this);

    // Создаем компоновщик для ползунков и меток
    QVBoxLayout *sliderLayout = new QVBoxLayout();
    sliderLayout->addWidget(label1);
    sliderLayout->addWidget(slider1);
    sliderLayout->addWidget(label2);
    sliderLayout->addWidget(slider2);
    sliderLayout->addWidget(label3);
    sliderLayout->addWidget(slider3);
    sliderLayout->addWidget(label4);
    sliderLayout->addWidget(slider4);
    sliderLayout->addWidget(scaleLabel);
    sliderLayout->addWidget(scaleSlider);

    // Основной компоновщик для виджета
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addStretch(); // Добавляем растягивающийся элемент, чтобы ползунки были справа
    mainLayout->addLayout(sliderLayout);

    // Подключаем сигналы изменения значений ползунков с контекстом
    connect(slider1, &QSlider::valueChanged, this, [this](int value) {
        label1->setText(QString("Probability 1: %1").arg(value / 100.0));
        emit probabilitiesChanged(slider1->value() / 100.0, slider2->value() / 100.0,
                                  slider3->value() / 100.0, slider4->value() / 100.0);
    });
    connect(slider2, &QSlider::valueChanged, this, [this](int value) {
        label2->setText(QString("Probability 2: %1").arg(value / 100.0));
        emit probabilitiesChanged(slider1->value() / 100.0, slider2->value() / 100.0,
                                  slider3->value() / 100.0, slider4->value() / 100.0);
    });
    connect(slider3, &QSlider::valueChanged, this, [this](int value) {
        label3->setText(QString("Probability 3: %1").arg(value / 100.0));
        emit probabilitiesChanged(slider1->value() / 100.0, slider2->value() / 100.0,
                                  slider3->value() / 100.0, slider4->value() / 100.0);
    });
    connect(slider4, &QSlider::valueChanged, this, [this](int value) {
        label4->setText(QString("Probability 4: %1").arg(value / 100.0));
        emit probabilitiesChanged(slider1->value() / 100.0, slider2->value() / 100.0,
                                  slider3->value() / 100.0, slider4->value() / 100.0);
    });

    // Подключаем сигнал изменения значения ползунка масштаба
    connect(scaleSlider, &QSlider::valueChanged, this, [this](int value) {
        scaleFactor = value;
        scaleLabel->setText(QString("Scale: %1").arg(scaleFactor));
        update();
    });
}

void FernView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::green);

    int widgetWidth = width();
    int widgetHeight = height();

    for (const auto& point : std::as_const(points)) {
        int px = static_cast<int>(point.x * scaleFactor + widgetWidth / 4);
        int py = static_cast<int>(-point.y * scaleFactor + widgetHeight / 1.1);
        painter.drawPoint(px, py);
    }
}

void FernView::setPoints(const QVector<FernModel::Point>& newPoints) {
    points = newPoints;
    update();
}
