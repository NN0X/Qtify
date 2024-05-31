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

class SearchMusicYT : public QObject
{
    Q_OBJECT

public:
    QWidget *parent;
    QLineEdit *textInput;
    QString songsFound;
    QString renderedSongsFound;
    QListWidget *songList;

    SearchMusicYT(QMainWindow *parent);
    ~SearchMusicYT();

public slots:
    void textChanged(const QString &text);
    void displaySongsFound();
    void songListDoubleClicked(QListWidgetItem *item);
};

namespace YT
{
    void download(QString name);
}

#endif // YT_H