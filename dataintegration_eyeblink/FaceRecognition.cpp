#include "FaceRecognition.h"
#include <QDebug>
#include <QProcess>
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QFileInfoList>

FaceRecognition::FaceRecognition(QObject *parent)
    : QObject(parent),
    modelsLoaded(false),
    frameCounter(0)
{
    qDebug() << "FaceRecognition backend created for camera";
    clearAutoFramesFolder();
    startRecognitionTimer();
}

void FaceRecognition::clearAutoFramesFolder()
{
    QString folderPath = QDir::homePath() + "/webcam_capture/auto_frames";
    QDir dir(folderPath);

    if (!dir.exists()) {
        dir.mkpath(".");
        return;
    }

    QFileInfoList files = dir.entryInfoList(QStringList() << "*.jpg", QDir::Files);
    for (const QFileInfo &file : files) {
        QFile::remove(file.absoluteFilePath());
    }

    processedFrames.clear();
    frameCounter = 0;

    qDebug() << "auto_frames cleared, counter reset";
}

void FaceRecognition::processFrame(const QImage &frame)
{
    if (frame.isNull())
        return;

    QImage cpuImage = frame.convertToFormat(QImage::Format_RGB888);

    QString outputDir = QDir::homePath() + "/webcam_capture/auto_frames";
    QDir().mkpath(outputDir);

    QString filename = QString("%1/frame_%2.jpg")
                           .arg(outputDir)
                           .arg(frameCounter, 6, 10, QChar('0'));

    if (cpuImage.save(filename, "JPG")) {
        frameCounter++;
    }
}

void FaceRecognition::startRecognitionTimer()
{
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this]() {

        QString folderPath = QDir::homePath() + "/webcam_capture/auto_frames";
        QDir dir(folderPath);

        QFileInfoList list = dir.entryInfoList(
            QStringList() << "*.jpg",
            QDir::Files,
            QDir::Name
            );

        if (list.isEmpty())
            return;

        for (const QFileInfo &fileInfo : list) {
            QString path = fileInfo.absoluteFilePath();

            if (!processedFrames.contains(path)) {
                processedFrames.insert(path);
                recognizeFace(path);
                break;
            }
        }
    });

    timer->start(1200);
}

/*void FaceRecognition::recognizeFace(const QString &imagePath)
{
    QProcess *process = new QProcess(this);

    connect(process, &QProcess::finished, this,
            [this, process](int, QProcess::ExitStatus) {

                QString output = process->readAllStandardOutput().trimmed();
                qDebug() << "Recognition output:" << output;

                if (output == "DROWSY") {
                    qDebug() << "⚠⚠ DRIVER DROWSY ⚠⚠";
                    emit faceRecognized("DROWSY");
                    process->deleteLater();
                    return;
                }

                if (!output.isEmpty() && output != "OK") {
                    emit faceRecognized(output);
                }

                process->deleteLater();
            });

    //QTimer::singleShot(3500, process, &QProcess::kill);

    process->start(
        "python3",
        QStringList()
            << "/home/umadevi/face_recognition.py"
            << imagePath
        );
}*/
void FaceRecognition::recognizeFace(const QString &imagePath)
{
    QProcess *process = new QProcess(this);

    connect(process, &QProcess::finished, this,
            [this, process](int exitCode, QProcess::ExitStatus status) {

                if (status != QProcess::NormalExit) {
                    process->deleteLater();
                    return;
                }

                QString output = QString::fromUtf8(
                                     process->readAllStandardOutput()
                                     ).trimmed();

                if (output.isEmpty()) {
                    process->deleteLater();
                    return;
                }

                qDebug() << "Recognition output:" << output;

                if (output == "DROWSY") {
                    qDebug() << "⚠⚠ DRIVER DROWSY ⚠⚠";
                    emit faceRecognized("DROWSY");
                } else if (output != "OK") {
                    emit faceRecognized(output);
                }

                process->deleteLater();
            });

    process->start(
        "python3",
        QStringList()
            << "/home/umadevi/face_recognition.py"
            << imagePath
        );
}
