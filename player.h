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

#include <vector>

#include "song.h"

class Player : public QObject
{
    Q_OBJECT
private:
    Song *previousSong;
    Song *currentSong;
    Song *nextSong;
    QProcess *playerProcess;

public:
    QWidget *parent;
    QPushButton *playButton;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QSlider *volume;
    QSlider *progress;
    QLabel *songTitle;
    QLabel *songTime;
    QLabel *songDuration;

    Player(QWidget *parent);
    ~Player();

    void loadSong(QString id);

    void play();
    void pause();
    void next();
    void prev();

    void updateProgress();

public slots:
    void onPlayButtonClick();
    void onNextButtonClick();
    void onPrevButtonClick();
    void onVolumeChange();
    void onProgressChange();
};

#endif // PLAYER_H