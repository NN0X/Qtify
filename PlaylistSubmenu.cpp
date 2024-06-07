#include "PlaylistSubmenu.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>


playlistloader::playlistloader(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    loadPlaylists();
}

void playlistloader::initUI()
{
    fileList = new QListWidget();
    fileContent = new QTextEdit();
    fileContent->setReadOnly(true);

    connect(fileList, &QListWidget::itemClicked, this, &playlistloader::displayFileContent);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(fileContent);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(fileList);

    newPlaylistButton = new QPushButton("New Playlist", this);
    rightLayout->addWidget(newPlaylistButton);
    connect(newPlaylistButton, &QPushButton::clicked, this, &playlistloader::createNewPlaylist);

    deletePlaylistButton = new QPushButton("Delete Playlist", this);
    rightLayout->addWidget(deletePlaylistButton);
    connect(deletePlaylistButton, &QPushButton::clicked, this, &playlistloader::deleteSelectedPlaylist);

    addButton = new QPushButton("+", this);
    leftLayout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &playlistloader::openListFile);

    songList = new QListWidget();
    leftLayout->addWidget(songList);
    connect(songList, &QListWidget::itemDoubleClicked, this, &playlistloader::addSongToPlaylist);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
}

void playlistloader::loadPlaylists()
{
    QFile file("resources/music/playlisty.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        fileList->clear();
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) {
                fileList->addItem(line);
            }
        }
        file.close();
    } else {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono pliku 'playlisty.txt'.");
    }
}

void playlistloader::displayFileContent(QListWidgetItem *item)
{
    QString filename = "resources/music/" + item->text() + ".txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        fileContent->clear();
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("\t");
            if (parts.size() == 2) {
                fileContent->append(parts[1]);
            }
        }
        file.close();
    } else {
        fileContent->setPlainText(QString("Nie znaleziono pliku '%1'.").arg(filename));
    }
}

void playlistloader::openListFile()
{
    QString filename = "resources/music/list.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        songList->clear();
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) {
                QStringList parts = line.split("\t");
                if (parts.size() == 2) {
                    QListWidgetItem *item = new QListWidgetItem(parts[1]);
                    item->setData(Qt::UserRole, parts[0]);
                    songList->addItem(item);
                }
            }
        }
        file.close();
    } else {
        QMessageBox::warning(this, "Błąd", "Nie można otworzyć pliku '" + filename + "'.");
    }
}


void playlistloader::createNewPlaylist()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("New Playlist"),
                                         tr("Playlist name:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        QString filename = "resources/music/" + text + ".txt";
        QFile newFile(filename);
        if (!newFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Błąd", "Nie można utworzyć pliku '" + filename + "'.");
            return;
        }
        newFile.close();

        QFile file("resources/music/playlisty.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << text << "\n";
            file.close();
            loadPlaylists();
        } else {
            QMessageBox::warning(this, "Błąd", "Nie można otworzyć pliku 'playlisty.txt' do zapisu.");
        }
    }

}
void playlistloader::deleteSelectedPlaylist()
{
    QListWidgetItem *item = fileList->currentItem();
    if (item) {
        QString playlistName = item->text();
        QString filename = "resources/music/" + playlistName + ".txt";
        QFile file("resources/music/playlisty.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QStringList lines;
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (line != playlistName) {
                    lines.append(line);
                }
            }
            file.close();

            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                foreach (const QString &line, lines) {
                    out << line << "\n";
                }
                file.close();
            } else {
                QMessageBox::warning(this, "Błąd", "Nie można otworzyć pliku 'playlisty.txt' do zapisu.");
                return;
            }

            QFile::remove(filename);  // Usuń plik playlisty
            loadPlaylists();
        } else {
            QMessageBox::warning(this, "Błąd", "Nie można otworzyć pliku 'playlisty.txt' do odczytu.");
        }
    } else {
        QMessageBox::warning(this, "Błąd", "Nie wybrano żadnej playlisty do usunięcia.");
    }
}
void playlistloader::addSongToPlaylist(QListWidgetItem *item)
{
    QString songCode = item->data(Qt::UserRole).toString();
    QString songName = item->text();

    QListWidgetItem *selectedItem = fileList->currentItem();
    if (selectedItem) {
        QString playlistName = selectedItem->text();
        QString filename = "resources/music/" + playlistName + ".txt";
        QFile file(filename);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << songCode << "\t" << songName << "\n";
            file.close();
            displayFileContent(selectedItem);
        } else {
            QMessageBox::warning(this, "Błąd", "Nie można otworzyć pliku '" + filename + "' do zapisu.");
        }
    } else {
        QMessageBox::warning(this, "Błąd", "Nie wybrano żadnej playlisty do dodania piosenki.");
    }
}
