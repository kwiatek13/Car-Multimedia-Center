#include "dialog.h"
#include "ui_dialog.h"
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <iostream>
#include "player.h"
#include "playlist.h"
#include <QDirIterator>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

pl.setPlayer(odtwarzacz.getPlayer());



    connect(odtwarzacz.getPlayer(), &QMediaPlayer::positionChanged, this, &Dialog::on_positionChanged);
    connect(odtwarzacz.getPlayer(), &QMediaPlayer::durationChanged, this, &Dialog::on_durationChanged);
    ui->setupUi(this);


    odtwarzacz.setPlaylist(pl.getPlaylist());

    lista = pl.getPlaylist();
    music = odtwarzacz.getPlayer();

   // music->moveToThread(&PlayerThread);
   // PlayerThread.start();

    ui->label_image->setPixmap(set_pixmap_img("/home/lukas/Dokumenty","albumart.jpg"));

    list_folders();


    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu); //ustawianie menu kontekstowego
    ui->playlist_listwidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->playlist_listwidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showPlaylistContextMenu(QPoint)));

connect(&pl ,SIGNAL(returnPath(QString)), this, SLOT(create_list(QString))); //przekazywanie poprzez sloty i sygnaly listy utworow z klasy playlist
connect(&pl ,SIGNAL(returnPathMain(QString)), this, SLOT(create_main_list(QString)));
connect(&pl,SIGNAL(returnPlaylistName(QString)), this, SLOT(create_playlist_list(QString)));


ui->button_pause->setVisible(false); //ukrycie niepotrzebnych juz elementow
ui->pushButton_3->setVisible(false);

pl.readPlaylist("playlist");

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_button_browser_clicked()
{
     // system("chromium");
    PlayerThread.quit();
    pl.fun_start();
    PlayerThread.start();
    odtwarzacz.odtworz(0);
}

void Dialog::on_button_player_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Dialog::on_button_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Dialog::on_button_open_clicked() //zrobiony na poczatek przycisk otwierania albumu z wybranego folderu
{
content.clear();

files.clear();
    directory = QFileDialog::getExistingDirectory(this,tr("Select dir for files to import"));
    if(directory.isEmpty())
        return;
   // QDir dir(directory);
    folder.setPath(directory);
    files = folder.entryList(QStringList() << "*.flac" <<"*.mp3",QDir::Files);
    image_files = folder.entryList(QStringList() << "*.jpg" <<"*.png",QDir::Files); //do okladki

    ui->listWidget->clear();
pl.clear();
    for(const QString& f:files)
    {
        content.push_back(QUrl::fromLocalFile(folder.path()+"/" + f));
        fi.setFile(f);
        ui->listWidget->addItem(fi.completeBaseName());

    }
    pl.setPlaylist(content);
    ui->listWidget->setCurrentRow(lista->currentIndex() != -1? lista->currentIndex():0);


    ui->label_image->setPixmap(set_pixmap_img(folder.path(),image_files.first()));

    ui->listWidget->addItem(content[0].canonicalUrl().path());



}

void Dialog::on_button_play_clicked()
{

if(mode == 0)
{
    mode=1;
    ui->button_play->setText("Play");
}
else
{
    mode=0;
    ui->button_play->setText("||");
}
    odtwarzacz.odtworz(mode);
}

void Dialog::on_pushButton_clicked()
{
    a-=15;
    if(a<=0) a=0;
    music->setVolume(a);

//ui->stackedWidget->setCurrentIndex(1);
    //ui->page_2->setVisible(false);
    //ui->page_3->setVisible(true);
}

void Dialog::on_pushButton_2_clicked()
{
    a += 15;
    if (a>=100) a=100;
    music->setVolume(a);


}

void Dialog::on_horizontalSlider_sliderMoved(int position)
{

}

void Dialog::on_positionChanged(qint64 position)
{

ui->slider_progress->setValue(position);

}

void Dialog::on_durationChanged(qint64 position)
{
ui->slider_progress->setMaximum(position);
}

void Dialog::on_slider_progress_sliderMoved(int position)
{

odtwarzacz.getPlayer()->setPosition(position);

}

void Dialog::on_button_pause_clicked()
{
  //  music->pause();
}

void Dialog::on_slider_progress_sliderPressed()
{
    odtwarzacz.odtworz(1);
}

