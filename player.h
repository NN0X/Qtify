#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QProcess>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <QElapsedTimer>
#include <QRegularExpression>

#include <vector>

#include "song.h"

class Player : public QObject
{
    Q_OBJECT
private:
    std::vector<Song *> songs;
    int currentSong;
    QProcess *playerProcess;

public:
    QWidget *parent;
    QPushButton *playButton;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QSlider *volumeBar;
    QSlider *progressBar;
    QLabel *songTitle;
    QLabel *songTime;
    QLabel *songDuration;

    Player(QWidget *parent);
    ~Player();

    void init();

    void load(QString id);

    void play();
    void pause();
    void next();
    void prev();

    void stop();

    void update();

public slots:
    void onPlayButtonClick();
    void onNextButtonClick();
    void onPrevButtonClick();
    void onVolumeChange();
    void onProgressChange(int value);
};

#endif // PLAYER_H