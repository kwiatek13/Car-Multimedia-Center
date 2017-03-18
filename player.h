#ifndef PLAYER_H
#define PLAYER_H

//#include "dialog.h"
#include "playlist.h"
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <iostream>

//class playlist;

class player
{
int music_volume=100, shuffle_val=0;
QMediaPlayer* music2;
QMediaPlaylist* m_list;

public:
    player();

  //  playing();
    void odtworz(int tryb);
    void losuj();
    void seek(int pos);
    QMediaPlayer* getPlayer();
    void setPlaylist(QMediaPlaylist* mpl);




};

#endif // PLAYER_H
