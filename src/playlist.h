#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QMainWindow>
#include <QWidget>
#include <QObject>

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QListWidget>

//const QString RESOURCES_PATH = "resources";

class playlist : public QObject
{
    //Q_OBJECT
public:
    QWidget *parent;
    QLineEdit *searchPlaylist;
    QLineEdit *searchSonglist;
    QListWidget *PlaylistList;
    QListWidget *SongsList;

    playlist(QMainWindow *parent);
    void onSearchTermChange(const QString &text);
    void create();
    void add_song();
    void remove_song();
    bool song_is_here();
    void open_lis_of_songs();
    void open_list_of_playlists();
    void load_playlist(QString PlayListName);

   // ~playlist();
};

#endif // PLAYLIST_H
