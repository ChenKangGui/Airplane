#include "mainscene.h"
#include "ui_mainscene.h"
#include "config.h"
#include <QPainter>
#include <QDebug>
#include <ctime>
#include <QProgressBar>
#include <QPixmap>

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    enemy_recorder = 10;
    Init_Scene();


    m.pic.load(":/res/1.png");
    m.rect.setWidth(m.pic.width());
    m.rect.setHeight(m.pic.height());
    m.rect.moveTo(0, 0);
}

MainScene::~MainScene()
{
    delete ui;
}


void MainScene::Init_Scene()
{
    setFixedSize(GAME_WIDTH, GAME_HEIGTH);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICO));
    ui->liftProcess->setOrientation(Qt::Vertical);
    ui->liftProcess->setRange(0, 20);
    ui->liftProcess->setValue(20);
    ui->liftProcess->setFixedSize(10, 250);
    ui->liftProcess->move(460, 0);
    ui->liftProcess->setTextVisible(false);

    connect(&timer, &QTimer::timeout, [=]()
    {
        updatePosistion();
        update();
        crash();
    });
    timer.start(GAME_RATE);

    connect(&enemy_timer, &QTimer::timeout, [=]()
    {
        enemy_updatePosistion();
    });
    enemy_timer.start(ENEMY_APPEAR);

    qsrand(time(NULL));
}

void MainScene::play_game()
{
    connect(&timer, &QTimer::timeout, [=]()
    {
        updatePosistion();
        //update();
    });
    timer.start(GAME_RATE);
}

void MainScene::updatePosistion()
{
    map.updataPosistion();

    for(int i=0; i<BULLET_NUM; i++)
    {
        if(!plane.m_bullet[i].free)
        {
            plane.m_bullet[i].setPosistion();
        }
    }

    for(int i=0; i<TOTAL_FINALHIT; i++)
    {
        if(!plane.m_finalhit[i].free)
        {
            plane.m_finalhit[i].updatePosistion();
        }
    }

    for(int i=0; i<ENEMY_NUM; i++)
    {
        for(int j=0; j<BULLET_NUM; j++)
        {
            if(!enemy[i].bul[j].free)
            {
                enemy[i].bul[j].setPosistion();
            }
        }
    }
}

void MainScene::paintEvent(QPaintEvent *event)
{
    static int count = 0;
    QPainter painters(this);

    painters.drawPixmap(0, 0, m.pic);
    painters.drawPixmap(0, map.map1_y, map.map1);
    painters.drawPixmap(0, map.map2_y, map.map2);
    if(plane.death)
    {
        painters.drawPixmap(plane.x, plane.y, plane.plane_death);
        enemy_timer.stop();
        timer.stop();
    }
    else
    {
        painters.drawPixmap(plane.x, plane.y, plane.plane);
    }

    for(int i=0; i<BULLET_NUM; i++)
    {
        if(!plane.m_bullet[i].free)
        {
            painters.drawPixmap(plane.m_bullet[i].x, plane.m_bullet[i].y, plane.m_bullet[i].m_bullet);
        }
    }

    for(int i=0; i<TOTAL_FINALHIT; i++)
    {
        if(!plane.m_finalhit[i].free)
        {
            painters.drawPixmap(plane.m_finalhit[i].x, plane.m_finalhit[i].y, plane.m_finalhit[i].finalHit);
        }
    }

    for(int i=0; i<ENEMY_NUM; i++)
    {
        if(!enemy[i].free)
        {
            painters.drawPixmap(enemy[i].x, enemy[i].y, enemy[i].pic);
        }
        for(int j=0; j<BULLET_NUM; j++)
        {
            if(!enemy[i].bul[j].free)
            {
                painters.drawPixmap(enemy[i].bul[j].x, enemy[i].bul[j].y, enemy[i].bul[j].m_bullet);
            }
        }
        if(enemy[i].death)
        {
            count++;
            if(count >= 10)
            {
                count = 0;
                 enemy[i].death = false;
            }
            painters.drawPixmap(enemy[i].x, enemy[i].y, enemy[i].pic_death);
        }
    }
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    if(event->x()>=plane.x && event->x()<=(plane.x+60) && event->y()>=plane.y && event->y()<=plane.y+85)
    {
        plane.x = event->x() - plane.rect.width() *0.5;     //鼠标位置 - 飞机矩形的一半
        plane.y = event->y() - plane.rect.height()*0.5;

        //边界检测
        if(plane.x <= 0 )
        {
            plane.x = 0;
        }

        if(plane.x >= GAME_WIDTH - plane.rect.width())
        {
            plane.x = GAME_WIDTH - plane.rect.width();
        }

        if(plane.y <= 0)
        {
            plane.y = 0;
        }

        if(plane.y >= GAME_HEIGTH - plane.rect.height())
        {
            plane.y = GAME_HEIGTH - plane.rect.height();
        }
        qDebug() << "x = " << plane.x << "y = " << plane.y;
        plane.rect.moveTo(plane.x, plane.y);
    }
}

void MainScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)   //up
    {
        if(plane.y >= plane.rect.width())
        {
            plane.y -= PLANE_SPEED;
        }
    }
    else if(event->key() == Qt::Key_S)  //down
    {
        if(plane.y <= (GAME_HEIGTH-plane.rect.height()))
        {
            plane.y += PLANE_SPEED;
        }
    }
    else if(event->key() == Qt::Key_A)  //left
    {
        if(plane.x >= 0)
        {
            plane.x -= PLANE_SPEED;
        }
    }
    else if(event->key() == Qt::Key_D)
    {
        if(plane.x <= GAME_WIDTH-plane.rect.width())
        {
            plane.x += PLANE_SPEED;
        }
    }
    else if(event->key() == Qt::Key_J)
    {
        plane.shoot();
    }
    else if(event->key() == Qt::Key_K)
    {
        if(plane.finahit_num > 0)
        {
            plane.finahit_num--;
            plane.final_hit();
            for(int i=0; i<ENEMY_NUM; i++)
            {
                if(!enemy[i].free)
                {
                    enemy[i].allDeath();
                }
                for(int j=0; j<BULLET_NUM; j++)
                {
                    enemy[i].bul[j].allDisappear();
                }
            }
        }
    }
    plane.rect.moveTo(plane.x, plane.y);
}

void MainScene::enemy_updatePosistion()
{
    for(int j=0; j<ENEMY_NUM; j++)
    {
        if(enemy[j].recorder > ENEMYBULLET_INTERVAL && (!enemy[j].free))
        {
            enemy[j].recorder = 0;
            enemy[j].shoot();

        }
        if(!enemy[j].free)
        {
            enemy[j].recorder++;
            enemy[j].updatePosistion();
        }
    }

    enemy_recorder++;
    if(enemy_recorder >= 10)
    {
        enemy_recorder = 0;
        for(int i=0; i<ENEMY_NUM; i++)
        {
            if(enemy[i].free)
            {
                enemy[i].free = false;                
                enemy[i].x = qrand() % (GAME_WIDTH-enemy[i].rect.width());
                enemy[i].y = 0;
                enemy[i].speed = (qrand()%2) ? ENEMY_SPEED : -ENEMY_SPEED;
                enemy[i].rect.moveTo(enemy[i].x, enemy[i].y);
                break;
            }
        }
    }
}

void MainScene::crash()
{
    for(int j=0; j<BULLET_NUM; j++)  //plane bullet and enemy
    {
        if(!plane.m_bullet[j].free)
        {
            for(int i=0; i<ENEMY_NUM; i++)
            {
                if(!enemy[i].free)
                {                   
                    if(enemy[i].rect.intersects(plane.m_bullet[j].rect))
                    {
                        enemy[i].free = true;
                        plane.m_bullet[j].free = true;
                        enemy[i].death = true;
                        break;
                    }
                }
            }
        }
    }

    for(int j=0; j<ENEMY_NUM; j++)  //plane and enemy
    {
        if(!enemy[j].free)
        {
            if(enemy[j].rect.intersects(plane.rect))
            {
                enemy[j].free = true;
                enemy[j].death = true;
                plane.life -= 2;
                ui->liftProcess->setValue(plane.life);
                if(plane.life <= 5 && plane.life > 0)
                {
                    ui->liftProcess->setStyleSheet("QProgressBar::chunk { background-color: rgb(255, 0, 0) }");
                }
                else if(plane.life <= 0)
                {
                    ui->liftProcess->setValue(0);
                    plane.death = true;
                }
            }
        }
    }

    for(int j=0; j<ENEMY_NUM; j++)   //plane and enemyBullet
    {
        for(int i=0; i<BULLET_NUM; i++)
        {
            if((!enemy[j].free) && (!enemy[j].bul[i].free))
            {
                if(plane.rect.intersects(enemy[j].bul[i].rect))
                {
                    enemy[j].bul[i].free = true;
                    plane.life--;
                    ui->liftProcess->setValue(plane.life);
                    if(plane.life <= 5 && plane.life > 0)
                    {
                        ui->liftProcess->setStyleSheet("QProgressBar::chunk { background-color: rgb(255, 0, 0) }");
                    }
                    else if(plane.life <= 0)
                    {
                        plane.death = true;
                    }
                }
            }
        }
    }

}

