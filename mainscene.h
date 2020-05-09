#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QTimer>
#include "map.h"
#include "heroplane.h"
#include <QKeyEvent>
#include "bullet.h"
#include "enemy.h"
#include <QProgressBar>

namespace Ui {
class MainScene;
}


class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();

    QTimer enemy_timer;
    QTimer timer;
    Map map;
    HeroPlane plane;
    bullet m_bullet[BULLET_NUM];
    Enemy enemy[ENEMY_NUM];
Enemy m;
    int enemy_recorder;

    void Init_Scene();
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void crash();
public slots:
    void play_game();
    void updatePosistion();
    void paintEvent(QPaintEvent *event);
    void enemy_updatePosistion();
private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
