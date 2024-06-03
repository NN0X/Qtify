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

void Song::setDuration(unsigned int duration)
{
    this->duration = duration;
}

unsigned int Song::getDuration()
{
    return duration;
}

Player::Player(QWidget *parent)
    : parent(parent), currentSong(nullptr), player(nullptr), previousSong(nullptr), nextSong(nullptr)
{
    playButton = new QPushButton("Play", parent);
    connect(playButton, &QPushButton::clicked, this, &Player::onPlayButtonClick);

    nextButton = new QPushButton("Next", parent);
    connect(nextButton, &QPushButton::clicked, this, &Player::next);

    prevButton = new QPushButton("Previous", parent);
    connect(prevButton, &QPushButton::clicked, this, &Player::prev);

    volume = new QSlider(Qt::Horizontal, parent);
    progress = new QSlider(Qt::Horizontal, parent);
    if (currentSong == nullptr)
    {
        currentSong = new Song("0");
    }
    songTitle = new QLabel(currentSong->title, parent);
    songTime = new QLabel("--:--", parent);
    songDuration = new QLabel("--:--", parent);
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
    if (currentSong->id != "0")
    {
        previousSong = currentSong;
        pause();
        currentSong = nullptr;
    }
    currentSong = new Song(id);
    songTitle->setText(currentSong->title);
    songTime->setText("--:--");
    songDuration->setText("--:--");
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
    QProcess *duration = new QProcess();
    duration->start("resources/bin/getDuration.exe", QStringList() << currentSong->id);
    duration->waitForFinished();
    QString output = duration->readAllStandardOutput();
    delete duration;

    currentSong->setDuration(output.toUInt());
    songDuration->setText(QString::number(currentSong->getDuration() / 60) + ":" + QString::number(currentSong->getDuration() % 60));

    player = new QProcess();
    player->start("resources/bin/player.exe", QStringList() << currentSong->id << QString::number(currentSong->getTimestamp()));
    QtConcurrent::run([this]
                      { Player::updateProgress(); });
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

    // to prevent updateProgress from doubleing
    QThread::sleep(1);
}

void Player::next()
{
    if (nextSong == nullptr)
    {
        return;
    }
    if (currentSong != nullptr)
    {
        delete currentSong;
    }
    currentSong = nextSong;
    nextSong = nullptr;
    playSong(currentSong->id);
}

void Player::prev()
{
    if (previousSong == nullptr)
    {
        return;
    }
    if (nextSong != nullptr)
    {
        delete nextSong;
    }
    nextSong = currentSong;
    currentSong = previousSong;
    previousSong = nullptr;
    playSong(currentSong->id);
}

void Player::updateProgress()
{
    while (player != nullptr)
    {
        QThread::sleep(1);
        if (player == nullptr)
        {
            break;
        }
        if (currentSong == nullptr)
        {
            break;
        }
        currentSong->setTimestamp(currentSong->getTimestamp() + 1);
        songTime->setText(QString::number(currentSong->getTimestamp() / 60) + ":" + QString::number(currentSong->getTimestamp() % 60));
        progress->setValue(currentSong->getTimestamp() * 100 / currentSong->getDuration());

        if (currentSong->getTimestamp() >= currentSong->getDuration())
        {
            next();
        }
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
