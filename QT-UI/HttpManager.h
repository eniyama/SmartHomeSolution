#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class HttpManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString apiBaseUrl READ apiBaseUrl WRITE setApiBaseUrl NOTIFY apiBaseUrlChanged)

public:
    explicit HttpManager(QObject *parent = nullptr);

    QString apiBaseUrl() const { return m_apiBaseUrl; }
    void setApiBaseUrl(const QString &url);

    // Call from QML when Light switch is toggled (state = "ON" or "OFF")
    Q_INVOKABLE void sendLightCommand(const QString &state);

signals:
    void apiBaseUrlChanged();
    void lightCommandSent(bool success, const QString &responseOrError);

private slots:
    void onLightRequestFinished();

private:
    QNetworkAccessManager m_networkManager;
    QString m_apiBaseUrl;
    QNetworkReply *m_pendingLightReply = nullptr;
};

#endif // HTTPMANAGER_H
