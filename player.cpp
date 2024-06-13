#include "player.h"
#include "mainwindow.h"

Player::Player(QWidget *parent)
    : parent(parent), currentSong(-1), playerProcess(nullptr)
{
    playlistList = new QListWidget(parent);
    playlistList->setStyleSheet(
        "QListWidget {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #011517, stop:1 #011519);"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    padding: 10px 20px;"
        "}"
        );
    songList = new QListWidget(parent);
    songList->setStyleSheet(
        "QListWidget {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #011517, stop:1 #011519);"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    padding: 10px 20px;"
        "}"
        );
    playButton = new QPushButton("Play", parent);
    playButton->setStyleSheet(
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
        );
    connect(playButton, &QPushButton::clicked, this, &Player::onPlayButtonClick);

    nextButton = new QPushButton("Next", parent);
    nextButton->setStyleSheet(
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
        );
    connect(nextButton, &QPushButton::clicked, this, &Player::onNextButtonClick);

    prevButton = new QPushButton("Prev", parent);
    prevButton->setStyleSheet(
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
        );
    connect(prevButton, &QPushButton::clicked, this, &Player::onPrevButtonClick);

    volumeBar = new QSlider(Qt::Horizontal, parent);
    volumeBar->setRange(0, 100);
    volumeBar->setValue(50);
    volumeBar->setStyleSheet(
        "QSlider {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #4CAF50);"
        "    color: white;"
        "    border: 2px solid #011519;"
        "    padding: 10px 20px;"
        "}"
        );
    connect(volumeBar, &QSlider::valueChanged, this, &Player::onVolumeChange);

    progressBar = new QSlider(Qt::Horizontal, parent);
    progressBar->setStyleSheet(
        "QSlider {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #4CAF50);"
        "    color: white;"
        "    border: 2px solid #011519;"
        "    padding: 10px 20px;"
        "}"
        );
    connect(progressBar, &QSlider::sliderMoved, this, &Player::onProgressChange);

    songTitle = new QLabel("Unknown", parent);
    songTitle->setStyleSheet(
        "QLabel {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #4CAF50);"
        "    color: white;"
        "    border: 2px solid #011519;"
        "    padding: 10px 20px;"
        "}"
        );
    songTime = new QLabel("--:--", parent);
    songTime->setStyleSheet(
        "QLabel {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #4CAF50);"
        "    color: white;"
        "    border: 2px solid #011519;"
        "    padding: 10px 20px;"
        "}"
        );
    songDuration = new QLabel("--:--", parent);
    songDuration->setStyleSheet(
        "QLabel {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #4CAF50);"
        "    color: white;"
        "    border: 2px solid #011519;"
        "    padding: 10px 20px;"
        "}"
        );
    connect(songList, &QListWidget::itemDoubleClicked, this, &Player::onsongselected);
    connect(playlistList, &QListWidget::itemDoubleClicked, this, &Player::displaySongsInPlaylist);
    loadPlaylists();
    init();
    setupUI();
}

Player::~Player()
{
    if (playerProcess != nullptr)
    {
        QByteArray data("EXIT\n");
        //playerProcess->write(data);
        playerProcess->terminate();
        //playerProcess->waitForFinished();
        delete playerProcess;
    }

    for (Song *song : songs)
    {
        delete song;
    }
/*
    delete playButton;
    delete nextButton;
    delete prevButton;
    delete volumeBar;
    delete progressBar;

    delete songTitle;
    delete songTime;
    delete songDuration;
*/
}

void Player::init()
{
    playerProcess = new QProcess();
    playerProcess->start("resources/bin/player.exe");
}
void Player::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *leftLayout = new QHBoxLayout();
    leftLayout->addWidget(playlistList);

    QHBoxLayout *centerLayout = new QHBoxLayout();
    leftLayout->addWidget(songList);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(centerLayout);
    setLayout(mainLayout);
}
void Player::load(QString id)
{
   // songs.push_back(new Song(id));
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
void Player::loadPlaylists() {
    QString filename = "resources/music/playlisty.txt";
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //QMessageBox::warning(this, tr("Błąd odczytu"), tr("Nie można otworzyć pliku playlisty.txt"));
        return;
    }
    playlistList->addItem("list");
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QListWidgetItem *item = new QListWidgetItem(line);
        playlistList->addItem(item);
    }
    file.close();
}

void Player::displaySongsInPlaylist(QListWidgetItem *item) {
    QString filename = "resources/music/" + item->text() + ".txt";
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //QMessageBox::warning(this, tr("Błąd odczytu"), tr("Nie można otworzyć pliku ") + filename);
        return;
    }

    songList->clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty()) {
            QStringList parts = line.split("\t");
            if (parts.size() == 2) {
                QListWidgetItem *item = new QListWidgetItem(parts[1]);
                item->setData(Qt::UserRole, parts[0]);
                songList->addItem(item);
            }
        }
    }
    file.close();
}
void Player::onsongselected(QListWidgetItem *item) {
    if (item) {
        QString songID = item->data(Qt::UserRole).toString();
        QListWidgetItem *playlistItem = playlistList->currentItem();
        if (playlistItem) {
            QString playlistName = playlistItem->text();
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
                    load(songID);
                    break;
                }
            }
        }
    }
}

