#include "player.h"

Player::Player(QWidget *parent)
    : parent(parent), currentSong(nullptr), playerProcess(nullptr), previousSong(nullptr), nextSong(nullptr)
{
    playButton = new QPushButton("Play", parent);
    connect(playButton, &QPushButton::clicked, this, &Player::onPlayButtonClick);

    nextButton = new QPushButton("Next", parent);
    connect(nextButton, &QPushButton::clicked, this, &Player::onNextButtonClick);

    prevButton = new QPushButton("Previous", parent);
    connect(prevButton, &QPushButton::clicked, this, &Player::onPrevButtonClick);

    volume = new QSlider(Qt::Horizontal, parent);
    volume->setRange(0, 100);
    connect(volume, &QSlider::sliderReleased, this, &Player::onVolumeChange);

    progress = new QSlider(Qt::Horizontal, parent);
    progress->setRange(0, 100);
    progress->setTracking(false);
    connect(progress, &QSlider::sliderReleased, this, &Player::onProgressChange);

    currentSong = new Song();
    previousSong = new Song();
    nextSong = new Song();

    volume->setValue(50);
    progress->setValue(0);
    songTitle = new QLabel("Unknown", parent);
    songTime = new QLabel("--:--", parent);
    songDuration = new QLabel("--:--", parent);
}

Player::~Player()
{
    if (playerProcess != nullptr)
    {
        pause();
    }
    delete currentSong;
    delete previousSong;
    delete nextSong;
    delete playButton;
    delete nextButton;
    delete prevButton;
    delete volume;
    delete progress;
    delete songTitle;
    delete songTime;
    delete songDuration;
}

void Player::loadSong(QString id)
{
    pause();

    if (currentSong->getId() != "0")
    {
        delete previousSong;
        previousSong = currentSong;
    }
    else
        delete currentSong;

    currentSong = new Song(id);

    play();
}

void Player::play()
{
    if (currentSong->getId() == "0")
        return;

    playButton->setText("Pause");

    songTitle->setText(currentSong->getTitle());
    songTime->setText(QString::number(currentSong->getTime() / 60) + ":" + QString::number(currentSong->getTime() % 60));
    songDuration->setText(QString::number(currentSong->getDuration() / 60) + ":" + QString::number(currentSong->getDuration() % 60));

    if (playerProcess != nullptr)
        delete playerProcess;

    playerProcess = new QProcess();
    playerProcess->start("resources/bin/player.exe", QStringList() << currentSong->getId() << QString::number(currentSong->getTime()));
    QtConcurrent::run([this]
                      { Player::updateProgress(); });
}

void Player::pause()
{
    playButton->setText("Play");

    if (playerProcess != nullptr)
    {
        playerProcess->write("STOP\n");
        playerProcess->waitForFinished();
        delete playerProcess;
        playerProcess = nullptr;
    }
}

void Player::next()
{
    if (nextSong->getId() == "0")
    {
        return;
    }

    pause();

    delete previousSong;
    previousSong = currentSong;
    currentSong = nextSong;
    nextSong = new Song();

    play();
}

void Player::prev()
{
    if (previousSong->getId() == "0")
    {
        return;
    };

    pause();

    delete nextSong;
    nextSong = currentSong;
    currentSong = previousSong;
    previousSong = new Song();

    play();
}

void Player::updateProgress()
{
    QProcess *thisProcess = playerProcess;
    QElapsedTimer timer;
    timer.start();
    while (true)
    {
        QThread::msleep(100);
        if (timer.elapsed() >= 1000)
        {
            timer.restart();
        }
        else
            continue;
        if (playerProcess != thisProcess)
        {
            break;
        }
        currentSong->setTime(currentSong->getTime() + 1);
        songTime->setText(QString::number(currentSong->getTime() / 60) + ":" + QString::number(currentSong->getTime() % 60));
        progress->setValue(currentSong->getTime() * 100 / currentSong->getDuration());

        if (currentSong->getTime() >= currentSong->getDuration())
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

void Player::onNextButtonClick()
{
    next();
}

void Player::onPrevButtonClick()
{
    prev();
}

void Player::onVolumeChange()
{
    if (currentSong->getId() == "0")
        return;
}

void Player::onProgressChange()
{
    if (currentSong->getId() == "0")
        return;
}