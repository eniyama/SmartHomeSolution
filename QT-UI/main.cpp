/*#include <QGuiApplication>   //supports qt classes which manages qt gui application
#include <QQmlApplicationEngine>  //for loading and running qml files
#include <QQmlContext> //qml can access objects,properties,functions and signals from c++
#include "MqttManager.h"  //it includes header file which include mqtt communication

int main(int argc, char *argv[]) //starting point of application
{
    QGuiApplication app(argc, argv);//it creates instance of gui application,and manages event loops,input events and etc for gui

    QQmlApplicationEngine engine;//creates qml engine instance for load and run qml ui files

    // --- Create and expose MqttManager to QML ---
    MqttManager mqttManager;//creates an instance of mqttmanager class,that manages mqtt connection,public and subscribe options
    engine.rootContext()->setContextProperty("Mqtt", &mqttManager); //exposing mqttmanager to qml with name 'mqtt',changes in c++ properties will automatically updates on ui

    // --- Load the main QML file ---
    engine.load(QUrl(QStringLiteral("qrc:/SmartHome/qml/Main.qml")));

    if (engine.rootObjects().isEmpty()) //checks if qml file loaded successfully or not
        return -1;

    return app.exec();//programme runs until the app is closed
}*/
#include "MqttManager.h"
#include "HttpManager.h"
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MqttManager mqttManager;
    HttpManager httpManager;

    // AWS API Gateway endpoint for light control
    httpManager.setApiBaseUrl("https://3sd2hn2m3c.execute-api.ap-south-1.amazonaws.com/prod/control");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("mqttManager", &mqttManager);
    engine.rootContext()->setContextProperty("httpManager", &httpManager);

    engine.load(QUrl(QStringLiteral("qrc:/SmartHome/qml/Main.qml")));
    mqttManager.connectToBroker();

    return app.exec();
}
