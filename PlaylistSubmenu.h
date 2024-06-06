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
private slots:
    void displayFileContent(QListWidgetItem *item);
private:
    void initUI();
    QListWidget *fileList;
    QTextEdit *fileContent;
    QPushButton *newPlaylistButton;
};

#endif // PLAYLISTSUBMENU_H
