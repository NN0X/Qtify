#include "player.h"

Player::Player(QWidget *parent)
    : parent(parent), currentSong(-1), playerProcess(nullptr)
{
    playButton = new QPushButton("Play", parent);
    connect(playButton, &QPushButton::clicked, this, &Player::onPlayButtonClick);

    nextButton = new QPushButton("Next", parent);
    connect(nextButton, &QPushButton::clicked, this, &Player::onNextButtonClick);

    prevButton = new QPushButton("Prev", parent);
    connect(prevButton, &QPushButton::clicked, this, &Player::onPrevButtonClick);

    volumeBar = new QSlider(Qt::Horizontal, parent);
    volumeBar->setRange(0, 100);
    volumeBar->setValue(50);
    connect(volumeBar, &QSlider::valueChanged, this, &Player::onVolumeChange);

    progressBar = new QSlider(Qt::Horizontal, parent);
    connect(progressBar, &QSlider::sliderMoved, this, &Player::onProgressChange);

    songTitle = new QLabel("Unknown", parent);
    songTime = new QLabel("--:--", parent);
    songDuration = new QLabel("--:--", parent);

    init();
}

Player::~Player()
{
    if (playerProcess != nullptr)
    {
        QByteArray data("EXIT\n");
        playerProcess->write(data);
        playerProcess->waitForFinished();
        delete playerProcess;
    }

    for (Song *song : songs)
    {
        delete song;
    }

    delete playButton;
    delete nextButton;
    delete prevButton;
    delete volumeBar;
    delete progressBar;

    delete songTitle;
    delete songTime;
    delete songDuration;
}

void Player::init()
{
    playerProcess = new QProcess();
    playerProcess->start("resources/bin/player.exe");
}

void Player::load(QString id)
{
    songs.push_back(new Song(id));
    currentSong = songs.size() - 1;

    songTitle->setText(songs[currentSong]->getTitle());
    songDuration->setText(QString::number(songs[currentSong]->getDuration() / 60) + ":" + QString::number(songs[currentSong]->getDuration() % 60));
    progressBar->setValue(0);
    songTime->setText("0:00");

    QString data("LOAD\n" + songs[currentSong]->getId() + "\n" + QByteArray::number(songs[currentSong]->getTime()) + "\n" + QByteArray::number(volumeBar->value()) + "\n" + QByteArray::number(songs[currentSong]->getDuration()) + "\n");
    QByteArray dataBytes = data.toUtf8();
    playerProcess->write(dataBytes);

    playButton->setText("Pause");

    QtConcurrent::run([this]
                      { update(); });
}

void Player::play()
{
    QByteArray data("PLAY\n");
    playerProcess->write(data);
}

void Player::pause()
{
    QByteArray data("PAUSE\n");
    playerProcess->write(data);
}

void Player::next()
{
    currentSong++;
    if (currentSong >= songs.size())
    {
        currentSong--;
    }

    QString data("LOAD\n" + songs[currentSong]->getId() + "\n" + QByteArray::number(songs[currentSong]->getTime()) + "\n" + QByteArray::number(volumeBar->value()) + "\n" + QByteArray::number(songs[currentSong]->getDuration()) + "\n");
    QByteArray dataBytes = data.toUtf8();
    playerProcess->write(dataBytes);

    playButton->setText("Pause");
    songTitle->setText(songs[currentSong]->getTitle());
    songDuration->setText(QString::number(songs[currentSong]->getDuration() / 60) + ":" + QString::number(songs[currentSong]->getDuration() % 60));
    progressBar->setValue(0);
    songTime->setText("0:00");
}

void Player::prev()
{
    currentSong--;
    if (currentSong < 0)
    {
        currentSong++;
    }

    QString data("LOAD\n" + songs[currentSong]->getId() + "\n" + QByteArray::number(songs[currentSong]->getTime()) + "\n" + QByteArray::number(volumeBar->value()) + "\n" + QByteArray::number(songs[currentSong]->getDuration()) + "\n");
    QByteArray dataBytes = data.toUtf8();
    playerProcess->write(dataBytes);

    playButton->setText("Pause");
    songTitle->setText(songs[currentSong]->getTitle());
    songDuration->setText(QString::number(songs[currentSong]->getDuration() / 60) + ":" + QString::number(songs[currentSong]->getDuration() % 60));
    progressBar->setValue(0);
    songTime->setText("0:00");
}

void Player::stop()
{
    QByteArray data("STOP\n");
    playerProcess->write(data);
}

void Player::update()
{
    while (true)
    {
        QByteArray data("TIME\n");
        playerProcess->write(data);

        playerProcess->waitForReadyRead();
        QByteArray outputB = playerProcess->readAll();

        QString output = QString::fromUtf8(outputB).remove(QRegularExpression("[\\r]"));

        int time = 0;
        if (output.isEmpty())
        {
            continue;
        }
        if (output == "END\n")
        {
            next();
            continue;
        }
        else
            time = output.toInt();

        songs[currentSong]->setTime(time);

        progressBar->setValue(time * 100 / songs[currentSong]->getDuration());
        songTime->setText(QString::number(time / 60) + ":" + QString::number(time % 60));

        QThread::msleep(1000);
    }
}

void Player::onPlayButtonClick()
{
    if (playButton->text() == "Play")
    {
        play();
        playButton->setText("Pause");
    }
    else
    {
        pause();
        playButton->setText("Play");
    }
}

void Player::onNextButtonClick()
{
    if (currentSong + 1 >= songs.size())
    {
        return;
    }

    next();
}

void Player::onPrevButtonClick()
{
    if (currentSong - 1 < 0)
    {
        return;
    }

    prev();
}

void Player::onVolumeChange()
{
    QByteArray data("VOLUME\n" + QByteArray::number(volumeBar->value()) + "\n");
    playerProcess->write(data);
}

void Player::onProgressChange(int value)
{
    int time = value * songs[currentSong]->getDuration() / 100;

    QByteArray data("SKIP\n" + QByteArray::number(time) + "\n");
    playerProcess->write(data);
}
