#include "current_widget.h"
#include "ui_current_widget.h"

#include "../database/data.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <time.h>

QLabel *current_widget::hive1_entry;
QLabel *current_widget::hive1_exit;
QLabel *current_widget::hive2_entry;
QLabel *current_widget::hive2_exit;
QLabel *current_widget::hive3_entry;
QLabel *current_widget::hive3_exit;

// default constructor
current_widget::current_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::current_widget)
{
    ui->setupUi(this);

    hive1_entry=ui->hive1_entry;
    hive1_exit=ui->hive1_exit;
    hive2_entry=ui->hive2_entry;
    hive2_exit=ui->hive2_exit;
    hive3_entry=ui->hive3_entry;
    hive3_exit=ui->hive3_exit;
    timer_start(update,20000);
}

// deconstructor
current_widget::~current_widget()
{
    delete ui;
}

/**
 * @brief current_widget::update update the live data (entries/exits)
 */
void current_widget::update(){
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t end = chrono::system_clock::to_time_t(now);
    time_t start = chrono::system_clock::to_time_t(now-chrono::minutes(1));
    std::stringstream ss,ss2;
    ss <<put_time(localtime(&start), "%T");
    ss2 <<put_time(localtime(&end), "%T");
    std::string st= ss.str();
    std::string et = ss2.str();
    st.append("000");
    et.append("000");
    st.replace(2,1, ".");
    st.replace(5,1,".");
    et.replace(2,1, ".");
    et.replace(5,1,".");

    // get data from the database
    Data d("../../../../process_messages");

    d.selectwheredtt("19.06.02", st, et, "1", "Entry");  //hive 1 current data
    int hive_1_entry=d.getEventsV().size(); // number of entries in hive 1
    d.getEventsV().clear();

    d.selectwheredtt("19.06.02", st, et, "1", "Exit");
    int hive_1_exit=d.getEventsV().size(); // number of exits from hive 1
    d.getEventsV().clear();

    d.selectwheredtt("19.06.02", st, et, "2", "Entry");
    int hive_2_entry=d.getEventsV().size();
    d.getEventsV().clear();

    d.selectwheredtt("19.06.02", st, et, "2", "Exit");
    int hive_2_exit=d.getEventsV().size();
    d.getEventsV().clear();

    d.selectwheredtt("19.06.02", st, et, "3", "Entry");
    int hive_3_entry=d.getEventsV().size();
    d.getEventsV().clear();

    d.selectwheredtt("19.06.02", st, et, "3", "Exit");
    int hive_3_exit=d.getEventsV().size();
    d.getEventsV().clear();

    //    cout << st <<" - "<<et<<" "<<"Hive 1 Entry:" << hive_1_entry<<endl;
    //    cout << st <<" - "<<et<<" "<<"Hive 1 Exit:" << hive_1_exit<<endl;
    //    cout << st <<" - "<<et<<" "<<"Hive 2 Entry:" << hive_2_entry<<endl;
    //    cout << st <<" - "<<et<<" "<<"Hive 2 Exit:" << hive_2_exit<<endl;
    //    cout << st <<" - "<<et<<" "<<"Hive 3 Entry:" << hive_3_entry<<endl;
    //    cout << st <<" - "<<et<<" "<<"Hive 3 Exit:" << hive_3_exit<<endl;

    hive1_entry->setNum(hive_1_entry);
    hive1_exit->setNum(hive_1_exit);
    hive2_entry->setNum(hive_2_entry);
    hive2_exit->setNum(hive_2_exit);
    hive3_entry->setNum(hive_3_entry);
    hive3_exit->setNum(hive_3_exit);

}

/**
 * @brief current_widget::timer_start threading based on certain interval
 * @param func fuction
 * @param interval time interval
 */
void current_widget::timer_start(std::function<void(void)> func, unsigned int interval){
    std::thread([func, interval](){
        while(true){
            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
            func();
            std::this_thread::sleep_until(x);
        }
    }).detach();
}

/**
 * @brief current_widget::on_hive1_sound_clicked sound for hive 1
 */
void current_widget::on_hive1_sound_clicked()
{
    int entry=hive1_entry->text().toInt();
    int exit=hive1_exit->text().toInt();
    int sum=entry+exit;
    play_sound(sum);
}

/**
 * @brief current_widget::on_hive2_sound_clicked sound for hive 2
 */
void current_widget::on_hive2_sound_clicked()
{
    int entry=hive2_entry->text().toInt();
    int exit=hive2_exit->text().toInt();
    int sum=entry+exit;
    play_sound(sum);
}

/**
 * @brief current_widget::on_hive3_sound_clicked sound for hive 3
 */
void current_widget::on_hive3_sound_clicked()
{
    int entry=hive3_entry->text().toInt();
    int exit=hive3_exit->text().toInt();
    int sum=entry+exit;
    play_sound(sum);
}

// variables
static QMediaPlayer *music = new QMediaPlayer();
bool current_widget::current_flag1;
bool current_widget::current_flag2;
bool current_widget::current_flag3;
bool current_widget::current_flag4;

/**
 * @brief current_widget::play_sound play sound based on activity
 * @param activity activity number
 */
void current_widget::play_sound(int activity){
    //cout<<"Activity: "<<activity<<" ";
    if(activity>=0 && activity<=5){
        if(current_flag1==false){
            QMediaPlaylist *playlist = new QMediaPlaylist();
            playlist->addMedia(QUrl("qrc:/files/Bee-noise_2.mp3"));
            playlist->setPlaybackMode(QMediaPlaylist::Loop);
            music->stop();
            music->setPlaylist(playlist);
            music->play();
            current_flag1=true;
        }else{
            music->stop();
            current_flag1=false;
        }


    }else if(activity>=6 && activity<=15){
        if(current_flag2==false){
            QMediaPlaylist *playlist = new QMediaPlaylist();
            playlist->addMedia(QUrl("qrc:/files/Bee-noise_3.mp3"));
            playlist->setPlaybackMode(QMediaPlaylist::Loop);

            music->stop();
            music->setPlaylist(playlist);
            music->play();
            current_flag2=true;

        }else{
            music->stop();
            current_flag2=false;
        }
    }else if(activity>=16 && activity<=30){
        if(current_flag3==false){
            QMediaPlaylist *playlist = new QMediaPlaylist();
            playlist->addMedia(QUrl("qrc:/files/Bee-noise_4.mp3"));
            playlist->setPlaybackMode(QMediaPlaylist::Loop);

            music->stop();
            music->setPlaylist(playlist);
            music->play();
            current_flag3=true;

        }else{
            music->stop();
            current_flag3=false;
        }
    }else if(activity>31){
        if(current_flag4==false){
            QMediaPlaylist *playlist = new QMediaPlaylist();
            playlist->addMedia(QUrl("qrc:/files/Bee-noise_5.mp3"));
            playlist->setPlaybackMode(QMediaPlaylist::Loop);

            music->stop();
            music->setPlaylist(playlist);
            music->play();
            current_flag4=true;

        }else{
            music->stop();
            current_flag4=false;
        }
    }
}
