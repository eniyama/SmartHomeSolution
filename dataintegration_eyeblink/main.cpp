#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include "SDV.h"
#include "FaceRecognition.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QScopedPointer<SDV> can_speed(new SDV);
    FaceRecognition faceRec;   // ✅ create ONCE

    // ---------------- MAIN SCREEN ----------------
    QQuickView view;
    view.rootContext()->setContextProperty("can_speed", can_speed.data());
    view.rootContext()->setContextProperty("faceRec", &faceRec);   // 🔥 FIX
    view.setSource(QUrl("qrc:/main.qml"));
    view.setScreen(app.screens().first());
    view.show();

    // ---------------- HUD SCREEN ----------------
    QQuickView view2;
    view2.rootContext()->setContextProperty("can_speed", can_speed.data());
    view2.rootContext()->setContextProperty("faceRec", &faceRec);  // 🔥 FIX
    view2.setSource(QUrl("qrc:/hud.qml"));
    view2.setScreen(app.screens().last());
    view2.show();

    return app.exec();
}
