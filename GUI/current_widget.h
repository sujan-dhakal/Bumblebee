#ifndef CURRENT_WIDGET_H
#define CURRENT_WIDGET_H

#include <QWidget>
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <vector>
#include "ui_current_widget.h"
#include <string>

#include <QMediaPlayer>
#include <QMediaPlaylist>

using namespace std;

namespace Ui {
class current_widget;
}

class current_widget : public QWidget
{
    Q_OBJECT

public:
    explicit current_widget(QWidget *parent = nullptr);
    ~current_widget();
    static void  update();
    void timer_start(std::function<void(void)> func, unsigned int interval);

   static QLabel* hive1_entry;
   static QLabel* hive1_exit;
   static QLabel* hive2_entry;
   static QLabel* hive2_exit;
   static QLabel* hive3_entry;
   static QLabel* hive3_exit;

   static bool current_flag1;
   static bool current_flag2;
   static bool current_flag3;
   static bool current_flag4;

   static void play_sound(int activity);

private slots:
   void on_hive1_sound_clicked();

   void on_hive2_sound_clicked();

   void on_hive3_sound_clicked();

private:
    Ui::current_widget *ui;

};

#endif // CURRENT_WIDGET_H
