#include "MqttManager.h"
#include <QDebug>
#include <QtMqtt/QMqttTopicFilter>
#include <QtMqtt/QMqttTopicName>

MqttManager::MqttManager(QObject *parent)
    : QObject(parent)
{
    // MQTT broker details
    m_client.setHostname("192.168.0.19");   // your broker IP
    m_client.setPort(1883);
    m_client.setClientId("QtSmartHome");

    // ---------------- MQTT Connected ----------------
    connect(&m_client, &QMqttClient::connected, this, [=]() {
        qDebug() << "MQTT connected";

        // subscribe to sensor topics after connect
        m_client.subscribe(QMqttTopicFilter("home/temperature"));
        m_client.subscribe(QMqttTopicFilter("home/humidity"));
    });

    // ---------------- MQTT Disconnected ----------------
    connect(&m_client, &QMqttClient::disconnected, this, []() {
        qDebug() << "MQTT disconnected";
    });

    // ---------------- Incoming Messages ----------------
    connect(&m_client, &QMqttClient::messageReceived,
            this, &MqttManager::onMessageReceived);
}

// ----------------------------------------------------------
//  CONNECT to broker (called from main.cpp)
// ----------------------------------------------------------
void MqttManager::connectToBroker()
{
    qDebug() << "Connecting to MQTT broker...";
    m_client.connectToHost();
}

// ----------------------------------------------------------
//  PUBLISH Light / Switch State (called from QML)
// ----------------------------------------------------------
void MqttManager::publishSwitch(const QString &device,
                                const QString &state)
{
    if (m_client.state() != QMqttClient::Connected) {
        qDebug() << "MQTT not connected — cannot publish";
        return;
    }

    // topic format: home/<device>
    QString topic = "home/" + device;

    qint32 id = m_client.publish(topic,
                                 state.toUtf8(),
                                 0,
                                 false);

    qDebug() << "Publish →"
             << "Topic:" << topic
             << "State:" << state
             << "ID:" << id;
}

// ----------------------------------------------------------
//  HANDLE Incoming messages
// ----------------------------------------------------------
void MqttManager::onMessageReceived(const QByteArray &message,
                                    const QMqttTopicName &topic)
{
    const QString msg  = QString::fromUtf8(message);
    const QString name = topic.name();

    qDebug() << "MQTT RX →" << name << msg;

    if (name == "home/temperature") {
        m_temperature = msg;
        emit temperatureChanged();
    }
    else if (name == "home/humidity") {
        m_humidity = msg;
        emit humidityChanged();
    }
}
