#include "HttpManager.h"
#include <QDebug>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>

HttpManager::HttpManager(QObject *parent)
    : QObject(parent)
{
    m_apiBaseUrl = QString(); // Set your REST API base URL in QML or here
}

void HttpManager::setApiBaseUrl(const QString &url)
{
    if (m_apiBaseUrl != url) {
        m_apiBaseUrl = url;
        emit apiBaseUrlChanged();
    }
}

void HttpManager::sendLightCommand(const QString &state)
{
    if (m_apiBaseUrl.isEmpty()) {
        qDebug() << "HttpManager: apiBaseUrl not set — skipping REST API call";
        emit lightCommandSent(false, "API URL not configured");
        return;
    }

    QUrl url(m_apiBaseUrl);
    if (!url.isValid()) {
        qDebug() << "HttpManager: invalid URL" << m_apiBaseUrl;
        emit lightCommandSent(false, "Invalid URL");
        return;
    }

    // API expects "command": "LED_ON" or "LED_OFF" (not "state": "ON"/"OFF")
    QString command = (state == "ON") ? "LED_ON" : "LED_OFF";
    QJsonObject body;
    body["command"] = command;
    QByteArray json = QJsonDocument(body).toJson(QJsonDocument::Compact);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::UserAgentHeader, "SmartHomeDashboard/1.0");

    if (m_pendingLightReply) {
        m_pendingLightReply->abort();
        m_pendingLightReply->deleteLater();
    }

    m_pendingLightReply = m_networkManager.post(request, json);

    connect(m_pendingLightReply, &QNetworkReply::finished,
            this, &HttpManager::onLightRequestFinished);

    // Print every command sent to AWS on Qt console
    qDebug().noquote() << "[AWS] Command sent to AWS:"
                       << "URL:" << m_apiBaseUrl
                       << "| Body:" << json;
}

void HttpManager::onLightRequestFinished()
{
    if (!m_pendingLightReply)
        return;

    QNetworkReply *reply = m_pendingLightReply;
    m_pendingLightReply = nullptr;

    bool success = (reply->error() == QNetworkReply::NoError);
    QString responseOrError;

    if (success) {
        responseOrError = QString::fromUtf8(reply->readAll());
        qDebug().noquote() << "[AWS] Response from AWS:" << responseOrError;
    } else {
        responseOrError = reply->errorString();
        qDebug().noquote() << "[AWS] Error from AWS:" << responseOrError;
    }

    reply->deleteLater();
    emit lightCommandSent(success, responseOrError);
}