void Dialog::on_slider_progress_sliderReleased()
{
    odtwarzacz.odtworz(0);

}

void Dialog::on_button_backward_clicked()
{
    pl.previous();
}

void Dialog::on_button_forward_clicked()
{
    if(mieszanie == 0)
    {
    pl.next();
    }
    if(mieszanie == 1)
    {
        lista->shuffle();
    }
}

void Dialog::on_listWidget_doubleClicked(const QModelIndex &index)
{
   pl.setIndex(ui->listWidget->currentRow());
   odtwarzacz.odtworz(0);

}

void Dialog::on_button_shuffle_clicked()
{
   mieszanie = 1;
}

void Dialog::on_test_button_pressed()
{
    mieszanie = 1;
}

void Dialog::on_test_button_released()
{
    mieszanie = 0;
}

void Dialog::on_test_button_clicked() //przycisk playlisty
{
ui->stackedWidget->setCurrentIndex(3);
ui->playlist_listwidget->clear();
ui->playlists_list->clear();
pl.list_playlists();
pl.readPlaylist("playlist"); //wczytanie playlisty ulubionych utworow


}

void Dialog::on_button_exit_clicked()
{
    PlayerThread.quit();
    PlayerThread.wait();
    close();
}


void Dialog::list_folders() //zaladowanie elementow do biblioteki
{
folders << "";
QDirIterator directories("/home/lukas/Muzyka", QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
//QString abc;

//int a=1;
if(!directories.hasNext()) return;
   do{
    directories.next();
 //while(a <= 19){ //tymczasowe

       folder.setPath(directories.filePath());



        image_files = folder.entryList(QStringList() << "*.jpg" <<"*.png",QDir::Files);

        if(!image_files.isEmpty())
            set_pixmap_img(directories.filePath(),image_files.first());

        if(image_files.isEmpty())
            set_pixmap_img("/home/lukas/Dokumenty","albumart.jpg");

       nazwy = directories.fileName();
       add_button(directories.filePath());
     //  directories.next();

//a++;
image_files.clear();
   }while(directories.hasNext());
}





void Dialog::on_pushButton_3_clicked()
{
ui->stackedWidget->setCurrentIndex(3);
}

void Dialog::add_button(QString filepath) //funkcja do dynamicznego dodawania przyciskow do biblioteki
{



    button_tab.push_back(new QPushButton);

    ui->gridLayout->addWidget(button_tab[pos],x,y);
    button_tab[pos]->setMaximumHeight(100);
    button_tab[pos]->setMaximumWidth(100);

   connect(button_tab[pos],&QPushButton::clicked,[=](){set_album_page(filepath);}); //przypisywanie funkcji do przyciskow

  if(!image.isNull())  button_tab[pos]->setIcon(image);


    x++;
    pos++;
    if(x == max_rows)
    {
        x=0;
        y++;
    }

}


QPixmap Dialog::set_pixmap_img(QString sciezka, QString plik)
{
    image.load(sciezka + "/" + plik);

    image = image.scaledToWidth(ui->label_image->width(), Qt::SmoothTransformation);
    image = image.scaledToHeight(ui->label_image->height(), Qt::SmoothTransformation);
    return image;
}

void Dialog::set_album_page(QString sciezka) //wczytanie wybranego folderu do storny albumu
{
ui->stackedWidget->setCurrentIndex(2);

    content.clear();
   folder.setPath(sciezka);
   ui->title_album_page->setText(folder.dirName());
    files = folder.entryList(QStringList() << "*.flac" <<"*.mp3",QDir::Files);
    image_files = folder.entryList(QStringList() << "*.jpg" <<"*.png",QDir::Files); //do okladki

    ui->listWidget_album_page->clear();

    for(const QString& f:files) // Do sprawdzenia
    {
        content.push_back(QUrl::fromLocalFile(folder.path()+"/" + f));
     fi.setFile(f);
        ui->listWidget_album_page->addItem(fi.completeBaseName());


    }

    ui->listWidget_album_page->setCurrentRow(lista->currentIndex() != -1? lista->currentIndex():0);


  if(!image_files.empty())  ui->cover_album_page->setPixmap(set_pixmap_img(folder.path(),image_files.first()));
if(image_files.isEmpty()) ui->cover_album_page->setPixmap(set_pixmap_img("/home/lukas/Dokumenty","albumart.jpg"));

}


void Dialog::on_listWidget_album_page_doubleClicked(const QModelIndex &index) //zaladowanie wybranego albumu do odtwarzacza po wybraniu utowru z listy
{
pl.clear();
    pl.setPlaylist(content);

   if(!image_files.empty()) ui->label_image->setPixmap(set_pixmap_img(folder.path(),image_files.first()));
   if(image_files.isEmpty()) ui->label_image->setPixmap(set_pixmap_img("/home/lukas/Dokumenty","albumart.jpg"));

    pl.setIndex(ui->listWidget_album_page->currentRow());
    ui->listWidget->clear();
    set_main_listwidget(folder,files);
    odtwarzacz.odtworz(0);
}

void Dialog::on_player_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Dialog::set_main_listwidget(QDir album_dir, QStringList dir_list) //wypelnianie listy utworow na glownej stronie odtwarzacza
{
    for(const QString& f:dir_list)
    {
        content.push_back(QUrl::fromLocalFile(album_dir.path()+"/" + f));
     fi.setFile(f);

         ui->listWidget->addItem(fi.completeBaseName());

    }

    ui->listWidget_album_page->setCurrentRow(lista->currentIndex() != -1? lista->currentIndex():0);
}

void Dialog::on_button_back_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Dialog::on_playlist_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Dialog::showContextMenu(const QPoint &pos) //menu kontekstowe z dodwaniem utworu do playlisty
{

        globalPos = ui->listWidget->mapToGlobal(pos);

        myMenu = std::make_shared<QMenu>();


        myMenu->addAction("Dodaj do ulubionych", this, SLOT(add_to_playlist()));
       // myMenu.addAction("Erase",  this, SLOT(eraseItem()));


        myMenu->exec(globalPos);
}

void Dialog::showPlaylistContextMenu(const QPoint &pos2) //menu kontekstowe z usuaniem utworow z playlisty
{
 globalPos = ui->playlist_listwidget->mapToGlobal(pos2);
 //myMenu2 = std::make_shared<QMenu>(); //do sprawdzenia

 myMenu2->addAction("Usun z listy", this, SLOT(remove_from_playlist()));
  myMenu2->exec(globalPos);


}

void Dialog::add_to_playlist()
{
    pl.writePlaylist(ui->listWidget->currentRow());

}


void Dialog::create_list(QString track_path)
{
    fi.setFile(track_path);
ui->playlist_listwidget->addItem(fi.completeBaseName());
}

void Dialog::create_main_list(QString main_track_path)
{
    fi.setFile(main_track_path);
    ui->listWidget->addItem(fi.completeBaseName());
}


void Dialog::on_playlist_listwidget_doubleClicked(const QModelIndex &index) //ladowanie playlisty do odtwarzacza po wybraniu utworu z listy
{
pl.clear();
ui->listWidget->clear();
    pl.add_current();
    pl.setIndex(ui->playlist_listwidget->currentRow());
ui->label_image->setPixmap(set_pixmap_img("/home/lukas/Dokumenty","albumart.jpg"));
    odtwarzacz.odtworz(0);
}

void Dialog::remove_from_playlist() //usuwanie pozycji z playlisty
{

    pl.deleteEntry(ui->playlist_listwidget->currentRow());
    ui->playlist_listwidget->takeItem(ui->playlist_listwidget->currentRow());
    ui->playlist_listwidget->clear();
    pl.readPlaylist(pl.returnPlaylistPath(ui->playlists_list->currentRow()));

}

void Dialog::on_library_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Dialog::on_library_player_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Dialog::on_button_library_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Dialog::create_playlist_list(QString playlist_path)
{
ui->playlists_list->addItem(playlist_path);


}

void Dialog::on_playlists_list_doubleClicked(const QModelIndex &index) //ladowanie listy utworow z wybranej playlisty
{
    ui->playlist_listwidget->clear();
    pl.readPlaylist(pl.returnPlaylistPath(ui->playlists_list->currentRow()));

}

void Dialog::on_add_button_clicked() //przycisk dodawania playlisty
{
    pl.create_playlist(ui->lineEdit->text());
    ui->playlists_list->clear();
    pl.list_playlists();
}


void Dialog::on_remove_button_clicked() //przycisk usuwania playlisty
{
    pl.delete_current_playlist();
    ui->playlists_list->clear();
    ui->playlist_listwidget->clear();
    pl.list_playlists();
}
