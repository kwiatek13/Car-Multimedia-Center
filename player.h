#ifndef PLAYER_H
#define PLAYER_H

//#include "dialog.h"
//#include "playlist.h"
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <iostream>
#include <QSharedPointer>
#include <memory>

class playlist;

class player
{
int music_volume=100, shuffle_val=0;
std::shared_ptr<QMediaPlayer> music2;
std::shared_ptr<QMediaPlaylist> m_list;

public:
    player();

  //  playing();
    void odtworz(int tryb);
    void losuj();
    void seek(int pos);
    QMediaPlayer* getPlayer();
    void setPlaylist(std::shared_ptr<QMediaPlaylist> mpl);




};

#endif // PLAYER_H
