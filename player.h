#ifndef SONG_H
#define SONG_H

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

class Song
{
private:
    unsigned int timestamp;
    unsigned int duration;

public:
    QString id;
    QString title;

    Song(QString id);
    ~Song();

    void setTimestamp(unsigned int timestamp);
    unsigned int getTimestamp();

    void setDuration(unsigned int duration);
    unsigned int getDuration();
};

class Player : public QObject
{
    Q_OBJECT
private:
    Song *previousSong;
    Song *currentSong;
    Song *nextSong;
    QProcess *player;

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

    void playSong(QString id);

    void play();
    void pause();
    void next();
    void prev();
    void setVolume(int volume);

    void updateProgress();

public slots:
    void onPlayButtonClick();
};

#endif // SONG_H