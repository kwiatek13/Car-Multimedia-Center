#include "dialog.h"
#include "ui_dialog.h"
#include "player.h"
#include "playlist.h"
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <iostream>

player::player()
{
    music2 = std::make_shared<QMediaPlayer>();

    //music2 ->setPlaylist(m_list.getPlaylist());

}


 void player::odtworz(int tryb)
{

    switch(tryb)
    {
    case 0:
        music2->play();
        break;

    case 1:
        music2->pause();
        break;
    }
  //  if(tryb == 0) tryb=1;
//    else tryb=0;

}

void player::losuj()
{
//music_list->shuffle();
}

void player::seek(int pos)
{
    music2->setPosition(pos);
}


QMediaPlayer* player::getPlayer()
{
    return music2.get(); //chyba moze zawisnac
}

void player::setPlaylist(std::shared_ptr<QMediaPlaylist> mpl)
{
    music2->setPlaylist(mpl.get());
}
