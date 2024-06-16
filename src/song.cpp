#include "song.h"

Song::Song()
    : id("0"), title("Unknown"), time(0), duration(__UINT16_MAX__)
{
}

Song::Song(QString id)
    : id(id), time(0), duration(__UINT16_MAX__)
{
    load(id);
}

Song::~Song()
{
}

void Song::load(QString id)
{
    QFile file("resources/music/all songs.txt");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open file";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split("\t");
        if (fields[0] == id)
        {
            title = fields[1];
            break;
        }
    }
    file.close();

    if (title.isEmpty())
    {
        title = "Unknown";
    }

    QProcess *loadDuration = new QProcess();
    loadDuration->start("resources/bin/getDuration.exe", QStringList() << id);
    loadDuration->waitForFinished();
    QString output = loadDuration->readAllStandardOutput();
    delete loadDuration;

    duration = output.toUInt();

    if (duration == 0)
    {
        qDebug() << "Could not get duration";
        duration = __UINT16_MAX__;
    }
}

void Song::setTime(uint16_t pTime)
{
    time = pTime;
}

QString Song::getId()
{
    return id;
}

QString Song::getTitle()
{
    return title;
}

uint16_t Song::getTime()
{
    return time;
}

uint16_t Song::getDuration()
{
    return duration;
}
