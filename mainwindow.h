#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "yt.h"
#include "PlaylistSubmenu.h"
#include "player.h"
#include "PlayerMenu.h"

class SearchMusicYT;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Player *player;
    PlayerMenu *playerMenu;


private:
    Ui::MainWindow *ui;
    QVBoxLayout *layout;
    SearchMusicYT  *searchMusicYT;
    playlistloader *playlistloader;

private slots:
    void OpenMenu();
    void OpenPlaylistSubMenu();
    void OpenPlayerMenu();
};
#endif // MAINWINDOW_H
