#include "yt.h"

SearchMusicYT::SearchMusicYT(QMainWindow *parent)
{
    this->parent = parent;

    textInput = new QLineEdit();
    textInput->setPlaceholderText("Enter song name...");
    textInput->setGeometry(0, 0, 200, 20);
    textInput->show();

    songsFound = "";
    renderedSongsFound = "";

    songList = new QListWidget(parent);
    songList->setGeometry(0, 20, 200, 180);
    songList->setSelectionMode(QAbstractItemView::SingleSelection);
    songList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    songList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    songList->show();

    connect(textInput, &QLineEdit::textChanged, this, &SearchMusicYT::textChanged);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SearchMusicYT::displaySongsFound);
    timer->start(10);

    connect(songList, &QListWidget::itemDoubleClicked, this, &SearchMusicYT::songListDoubleClicked);
}

SearchMusicYT::~SearchMusicYT()
{
    delete textInput;
}

void SearchMusicYT::textChanged(const QString &text)
{
    QtConcurrent::run([this, text]
                      {
        QProcess *process = new QProcess();
        process->start("resources/bin/SearchMusicYT.exe", QStringList() << text);
        process->waitForFinished();
        QString output = process->readAllStandardOutput();
        delete process;

        QMetaObject::invokeMethod(this, [this, output] {
            songsFound = output;
        }, Qt::QueuedConnection); });
}

void SearchMusicYT::displaySongsFound()
{
    if (renderedSongsFound == songsFound)
    {
        return;
    }
    songList->clear();

    for (QString song : songsFound.split("\n"))
    {
        if (song.isEmpty())
        {
            continue;
        }
        songList->addItem(song);
    }

    songList->show();

    renderedSongsFound = songsFound;
}

void SearchMusicYT::songListDoubleClicked(QListWidgetItem *item)
{
}