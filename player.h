#ifndef PLAYER_H
#define PLAYER_H

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
#include <QElapsedTimer>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qmessagebox.h>

#include <vector>

#include "qlistwidget.h"
#include "song.h"

class Player : public QWidget
{
    Q_OBJECT
private:
    std::vector<Song *> songs;
    int currentSong;
    QProcess *playerProcess;

public:
    QWidget *parent;
    QPushButton *playButton;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QSlider *volumeBar;
    QSlider *progressBar;
    QLabel *songTitle;
    QLabel *songTime;
    QLabel *songDuration;
    QListWidget *songList;
    QListWidget *playlistList;
    QString playlistName;

    Player(QWidget *parent);
    ~Player();

    void init();
    void setupUI();

    void load(QString id);

    void play();
    void pause();
    void next();
    void prev();

    void stop();

    void update();

public slots:
    void onPlayButtonClick();
    void onNextButtonClick();
    void onPrevButtonClick();
    void onVolumeChange();
    void onProgressChange(int value);
    void loadPlaylists();
    void displaySongsInPlaylist(QListWidgetItem *item);
    void onsongselected(QListWidgetItem *item);
};
#endif // PLAYER_H
