#ifndef YT_H
#define YT_H

#include <QMainWindow>
#include <QObject>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QStringList>
#include <QProcess>
#include <QListWidget>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>
#include <QAbstractItemView>
#include <QRegularExpression>

const QString RESOURCES_PATH = "resources";

class SearchMusicYT : public QObject
{
    Q_OBJECT

public:
    QWidget *parent;
    QLineEdit *searchTerm;
    QListWidget *songList;

    QStringList songsFoundIDs;
    QStringList songsFoundTitles;
    QStringList songsAlreadyFoundIDs;
    QStringList songsDownloadingIDs;

    SearchMusicYT(QMainWindow *parent);
    ~SearchMusicYT();

    void download(QString id);

public slots:
    void onSearchTermChange(const QString &text);
    bool isAlreadyDownloaded(QString id);
    void updateSongList(bool force);
    void onSongListDoubleClick(QListWidgetItem *item);
    void addToDatabase(QString id, QString title);
};

#endif // YT_H