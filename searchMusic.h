#ifndef SEARCHMUSIC_H
#define SEARCHMUSIC_H

#include <QMainWindow>
#include <QObject>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QStringList>

class SearchMusic : public QObject
{
    Q_OBJECT

public:
    QWidget *parent;
    QLineEdit *textInput;
    QStringList songsFound;

    SearchMusic(QMainWindow *parent);
    ~SearchMusic();

public slots:
    void searchMusicTextChanged(const QString &text);
};

#endif // SEARCHMUSIC_H