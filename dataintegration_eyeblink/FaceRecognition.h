#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <QObject>
#include <QImage>
#include <QSet>
#include <QMutex>

class FaceRecognition : public QObject
{
    Q_OBJECT
public:
    explicit FaceRecognition(QObject *parent = nullptr);

    // Called from QML to send frames
    Q_INVOKABLE void processFrame(const QImage &frame);

signals:
    void faceDetected(int count);
    void faceRecognized(QString name);

private:
    bool modelsLoaded;
    QSet<QString> processedFrames;

    // 🔥 NEW: frame numbering counter
    int frameCounter;

    // 🔥 NEW: clear auto_frames folder on app start
    void clearAutoFramesFolder();

    // --- Python recognition helpers ---
    void startRecognitionTimer();
    void recognizeFace(const QString &imagePath);
};

#endif // FACERECOGNITION_H
