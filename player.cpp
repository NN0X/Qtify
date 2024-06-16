#include "player.h"
#include "mainwindow.h"

Player::Player(QWidget *parent)
    : parent(parent), currentSong(-1), playerProcess(nullptr)
{
    initPlayerToolbox();
    init();
}

Player::~Player()
{
}
void Player::initPlayerToolbox()
{
    QString playerbuttondesing=
        "QPushButton {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #011517, stop:1 #011519);"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #42a658);"
        "}"
        "QPushButton:pressed {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #289042);"
        "}"
        ;
    playButton = new QPushButton("Play", parent);
    playButton->setStyleSheet(playerbuttondesing);
    connect(playButton, &QPushButton::clicked, this, &Player::onPlayButtonClick);
    nextButton = new QPushButton("Next", parent);
    nextButton->setStyleSheet(playerbuttondesing);
    connect(nextButton, &QPushButton::clicked, this, &Player::onNextButtonClick);
    prevButton = new QPushButton("Prev", parent);
    prevButton->setStyleSheet(playerbuttondesing);
    connect(prevButton, &QPushButton::clicked, this, &Player::onPrevButtonClick);

    QString LabelAndSliderDesing=
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #4CAF50);"
        "    color: white;"
        "    border: 2px solid #011519;"
        "    padding: 10px 20px;"
        "}";
    volumeBar = new QSlider(Qt::Horizontal, parent);
    volumeBar->setRange(0, 100);
    volumeBar->setValue(50);
    volumeBar->setStyleSheet("QSlider {"+LabelAndSliderDesing);
    connect(volumeBar, &QSlider::valueChanged, this, &Player::onVolumeChange);

    progressBar = new QSlider(Qt::Horizontal, parent);
    progressBar->setStyleSheet("QSlider {"+LabelAndSliderDesing);
    connect(progressBar, &QSlider::sliderMoved, this, &Player::onProgressChange);

    songTitle = new QLabel("Unknown", parent);
    songTitle->setStyleSheet("QLabel {"+LabelAndSliderDesing);
    songTime = new QLabel("--:--", parent);
    songTime->setStyleSheet("QLabel {"+LabelAndSliderDesing);
    songDuration = new QLabel("--:--", parent);
    songDuration->setStyleSheet("QLabel {"+LabelAndSliderDesing);
}

void Player::init()
{
    playerProcess = new QProcess();
    playerProcess->start("resources/bin/player.exe");
}

void Player::load(QString id,int SongNr)
{
    if(SongNr>songs.size()) songs.push_back(new Song(id));
    if(SongNr<0) currentSong = songs.size() - 1;
    else currentSong=SongNr;
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

void Player::loadplaylist(QListWidgetItem *item, const QString &playlistName) {
    if (item) {
        QString songID = item->data(Qt::UserRole).toString();
         // QString playlistName = playlistItem->text();
            QString filename = "resources/music/" + playlistName + ".txt";
            QFile file(filename);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Could not open playlist file";
                return;
            }
            songs.clear();
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split("\t");
                if (parts.size() == 2) {
                    songs.push_back(new Song(parts[0]));
                }
            }
            file.close();

            for (int i = 0; i < songs.size(); ++i) {
                if (songs[i]->getId() == songID) {
                    currentSong = i;
                    load(songID,i);
                    break;
                }
            }
    }
}
