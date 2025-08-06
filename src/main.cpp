
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "fernmodel.h"
#include "fernview.h"
#include "ferncontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "BarnsleyFern_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    FernModel model;
    FernView view;
    FernController controller(model, view);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    QTimer::singleShot(0, &controller, &FernController::generateFern);

    // Устанавливаем размер окна равным размеру экрана
    view.resize(screenGeometry.width(), screenGeometry.height());
    view.show();

    return a.exec();
}
