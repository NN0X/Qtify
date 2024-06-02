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

class Song
{
private:
    unsigned int timestamp;

public:
    QString id;
    QString title;

    Song(QString id);
    ~Song();

    void setTimestamp(unsigned int timestamp);
    unsigned int getTimestamp();
};

class Player : public QObject
{
    Q_OBJECT
private:
    Song *currentSong;
    QProcess *player;

public:
    QWidget *parent;
    QPushButton *playButton;
    QPushButton *next;
    QPushButton *prev;
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
    void nextSong();
    void prevSong();
    void setVolume(int volume);
    void setTimestamp(unsigned int timestamp);

    void updateProgress();

public slots:
    void onPlayButtonClick();
};

#endif // SONG_H