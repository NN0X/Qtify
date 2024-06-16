#ifndef PLAYERMENU_H
#define PLAYERMENU_H
#include "player.h"
#include <QListWidget>
#include <QVBoxLayout>
class PlayerMenu : public QWidget
{
    Q_OBJECT
public:
    PlayerMenu(QWidget *parent = nullptr, Player *player = nullptr);
    ~PlayerMenu();
    void init();
    void setupUI();
    Player *player;
    QListWidget *playlistList;
private:
    QListWidget *songList;
    QString playlistName;
public slots:
    void loadPlaylists();
    void displaySongsInPlaylist(QListWidgetItem *item);
    void onsongselected(QListWidgetItem *item);
};
#endif // PLAYERMENU
