#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <QObject>
#include <QtMqtt/QMqttClient>

class MqttManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(QString humidity READ humidity NOTIFY humidityChanged)

public:
    explicit MqttManager(QObject *parent = nullptr);

    // Called from QML
    Q_INVOKABLE void publishSwitch(const QString &device,
                                   const QString &state);

    // Getters
    QString temperature() const { return m_temperature; }
    QString humidity()   const { return m_humidity;   }

signals:
    void temperatureChanged();
    void humidityChanged();

private slots:
    void onMessageReceived(const QByteArray &message,
                           const QMqttTopicName &topic);

public:
    void connectToBroker();

private:
    QMqttClient m_client;

    QString m_temperature;
    QString m_humidity;
};

#endif // MQTTMANAGER_H
