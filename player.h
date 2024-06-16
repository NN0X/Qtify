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

public:
    std::vector<Song *> songs;
    QWidget *parent;
    QProcess *playerProcess;
    QPushButton *playButton;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QSlider *volumeBar;
    QSlider *progressBar;
    QLabel *songTitle;
    QLabel *songTime;
    QLabel *songDuration;
    int currentSong;
    void loadplaylist(QListWidgetItem *item, const QString &playlistName);

    Player(QWidget *parent);
    ~Player();
    void initPlayerToolbox();
    void init();
    void load(QString id,int SongNr);

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
};
#endif // PLAYER_H
