#include "playlist.h"
#include "player.h"
#include <QMediaPlaylist>

playlist::playlist()
{
    playlist_file.setFileName("/home/lukas/playlist");

    playlist_file.open(QIODevice::ReadWrite);

outStream.setDevice(&playlist_file);

}


std::shared_ptr<QMediaPlaylist> playlist::getPlaylist()
{
  //  QMediaPlaylist* music_list_get;
  //  music_list_get = new QMediaPlaylist(music_list_get);

    auto music_list_get = music_list;

    //return music_list_get;
    return music_list;
}

void playlist::setPlaylist(QList<QMediaContent> content)
{
    music_list->addMedia(content);
    tracklist = content;
}

void playlist::setPlayer(QMediaPlayer *pl)
{
 if(created == 0)  music_list = std::make_shared<QMediaPlaylist>(pl);
    created=1;
}


void playlist::next()
{
   music_list->next();
}

void playlist::previous()
{
    music_list->previous();
}

void playlist::clear()
{
    music_list->clear();
}

void playlist::setIndex(int pos)
{
    music_list->setCurrentIndex(pos);
}


void playlist::readPlaylist(QString pl_name)
{
    playlist_content.clear();
    if(playlist_file.exists()) playlist_file.close();
    playlist_file.setFileName("/home/lukas/"+pl_name);

    playlist_file.open(QIODevice::ReadWrite);

    while(!playlist_file.atEnd())
    {
        list.clear();
        buffer = playlist_file.readLine();
        list = buffer.split("\n");
        playlist_content.push_back(QUrl::fromLocalFile(list.first()));
        emit returnPath(buffer);
    }

current_list = pl_name;

}

void playlist::writePlaylist(int position)
{

    outStream << tracklist[position].canonicalUrl().path() << "\n";
    outStream.flush();
}

void playlist::deleteEntry(int list_pos)
{
     playlist_file.seek(0);
    del_buffer.clear();
    selected_index=0;
    while(!playlist_file.atEnd())
    {


        if(list_pos != selected_index) del_buffer.push_back(playlist_file.readLine());
        if(list_pos == selected_index) playlist_file.readLine();

        selected_index++;
    }

    playlist_file.resize(0);
    for(int z=0;z<del_buffer.size();z++)
    {
       outStream << del_buffer[z];
    }
    outStream.flush();



}


void playlist::fun_start()
{
    poczatek:
    playlist_file.close();
    music_list->clear();
    playlist_content.clear();
    playlist_file.setFileName("/home/lukas/fun_playlist");

    playlist_file.open(QIODevice::ReadWrite);



    if(playlist_file.size()>0)
    {
    qsrand(QTime::currentTime().msec());

   // random_index = 1;
    while(!playlist_file.atEnd())
    {
        list.clear();
        buffer = playlist_file.readLine();
        list = buffer.split("\n");
        playlist_content.push_back(QUrl::fromLocalFile(list.first()));
    }
    random_index = qrand()%playlist_content.size();
    music_list->addMedia(playlist_content[random_index]);

    deleteEntry(random_index);
    }
    else
    {
        playlist_file.close();
        playlist_file.setFileName("/home/lukas/playlist");
        playlist_file.open(QIODevice::ReadWrite);
        playlist_file.seek(0);
        del_buffer.clear();
        while(!playlist_file.atEnd()) del_buffer.push_back(playlist_file.readLine());

        playlist_file.close();
        playlist_file.setFileName("/home/lukas/fun_playlist");
        playlist_file.open(QIODevice::ReadWrite);
        for(int z=0;z<del_buffer.size();z++)
        {
           outStream << del_buffer[z];
        }
        outStream.flush();
goto poczatek;




    }
}


void playlist::add_current()
{
    music_list->clear();
    music_list->addMedia(playlist_content);
playlist_file.seek(0);
    while(!playlist_file.atEnd())
    {
        list.clear();
        buffer = playlist_file.readLine();
        list = buffer.split("\n");
        playlist_content.push_back(QUrl::fromLocalFile(list.first()));
        emit returnPathMain(buffer);
    }
}


void playlist::list_playlists()
{
    playlist_folder.setPath("/home/lukas/");

   playlist_list = playlist_folder.entryList(QStringList() << "*.pla", QDir::Files);
    playlist_list.push_back("playlist");
   for(const QString& f:playlist_list)
   {

    info.setFile(f);
       emit returnPlaylistName(info.completeBaseName());


   }
}


QString playlist::returnPlaylistPath(int index_in_table)
{
    return playlist_list[index_in_table];
}

void playlist::create_playlist(QString name)
{
    playlist_file.close();
    playlist_file.setFileName("/home/lukas/"+name+".pla");
    playlist_file.open(QIODevice::ReadWrite);
}

void playlist::delete_current_playlist()
{
    playlist_file.remove();
}
