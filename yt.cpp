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
    songsDownloading = "";
    songsError = "";

    songList = new QListWidget(parent);
    songList->setGeometry(0, 20, 200, 180);
    songList->setSelectionMode(QAbstractItemView::SingleSelection);
    songList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    songList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    songList->show();

    connect(textInput, &QLineEdit::textChanged, this, &SearchMusicYT::textChanged);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]()
            { displaySongsFound(false); });
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

bool SearchMusicYT::songAlreadyDownloaded(QString song)
{
    song = song.replace(QRegularExpression("[^a-zA-Z0-9 ]"), "");
    QDir dir("resources/music");
    QStringList files = dir.entryList(QDir::Files);
    for (QString file : files)
    {
        // remove special characters
        file = file.replace(QRegularExpression("[^a-zA-Z0-9 ]"), "");
        if (file == song + "mp4")
        {
            return true;
        }
    }
    return false;
}

void SearchMusicYT::displaySongsFound(bool force)
{
    if (renderedSongsFound == songsFound && !force)
    {
        return;
    }
    songList->clear();

    for (QString song : songsFound.split("\n"))
    {
        song = song.left(song.length() - 1);
        if (song.isEmpty())
        {
            continue;
        }
        QListWidgetItem *item = new QListWidgetItem(song);
        if (songAlreadyDownloaded(song))
        {
            item->setForeground(Qt::green);
        }
        else if (songsDownloading.contains(song))
        {
            item->setForeground(Qt::blue);
        }
        else if (songsError.contains(song))
        {
            item->setForeground(Qt::red);
        }
        else
        {
            item->setForeground(Qt::black);
        }
        songList->addItem(item);
    }

    songList->show();

    renderedSongsFound = songsFound;
}

void SearchMusicYT::songListDoubleClicked(QListWidgetItem *item)
{
    songsDownloading += item->text() + "\n";
    displaySongsFound(true);

    QtConcurrent::run([this, item]
                      { SearchMusicYT::download(item->text()); });
}

void SearchMusicYT::download(QString name)
{
    QProcess *process = new QProcess();
    process->start("resources/bin/DownloadYT.exe", QStringList() << name);
    process->waitForFinished();
    if (songsDownloading.contains(name + "\n"))
    {
        songsDownloading = songsDownloading.replace(name + "\n", "");
    }

    delete process;

    displaySongsFound(true);
}