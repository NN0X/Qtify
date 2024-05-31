#include "searchMusic.h"

SearchMusic::SearchMusic(QMainWindow *parent)
{
    this->parent = parent;

    textInput = new QLineEdit();
    textInput->setPlaceholderText("Search music");
    textInput->setGeometry(0, 0, 200, 20);
    textInput->show();

    songsFound = QStringList();

    connect(textInput, &QLineEdit::textChanged, this, &SearchMusic::searchMusicTextChanged);
}

SearchMusic::~SearchMusic()
{
    delete textInput;
}

void SearchMusic::searchMusicTextChanged(const QString &text)
{
    songsFound.clear();
    songsFound << "Song 1" << "Song 2" << "Song 3";
    qDebug() << songsFound;
}