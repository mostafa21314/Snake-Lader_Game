#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<time.h>
#include<QTimer>
#include <ctime>
#include <QMainWindow>
#include <QEventLoop>
#include <QDebug>
#include"Board.h"
#include <QPixmap>
#include <QPalette>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include<QBrush>
#include <vector>
#include <QPen>
#include <iostream>
#include <vector>
#include <cstdlib>
#include"Players.h"
#include "ui_mainwindow.h"
#include<queue>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    int currentPlayer=1;
    bool BSizeSet=false;
    bool NumPSet=false;
    bool DiffSet=false;
    int difficulty;
    int SofBoard;
    int playersNum;
    Board gameBoard;
    const double xStart =0;
    const double yStart =708;
    const double xEnds = 708;
    const double yEnds =0;
    QGraphicsScene *scene = new QGraphicsScene();
    void Delay(int x)
    {
    QTimer timer;
                      timer.start(x);


                      QObject::connect(&timer, &QTimer::timeout, []()// Connect a lambda function to the timer's timeout signal
                      {
                          qDebug();
                      });
                      QEventLoop loop;   // Wait for the timer to finish
                      QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
                      loop.exec();

    }
    double getXcordinate(int x,int size)
    {
        double temp = (xEnds-xStart)/static_cast<double>(size);
        return (x*temp);
    }
    double getYcordinate(int x, int size)
    {
        double temp = (yEnds-yStart)/static_cast<double>(size);
        return (yStart+(x*temp));
    }

    double getWidth(int num)
    {
        return ((xEnds+xStart)/num);
    }

    double getLength(int num)
    {
        return ((yEnds+yStart)/num);
    }

    QVector<QVector<QGraphicsRectItem*>> rectItemsVector;
    QVector<QVector<QGraphicsTextItem*>> TextVector;
    std::queue<Players> playersQueue; // create queue of players

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;


    void BoardBuild(int k, double x)
    {

        gameBoard.SetDifficulty(100-x*20);
        gameBoard.Setladdertosnakeratio(0.6-x*0.05);
        gameBoard.generateBoard(k,k);
        gameBoard.dispEdges();

        QBrush redBrush(QColorConstants::Red);
        QBrush blackBrush(QColorConstants::Black);
        QBrush whiteBrush(QColorConstants::White);
        QPen redPen(QColorConstants::Red);
        QPen blackPen(QColorConstants::Black);
        QPen whitePen (QColorConstants::White);
        ui->GraphicsView->setScene(scene);
        ui->GraphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);  // Added alignment
        scene->setSceneRect(QRectF(0, 0, 708, 708));
        rectItemsVector.resize(k);
        TextVector.resize(k);

        for (int i = 0; i < k; ++i) {
            rectItemsVector[i].resize(k);
            TextVector[i].resize(k);
        }

        // Initialize each element in the vector
          for (int i = 0; i < k; ++i) {
              int counter=i;
              for (int j = 0; j < k; ++j) {
                  rectItemsVector[i][j] = new QGraphicsRectItem;
                  rectItemsVector[i][j]->setRect(getXcordinate(i,k), getYcordinate(j,k)-getWidth(k),getLength(k),getWidth(k));
                  rectItemsVector[i][j]->setPen(redPen);
                   scene->addItem(rectItemsVector[i][j]);
                  if((counter%2)==0)
                  {
                    rectItemsVector[i][j]->setBrush(redBrush)  ;              rectItemsVector[i][j]->setPen(redPen);

                  }
                  else
                  {
                    rectItemsVector[i][j]->setBrush(whiteBrush)  ;              rectItemsVector[i][j]->setPen(whitePen);

                  }
                  counter++;
              }
          }

          int indexing = 1;
           for(int i=0;i<k;i++)
           {
               for(int j=0;j<k;j++)
               {

                   TextVector[i][j]=new QGraphicsTextItem(QString::number(indexing++));


                   // Set the position of the text item to center it within the rectangle
                   if(i%2!=0)
                   {
                       QPointF textCenter = rectItemsVector[k-j-1][i]->boundingRect().center() - TextVector[i][j]->boundingRect().center();
                       TextVector[i][j]->setPos(rectItemsVector[k-j-1][i]->mapToScene(textCenter));
                       // Set the font size of the text
                        QFont font;
                         font.setPointSize(10); // Set the font size to 12 points
                         TextVector[i][j]->setFont(font);
                         scene->addItem(TextVector[i][j]);
                   }
                   else
                   {
                   QPointF textCenter = rectItemsVector[j][i]->boundingRect().center() - TextVector[i][j]->boundingRect().center();
                   TextVector[i][j]->setPos(rectItemsVector[j][i]->mapToScene(textCenter));
                   // Set the font size of the text
                    QFont font;
                     font.setPointSize(11); // Set the font size to 12 points
                     TextVector[i][j]->setFont(font);
                     scene->addItem(TextVector[i][j]);
                   }

               }
           }



           for(int i=0;i<k;i++)
           {
               for(int j=0;j<k;j++)
               {

               }

           }



           for(int i=0;i<k;i++)
           {
               for(int j=0;j<k;j++)
               {



               }
           }
           for(int i=0;i<k;i++)
           {
               for(int j=0;j<k;j++)
               {
                   Edge temp = gameBoard.findEdgeByU((i*k)+j+1);
                   if((temp.u>temp.v)&&(temp.w!=1))
                   {
                       int z=temp.v-1;
                       int y=z%k;
                       int x=z/k;
                      QPointF point1=TextVector[i][j]->pos();
                      QPointF point2=TextVector[x][y]->pos();
                     //  QPointF point1(0,0);
                     //  QPointF point2(708,708);
                    drawSnake(point1,point2,10);
                   }
                   else if((temp.u<temp.v)&&(temp.w!=1))
                   {
                       int z=temp.v-1;
                       int y=z%k;
                       int x=z/k;
                      QPointF point1=TextVector[i][j]->pos();
                      QPointF point2=TextVector[x][y]->pos();
                     //  QPointF point1(0,0);
                     //  QPointF point2(708,708);
                    drawLadder(point1,point2,x+3,20,4,4);

                   }
               }
           }
           scene->update();
    }

    void RandomBoardBuild()
    {


        gameBoard.generateRandBoard();
        gameBoard.dispEdges();
      //  gameBoard.dispEdges();
        int k= gameBoard.getSize();
        QBrush redBrush(QColorConstants::Red);
        QBrush blackBrush(QColorConstants::Black);
        QBrush whiteBrush(QColorConstants::White);
        QPen redPen(QColorConstants::Red);
        QPen blackPen(QColorConstants::Black);
        QPen whitePen (QColorConstants::White);
        ui->GraphicsView->setScene(scene);
        ui->GraphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);  // Added alignment
        scene->setSceneRect(QRectF(0, 0, 708, 708));
        rectItemsVector.resize(k);
        TextVector.resize(k);

        for (int i = 0; i < k; ++i) {
            rectItemsVector[i].resize(k);
            TextVector[i].resize(k);
        }

        // Initialize each element in the vector
          for (int i = 0; i < k; ++i) {
              int counter=i;
              for (int j = 0; j < k; ++j) {
                  rectItemsVector[i][j] = new QGraphicsRectItem;
                  rectItemsVector[i][j]->setRect(getXcordinate(i,k), getYcordinate(j,k)-getWidth(k),getLength(k),getWidth(k));
                  rectItemsVector[i][j]->setPen(redPen);
                   scene->addItem(rectItemsVector[i][j]);
                  if((counter%2)==0)
                  {
                    rectItemsVector[i][j]->setBrush(redBrush)  ;              rectItemsVector[i][j]->setPen(redPen);

                  }
                  else
                  {
                    rectItemsVector[i][j]->setBrush(whiteBrush)  ;              rectItemsVector[i][j]->setPen(whitePen);

                  }
                  counter++;
              }
          }

          int indexing = 1;
           for(int i=0;i<k;i++)
           {
               for(int j=0;j<k;j++)
               {

                   TextVector[i][j]=new QGraphicsTextItem(QString::number(indexing++));


                   // Set the position of the text item to center it within the rectangle
                   if(i%2!=0)
                   {
                       QPointF textCenter = rectItemsVector[k-j-1][i]->boundingRect().center() - TextVector[i][j]->boundingRect().center();
                       TextVector[i][j]->setPos(rectItemsVector[k-j-1][i]->mapToScene(textCenter));
                       // Set the font size of the text
                        QFont font;
                         font.setPointSize(10); // Set the font size to 12 points
                         TextVector[i][j]->setFont(font);
                         scene->addItem(TextVector[i][j]);
                   }
                   else
                   {
                   QPointF textCenter = rectItemsVector[j][i]->boundingRect().center() - TextVector[i][j]->boundingRect().center();
                   TextVector[i][j]->setPos(rectItemsVector[j][i]->mapToScene(textCenter));
                   // Set the font size of the text
                    QFont font;
                     font.setPointSize(10); // Set the font size to 12 points
                     TextVector[i][j]->setFont(font);
                     scene->addItem(TextVector[i][j]);
                   }

               }
           }



           for(int i=0;i<k;i++)
           {
               for(int j=0;j<k;j++)
               {
                   Edge temp = gameBoard.findEdgeByU((i*k)+j+1);
                   if((temp.u>temp.v)&&(temp.w!=1))
                   {
                       int z=temp.v-1;
                       int y=z%k;
                       int x=z/k;
                      QPointF point1=TextVector[i][j]->pos();
                      QPointF point2=TextVector[x][y]->pos();
                     //  QPointF point1(0,0);
                     //  QPointF point2(708,708);
                    drawSnake(point1,point2,13);
                   }
                   else if((temp.u<temp.v)&&(temp.w!=1))
                   {
                       int z=temp.v-1;
                       int y=z%k;
                       int x=z/k;
                      QPointF point1=TextVector[i][j]->pos();
                      QPointF point2=TextVector[x][y]->pos();
                     //  QPointF point1(0,0);
                     //  QPointF point2(708,708);
                    drawLadder(point1,point2,x+3,20,4,4);

                   }
               }
           }
           scene->update();
    }

   void initiatePlayers(int x)
    {
        if(x==1)
        {
            ui->PlayerName1->show();
            ui->PositionLabel1->show();
            ui->PositionStore->show();
            // Create and enqueue players based on user input
             for (int i = 1; i <= playersNum; ++i) {
                 playersQueue.push(Players("Player " + std::to_string(i)));
             }

        }
        if(x==2)
        {
            ui->PlayerName1->show();
            ui->PositionLabel1->show();
            ui->PositionStore->show();
            ui->PlayerName2->show();
            ui->PositionLabel2->show();
            ui->PositionStore_2->show();
            // Create and enqueue players based on user input
             for (int i = 1; i <= playersNum; ++i) {
                 playersQueue.push(Players("Player " + std::to_string(i)));
             }

        }
        if(x==3)
        {
            ui->PlayerName1->show();
            ui->PlayerName2->show();
            ui->PlayerName3->show();
            ui->PositionLabel1->show();
            ui->PositionLabel2->show();
            ui->PositionLabel3->show();
            ui->PositionStore->show();
            ui->PositionStore_2->show();
            ui->PositionStore_3->show();
            // Create and enqueue players based on user input
             for (int i = 1; i <= playersNum; ++i) {
                 playersQueue.push(Players("Player " + std::to_string(i)));
             }

        }
        if(x==4)
        {
            ui->PlayerName1->show();
            ui->PlayerName2->show();
            ui->PlayerName3->show();
            ui->PlayerName4->show();
            ui->PositionLabel1->show();
            ui->PositionLabel2->show();
            ui->PositionLabel3->show();
            ui->PositionLabel4->show();
            ui->PositionStore->show();
            ui->PositionStore_2->show();
            ui->PositionStore_3->show();
            ui->PositionStore_4->show();
            // Create and enqueue players based on user input
             for (int i = 1; i <= playersNum; ++i) {
                 playersQueue.push(Players("Player " + std::to_string(i)));
             }

        }


    }

    void drawSnake(const QPointF& startPoint, const QPointF& endPoint, int numBalls) {
        // Create a straight line using QLineF
        QLineF line(startPoint, endPoint);

        // Draw the straight line
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(line);
        scene->addItem(lineItem);

        // Number of balls along the line
        qreal ballRadius = 10;

        // Add more frequent and intersecting balls along the straight line
        for (int i = 0; i < numBalls; ++i) {
            qreal t = qreal(i) / qreal(numBalls - 1);  // Parameter along the line (0 to 1)
            QPointF pos = line.pointAt(t);             // Calculate point at parameter t

            QGraphicsEllipseItem* ball = new QGraphicsEllipseItem(pos.x() - ballRadius,
                                                                   pos.y() - ballRadius,
                                                                   2 * ballRadius,
                                                                   2 * ballRadius);

            // Alternate colors between yellow and green
            ball->setBrush((i % 2 == 0) ? QBrush(Qt::yellow) : QBrush(Qt::green));

            scene->addItem(ball);

            // Add eyes at the last ball
            if (i == numBalls - 1) {
                // Radius of the eye
                qreal eyeRadius = ballRadius / 4;

                // Coordinates for the eyes inside the last ball
                QPointF leftEyePos(pos.x() - ballRadius / 2, pos.y() - ballRadius / 2);
                QPointF rightEyePos(pos.x() + ballRadius / 4, pos.y() - ballRadius / 2);

                // Draw the eyes
                QGraphicsEllipseItem* leftEye = new QGraphicsEllipseItem(leftEyePos.x() - eyeRadius,
                                                                          leftEyePos.y() - eyeRadius,
                                                                          2 * eyeRadius,
                                                                          2 * eyeRadius);
                QGraphicsEllipseItem* rightEye = new QGraphicsEllipseItem(rightEyePos.x() - eyeRadius,
                                                                           rightEyePos.y() - eyeRadius,
                                                                           2 * eyeRadius,
                                                                           2 * eyeRadius);

                leftEye->setBrush(QBrush(Qt::black));
                rightEye->setBrush(QBrush(Qt::black));

                scene->addItem(leftEye);
                scene->addItem(rightEye);
            }
        }
    }




    void drawLadder(const QPointF& startPoint, const QPointF& endPoint, int numSteps, qreal ladderWidth, qreal parallelLineWidth, qreal stepThickness) {
        // Calculate the step size
        qreal stepSize = 1.0 / numSteps;

        // Create a QGraphicsItemGroup to hold ladder items
        QGraphicsItemGroup* ladderGroup = new QGraphicsItemGroup;

        // Set the pen for the parallel lines
        QPen parallelLinePen(Qt::blue);
        parallelLinePen.setWidthF(parallelLineWidth);

        // Draw the parallel lines of the ladder
        QGraphicsLineItem* ladderLine1 = new QGraphicsLineItem(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
        QGraphicsLineItem* ladderLine2 = new QGraphicsLineItem(startPoint.x(), startPoint.y() + ladderWidth, endPoint.x(), endPoint.y() + ladderWidth);

        ladderLine1->setPen(parallelLinePen);
        ladderLine2->setPen(parallelLinePen);

        ladderGroup->addToGroup(ladderLine1);
        ladderGroup->addToGroup(ladderLine2);

        // Set the pen for the steps
        QPen stepPen(Qt::blue);
        stepPen.setWidthF(stepThickness);  // Set the thickness of the steps

        // Draw the steps between the parallel lines
        for (int i = 0; i <= numSteps; ++i) {
            qreal t = stepSize * i;
            QPointF currentPoint = startPoint + t * (endPoint - startPoint);

            QGraphicsLineItem* stepLine = new QGraphicsLineItem(currentPoint.x(), currentPoint.y(), currentPoint.x(), currentPoint.y() + ladderWidth);
            stepLine->setPen(stepPen);
            ladderGroup->addToGroup(stepLine);
        }

        // Add the ladder group to the scene
        scene->addItem(ladderGroup);
    }


private slots:
    void on_ThrowDice_clicked();

    void on_StartButton_clicked();
    void on_BoardSize_editingFinished();
    void on_Diff_currentIndexChanged(int index);
    void on_NumPlayers_currentIndexChanged(int index);
    void on_RandomBoard_clicked();
};
#endif // MAINWINDOW_H
