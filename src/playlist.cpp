#include "playlist.h"
#include "qlineedit.h"

playlist::playlist(QMainWindow *parent)
  : PlaylistList(new QListWidget(parent)), parent(parent), searchPlaylist(new QLineEdit())
{
        searchPlaylist->setPlaceholderText("Enter Playlist to find...");
        searchPlaylist->setGeometry(0, 0, 20, 20);
        searchPlaylist->show();

        PlaylistList->setGeometry(0, 20, 200, 180);
        PlaylistList->setSelectionMode(QAbstractItemView::SingleSelection);
        PlaylistList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        PlaylistList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        PlaylistList->show();

        //to do: double click na playliste , double click na song by dodac
//      connect(searchPlaylist, &QLineEdit::textChanged, this, &playlist::onSearchTermChange);
//        connect(songList, &QListWidget::itemDoubleClicked, this, &SearchMusicYT::onSongListDoubleClick);

        qDebug() << "SearchMusicYT initialized";
}
    void playlist::load_playlist(QString PLName)
    {
        QString path="resources/music/"+PLName;
        QFile playlistfile(path);
    }
    void playlist::open_list_of_playlists()
    {
        QFile file("resources/music/playlisty.txt");
        if (!file.open(QIODevice::Append))
        {
           qDebug() << "playlisty.txt was not opened";
        }

        QTextStream stream(&file);
        QString PLName;
        while (!stream.atEnd())
        {
            PLName = stream.readLine();
            playlist::load_playlist(PLName);
           // stream++;
        }
        file.close();

        qDebug() << "Succesfully opened playlists file";
    }
