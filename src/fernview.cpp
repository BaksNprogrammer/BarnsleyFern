#include "fernview.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <cmath>

FernView::FernView(QWidget *parent) : QWidget(parent), scaleFactor(80), rotationAngleX(0), speedAni(1) {
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    // Создаем ползунки для различных частей папоротника
    stemSlider = new QSlider(Qt::Horizontal, this);
    leavesSlider = new QSlider(Qt::Horizontal, this);
    branchesSlider = new QSlider(Qt::Horizontal, this);
    tipsSlider = new QSlider(Qt::Horizontal, this);

    stemSlider->setRange(0, 100);
    leavesSlider->setRange(0, 100);
    branchesSlider->setRange(0, 100);
    tipsSlider->setRange(0, 100);

    stemSlider->setValue(1);
    leavesSlider->setValue(86);
    branchesSlider->setValue(93);
    tipsSlider->setValue(100);

    // Создаем метки для отображения значений
    stemLabel = new QLabel("Стебель: 0.01", this);
    leavesLabel = new QLabel("Листья: 0.86", this);
    branchesLabel = new QLabel("Ветви: 0.93", this);
    tipsLabel = new QLabel("Кончики: 1.00", this);

    // Создаем ползунок для масштабирования
    scaleSlider = new QSlider(Qt::Horizontal, this);
    scaleSlider->setRange(10, 200);
    scaleSlider->setValue(scaleFactor);

    // Создаем метку для отображения значения масштаба
    scaleLabel = new QLabel(QString("Масштаб: %0.01").arg(scaleFactor), this);

    //ползунок для скорости анимации
    speedAnimationSlider = new QSlider(Qt::Horizontal, this);
    speedAnimationSlider->setRange(0, 100);
    speedAnimationSlider->setValue(1);

    speedAnimationLabel = new QLabel(QString("Скорость анимации: %1").arg(speedAni/100), this);

    // Создаем компоновщик для ползунков и меток
    QVBoxLayout *sliderLayout = new QVBoxLayout();
    sliderLayout->addWidget(stemLabel);
    sliderLayout->addWidget(stemSlider);
    sliderLayout->addWidget(leavesLabel);
    sliderLayout->addWidget(leavesSlider);
    sliderLayout->addWidget(branchesLabel);
    sliderLayout->addWidget(branchesSlider);
    sliderLayout->addWidget(tipsLabel);
    sliderLayout->addWidget(tipsSlider);
    sliderLayout->addWidget(scaleLabel);
    sliderLayout->addWidget(scaleSlider);
    sliderLayout->addWidget(speedAnimationLabel);
    sliderLayout->addWidget(speedAnimationSlider);
     sliderLayout->addSpacing(height()/2);

    // Основной компоновщик для виджета
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addSpacing(width()*2);
    mainLayout->addLayout(sliderLayout);

    // Подключаем сигналы изменения значений ползунков с контекстом
    connect(stemSlider, &QSlider::valueChanged, this, [this](int value) {
        stemLabel->setText(QString("Стебель: %1").arg(value / 100.0));
        emit probabilitiesChanged(stemSlider->value() / 100.0, leavesSlider->value() / 100.0,
                                  branchesSlider->value() / 100.0, tipsSlider->value() / 100.0);
    });
    connect(leavesSlider, &QSlider::valueChanged, this, [this](int value) {
        leavesLabel->setText(QString("Листья: %1").arg(value / 100.0));
        emit probabilitiesChanged(stemSlider->value() / 100.0, leavesSlider->value() / 100.0,
                                  branchesSlider->value() / 100.0, tipsSlider->value() / 100.0);
    });
    connect(branchesSlider, &QSlider::valueChanged, this, [this](int value) {
        branchesLabel->setText(QString("Ветви: %1").arg(value / 100.0));
        emit probabilitiesChanged(stemSlider->value() / 100.0, leavesSlider->value() / 100.0,
                                  branchesSlider->value() / 100.0, tipsSlider->value() / 100.0);
    });
    connect(tipsSlider, &QSlider::valueChanged, this, [this](int value) {
        tipsLabel->setText(QString("Кончики: %1").arg(value / 100.0));
        emit probabilitiesChanged(stemSlider->value() / 100.0, leavesSlider->value() / 100.0,
                                  branchesSlider->value() / 100.0, tipsSlider->value() / 100.0);
    });

    // Подключаем сигнал изменения значения ползунка масштаба
    connect(scaleSlider, &QSlider::valueChanged, this, [this](int value) {
        scaleFactor = value;
        scaleLabel->setText(QString("Масштаб: %1").arg(scaleFactor));
        update();
    });
    connect(speedAnimationSlider, &QSlider::valueChanged, this, [this](int value){
        speedAni = value;
        speedAnimationLabel->setText(QString("Скорость анимации: %1").arg(speedAni/100));
        update();
    });

    // Создаем таймер для анимации вращения
    rotationTimer = new QTimer(this);
    connect(rotationTimer, &QTimer::timeout, this, &FernView::updateRotation);
    rotationTimer->start(1); // Обновляем каждые 50 мс
}

FernView::~FernView() {
    delete rotationTimer;
}

void FernView::updateRotation() {
    rotationAngleX += speedAni/100; // Увеличиваем угол вращения вокруг оси Y
    if (rotationAngleX >= 2 * M_PI) {
        rotationAngleX -= 2 * M_PI; // Сбрасываем угол, если он превышает 2π
    }
    update(); // Обновляем виджет для перерисовки
}

void FernView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0.2, Qt::green);
    gradient.setColorAt(0.6, Qt::black);
    painter.setPen(QPen(gradient, 0.7)); // Устанавливаем толщину линии

    int widgetWidth = width();
    int widgetHeight = height();

    for (const auto& point : std::as_const(points)) {
        // Применяем вращение вокруг оси Y
        double rotatedX = point.x * cos(rotationAngleX) - point.z * sin(rotationAngleX);
        double rotatedZ = point.x * sin(rotationAngleX) + point.z * cos(rotationAngleX);

        // Проецируем 3D координаты на 2D плоскость
        double distance = 50; // Расстояние до плоскости проекции
        double factor = distance / (distance + rotatedZ);
        int px = static_cast<int>(rotatedX * scaleFactor * factor + widgetWidth / 4);
        int py = static_cast<int>(-point.y * scaleFactor * factor + widgetHeight / 1.1);
        painter.drawPoint(px, py);
    }
}

void FernView::setPoints(const QVector<FernModel::Point>& newPoints) {
    points = newPoints;
    update();
}
