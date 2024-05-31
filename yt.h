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

class SearchMusicYT : public QObject
{
    Q_OBJECT

public:
    QWidget *parent;
    QLineEdit *textInput;
    QListWidget *songList;

    QString songsFound;
    QString songsDownloading;
    QString songsError;
    QString renderedSongsFound;

    SearchMusicYT(QMainWindow *parent);
    ~SearchMusicYT();

    void download(QString name);

public slots:
    void textChanged(const QString &text);
    bool songAlreadyDownloaded(QString song);
    void displaySongsFound(bool force);
    void songListDoubleClicked(QListWidgetItem *item);
};

#endif // YT_H