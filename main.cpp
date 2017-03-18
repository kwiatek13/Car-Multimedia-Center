#include "dialog.h"
#include "player.h"
#include "playlist.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog w;
    //w.setList(pl);
//playlist plpl;
  //  player p(pl.getPlaylist());
//pl.setPlayer(p.getPlayer());
//w.setList(pl.getPlaylist());


    w.show();

    return a.exec();
}
