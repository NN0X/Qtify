#ifndef PLAYLISTSUBMENU_H
#define PLAYLISTSUBMENU_H

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>

class playlistloader : public QWidget
{
    Q_OBJECT

public:
    playlistloader(QWidget *parent = nullptr);

private slots:
    void displayFileContent(QListWidgetItem *item);

private:
    void initUI();
    void loadPlaylists();

    QListWidget *fileList;
    QTextEdit *fileContent;
};

#endif // PLAYLISTSUBMENU_H
