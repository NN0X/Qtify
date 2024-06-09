#include "yt.h"

SearchMusicYT::SearchMusicYT(QMainWindow *parent)
    : songList(new QListWidget(parent)), parent(parent), searchTerm(new QLineEdit()),
      songsFoundIDs(QStringList()), songsFoundTitles(QStringList()),
      songsAlreadyFoundIDs(QStringList()), songsDownloadingIDs(QStringList())
{
    searchTerm->setPlaceholderText("Enter song to find...");
    searchTerm->setGeometry(0, 0, 200, 20);
    searchTerm->show();

    searchTerm->setStyleSheet(
        "QLineEdit {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #289042);"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    padding: 10px 20px;"
        "}"
        );

    songList->setGeometry(0, 20, 200, 180);
    songList->setSelectionMode(QAbstractItemView::SingleSelection);
    songList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    songList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    songList->setStyleSheet(
        "QListWidget {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0  #1A1A1A);"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    padding: 10px 20px;"
        "}"
        );

    songList->show();

    connect(searchTerm, &QLineEdit::textChanged, this, &SearchMusicYT::onSearchTermChange);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]()
            { updateSongList(false); });
    timer->start(10);

    connect(songList, &QListWidget::itemDoubleClicked, this, &SearchMusicYT::onSongListDoubleClick);

    qDebug() << "SearchMusicYT initialized";
}

SearchMusicYT::~SearchMusicYT()
{
    delete searchTerm;
    delete songList;

    qDebug() << "SearchMusicYT destroyed";
}

void SearchMusicYT::onSearchTermChange(const QString &text)
{
    QtConcurrent::run([this, text]
                      {
        QProcess *process = new QProcess();
        process->start(RESOURCES_PATH + "/bin/SearchMusicYT.exe", QStringList() << text);
        process->waitForFinished();
        QString output = process->readAllStandardOutput();
        delete process;

        QMetaObject::invokeMethod(this, [this, output] {
            songsFoundIDs.clear();
            songsFoundTitles.clear();
            for (QString song : output.split("\n"))
            {
                if (song.isEmpty())
                {
                    continue;
                }
                QStringList songSplit = song.split("\t");
                songsFoundIDs.append(songSplit[1].remove(QRegularExpression("[\\r]")));
                songsFoundTitles.append(songSplit[0]);
            }
        }, Qt::QueuedConnection); });
}

bool SearchMusicYT::isAlreadyDownloaded(QString id)
{
    QDir dir(RESOURCES_PATH + "/music");
    QStringList files = dir.entryList(QDir::Files);
    for (QString file : files)
    {
        if (file.contains(id))
        {
            return true;
        }
    }
    return false;
}

void SearchMusicYT::updateSongList(bool force)
{
    if (songsAlreadyFoundIDs == songsFoundIDs && !force)
    {
        return;
    }
    songList->clear();

    for (int i = 0; i < songsFoundIDs.size(); i++)
    {
        if (songsFoundTitles[i].isEmpty())
        {
            continue;
        }
        QListWidgetItem *item = new QListWidgetItem(songsFoundTitles[i]);
        if (isAlreadyDownloaded(songsFoundIDs[i]))
        {
            item->setForeground(Qt::green);
        }
        else if (songsDownloadingIDs.contains(songsFoundIDs[i]))
        {
            item->setForeground(Qt::yellow);
        }
        else
        {
            item->setForeground(Qt::black);
        }
        songList->addItem(item);
    }

    songList->show();

    songsAlreadyFoundIDs = songsFoundIDs;
}

void SearchMusicYT::onSongListDoubleClick(QListWidgetItem *item)
{
    if (isAlreadyDownloaded(songsFoundIDs[songsFoundTitles.indexOf(item->text())]))
    {
        // go to player
        return;
    }
    else if (songsDownloadingIDs.contains(songsFoundIDs[songsFoundTitles.indexOf(item->text())]))
    {
        return;
    }

    QString id = songsFoundIDs[songsFoundTitles.indexOf(item->text())];

    qDebug() << "Downloading " << item->text() << " with id " << id;

    QtConcurrent::run([this, id]
                      { SearchMusicYT::download(id); });

    songsDownloadingIDs.append(id);
    updateSongList(true);
}

void SearchMusicYT::download(QString id)
{
    QProcess *process = new QProcess();
    process->start(RESOURCES_PATH + "/bin/DownloadYT.exe", QStringList() << id);
    process->waitForFinished();
    QString output = process->readAllStandardOutput();

    delete process;

    if (output.contains("ERROR"))
    {
        qDebug() << "Error downloading " << songsFoundTitles[songsFoundIDs.indexOf(id)];
    }
    else
    {
        qDebug() << "Downloaded " << songsFoundTitles[songsFoundIDs.indexOf(id)];

        addToDatabase(id, songsFoundTitles[songsFoundIDs.indexOf(id)]);
    }

    songsDownloadingIDs.removeOne(id);
    updateSongList(true);
}

void SearchMusicYT::addToDatabase(QString id, QString title)
{
    QFile file(RESOURCES_PATH + "/music/list.txt");
    if (!file.open(QIODevice::Append))
    {
        return;
    }
    QTextStream stream(&file);
    stream << id << "\t" << title << "\n";
    file.close();

    qDebug() << "Added " << title << " to database";
}
