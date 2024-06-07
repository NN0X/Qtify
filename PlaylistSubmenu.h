#ifndef PLAYLISTSUBMENU_H
#define PLAYLISTSUBMENU_H

#include "qpushbutton.h"
#include <QWidget>
#include <QListWidget>
#include <QTextEdit>

class playlistloader : public QWidget
{
    Q_OBJECT

public:
    playlistloader(QWidget *parent = nullptr);
    void loadPlaylists();
public slots:
    void createNewPlaylist();
    void deleteSelectedPlaylist();
    void openListFile();
private slots:
    void displayFileContent(QListWidgetItem *item);
    void addSongToPlaylist(QListWidgetItem *item);

private:
    void initUI();
    QListWidget *fileList;
    QListWidget *songList;
    QTextEdit *fileContent;
    QPushButton *newPlaylistButton;
    QPushButton *deletePlaylistButton;
    QPushButton *addButton;
};

#endif // PLAYLISTSUBMENU_H
