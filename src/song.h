#ifndef SONG_H
#define SONG_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QProcess>

class Song
{
private:
    QString id;
    QString title;
    uint16_t time;
    uint16_t duration;

public:
    Song();
    Song(QString id);
    ~Song();

    void load(QString id);

    void setTime(uint16_t pTime);

    QString getId();
    QString getTitle();
    uint16_t getTime();
    uint16_t getDuration();
};

#endif // SONG_H
