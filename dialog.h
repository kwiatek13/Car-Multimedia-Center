#ifndef DIALOG_H
#define DIALOG_H
#include "dialog.h"
#include "ui_dialog.h"
#include <QDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QObject>
#include <QSignalMapper>
#include "player.h"
#include "playlist.h"
#include <QDirIterator>
#include <cstdio>
#include <vector>
#include <QMenu>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog

{
    Q_OBJECT
    QPixmap image;
    QStringList image_files;
    QStringList folders, files;
    QList<QMediaContent> content;
    QDir folder;
    QVector <QPushButton*> button_tab;
   // QPushButton* button_tab[100];
     QFileInfo fi;
    QString przycisk, nazwy="button", cala_nazwa;
    //QObject* obj = sender();
    QMenu* myMenu;
    QMenu* myMenu2;
    QPoint globalPos;
 //   player *odtwarzacz;
   // playlist *lista_muzyki;


    player odtwarzacz;
    playlist pl;




public:
    int a=0, mieszanie=0, x=0, y=0, mode=0, pos=0;
QMediaPlayer* music;
     QMediaPlaylist* lista;
      void setList(QMediaPlaylist *pl);
      QString directory;
     // QSignalMapper mapper;

void list_folders();
void add_button(QString filepath);
QPixmap set_pixmap_img(QString sciezka, QString plik);
void set_album_page(QString sciezka);
void set_main_listwidget(QDir album_dir, QStringList dir_list);


    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
   //   friend class playlist;
     // friend class player;

private slots:
    void on_button_browser_clicked();

    void on_button_player_clicked();

    void on_button_back_clicked();

    void on_button_open_clicked();

    void on_button_play_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);

    void on_slider_progress_sliderMoved(int position);

    void on_button_pause_clicked();

    void on_slider_progress_sliderPressed();

    void on_slider_progress_sliderReleased();

    void on_button_backward_clicked();

    void on_button_forward_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_button_shuffle_clicked();

    void on_test_button_pressed();

    void on_test_button_released();

    void on_test_button_clicked();

    void on_button_exit_clicked();



    void on_pushButton_3_clicked();

    void on_listWidget_album_page_doubleClicked(const QModelIndex &index);

    void on_player_button_clicked();

    void on_button_back_2_clicked();

    void on_playlist_back_button_clicked();

    void showContextMenu(const QPoint &pos);

    void showPlaylistContextMenu(const QPoint &pos2);

    void add_to_playlist();

    void create_list(QString track_path);

    void create_main_list(QString main_track_path);

    void create_playlist_list(QString playlist_path);

    void on_playlist_listwidget_doubleClicked(const QModelIndex &index);

    void remove_from_playlist();

    void on_library_back_button_clicked();

    void on_library_player_button_clicked();

    void on_button_library_clicked();

    void on_playlists_list_doubleClicked(const QModelIndex &index);

    void on_add_button_clicked();

    void on_remove_button_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H






