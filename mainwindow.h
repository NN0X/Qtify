#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QMainWindow>
#include <QVBoxLayout>

#include "yt.h"
#include "PlaylistSubmenu.h"


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


private:
    Ui::MainWindow *ui;
    QVBoxLayout *layout;

    SearchMusicYT *searchMusicYT;
    playlistloader *playlistloader;

private slots:

    void OpenPlaylistSubMenu();

};
#endif // MAINWINDOW_H
