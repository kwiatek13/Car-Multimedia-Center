#ifndef PLAYLIST_H
#define PLAYLIST_H
//#include "dialog.h"

#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QFile>
#include <QTextStream>
#include <QDialog>
#include <QTime>
#include <QStringList>
#include <QDirIterator>
#include <QFileInfo>

class playlist:public QDialog
{
    Q_OBJECT

     QMediaPlaylist* music_list;
     QMediaPlayer* player_p;
     QFile playlist_file;
     QString buffer,current_list;
     QStringList list, del_buffer, playlist_list;
     QList<QMediaContent> playlist_content;
     QTextStream outStream;
     QList <QMediaContent> tracklist;
     QDir playlist_folder;
  //   QStringList playlist_files;
     int created=0, selected_index=0, random_index=0;
     QFileInfo info;

public:
   playlist();
   QList<QMediaContent> getContent();
 QMediaPlaylist* getPlaylist();
   void setPlaylist(QList<QMediaContent> content);
       void setPlayer(QMediaPlayer* pl);
       void next();
       void previous();
       void clear();
       void setIndex(int pos);
       void readPlaylist(QString pl_name);
       void writePlaylist(int position);
       void deleteEntry(int list_pos);
       void fun_start();
       void add_current();
       void list_playlists();
       QString returnPlaylistPath(int index_in_table);
       void create_playlist(QString name);
       void delete_current_playlist();

       signals:
       void returnPath(QString);
       void returnPathMain(QString);
       void returnPlaylistName(QString);

};

#endif // PLAYLIST_H
