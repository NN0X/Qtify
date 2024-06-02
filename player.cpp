#include "player.h"

Song::Song(QString id)
    : id(id), timestamp(0)
{
    if (id == "0")
    {
        title = "Unknown";
        return;
    }

    QFile file("resources/music/list.txt");
    if (!file.open(QIODevice::ReadOnly))
    {
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
}

Song::~Song()
{
}

void Song::setTimestamp(unsigned int timestamp)
{
    this->timestamp = timestamp;
}

unsigned int Song::getTimestamp()
{
    return timestamp;
}

Player::Player(QWidget *parent)
    : parent(parent), currentSong(nullptr)
{
    playButton = new QPushButton("Play", parent);
    connect(playButton, &QPushButton::clicked, this, &Player::onPlayButtonClick);

    next = new QPushButton("Next", parent);
    prev = new QPushButton("Prev", parent);
    volume = new QSlider(Qt::Horizontal, parent);
    progress = new QSlider(Qt::Horizontal, parent);
    if (currentSong == nullptr)
    {
        currentSong = new Song("0");
    }
    songTitle = new QLabel(currentSong->title, parent);
    songTime = new QLabel("0:00", parent);
    songDuration = new QLabel("0:00", parent);
}

Player::~Player()
{
    if (player != nullptr)
    {
        pause();
    }
    delete currentSong;
}

void Player::playSong(QString id)
{
    if (currentSong != nullptr)
    {
        delete currentSong;
    }
    currentSong = new Song(id);
    songTitle->setText(currentSong->title);
    songTime->setText("0:00");
    songDuration->setText("0:00");
    progress->setValue(0);
    volume->setValue(50);

    play();
}

void Player::play()
{
    playButton->setText("Pause");

    if (player != nullptr)
    {
        delete player;
    }
    player = new QProcess();
    player->start("resources/bin/player.exe", QStringList() << currentSong->id << QString::number(currentSong->getTimestamp()));
    QString output = player->readAllStandardOutput();
    qDebug() << output;
}

void Player::pause()
{
    playButton->setText("Play");

    if (player != nullptr)
    {
        player->write("STOP\n");
        player->waitForFinished();
        delete player;
        player = nullptr;
    }
}

void Player::onPlayButtonClick()
{
    if (playButton->text() == "Play")
    {
        play();
    }
    else
    {
        pause();
    }
}
