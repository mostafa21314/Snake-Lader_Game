#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include"dice.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

Dice dice;

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ThrowDice_clicked()
{

    if(currentPlayer==1)
    {
    int x ;
    x=dice.roll();
    QString temp=ui->PositionStore->text();
    Edge test=gameBoard.findEdgeByU(x+temp.toInt());
    if(test.w==1)
    {
        ui->ThrowDiceMessage->setText("You threw the dice and got "+QString::number(x)+" so, your new position is "+QString::number(x+temp.toInt()));
        ui->PositionStore->setText(QString::number(temp.toInt()+x));
        Delay(1600);
        ui->ThrowDiceMessage->setText("");


    }
    else if(test.u<test.v)
    {
        ui->ThrowDiceMessage->setText("You threw the dice and got "+QString::number(x)+" so, you went to \n"+QString::number(x+temp.toInt())+", and there was a ladder so you ranked up to "+QString::number(test.v));
        Delay(500);
        ui->PositionStore->setText(QString::number(test.v));
        Delay(1000);
        ui->ThrowDiceMessage->setText("");

    }
    else if(test.u>test.v)
    {
        ui->ThrowDiceMessage->setText("You threw the dice and got "+QString::number(x)+" so, you went to \n"+QString::number(x+temp.toInt())+", and there was a Snake so you ranked down to "+QString::number(test.v));
        Delay(500);
        ui->PositionStore->setText(QString::number(test.v));
        Delay(1000);
        ui->ThrowDiceMessage->setText("");
    }

    }
    else if(currentPlayer==2)

}






void MainWindow::on_StartButton_clicked()
{
    if(BSizeSet&&DiffSet&&NumPSet)
    {
        Delay(1500);
        BoardBuild(SofBoard,difficulty*0.3);
        initiatePlayers(playersNum);
        ui->ThrowDice->show();
        ui->GraphicsView->show();
        ui->Diff->hide();
        ui->DiffLabel->hide();
        ui->MessageLabel->hide();
        ui->StartButton->hide();
        ui->BoardSize->hide();
        ui->BoardSizeLabel->hide();
        ui->RandomBoard->hide();
        ui->NumPlayers->hide();
        ui->NumPlayersLabel->hide();

    }
    else
    {

        ui->MessageLabel->setText("Please initiate the game conditions or start a random game ");
        Delay(1500);
        ui->MessageLabel->setText("");
    }


}


void MainWindow::on_BoardSize_editingFinished()
{
    if((ui->BoardSize->text().toInt()<5)||(ui->BoardSize->text().toInt()>15))
    {
        ui->BoardSize->setText("Please enter a number between 5 and 15 ");
        BSizeSet=false;
        Delay(1500);
        ui->BoardSize->setText("");
    }
    else
    {
        SofBoard=ui->BoardSize->text().toInt();
        BSizeSet=true;
    }



}


void MainWindow::on_Diff_currentIndexChanged(int index)
{
    switch (index) {
     case 1:
    {
        DiffSet=true; difficulty=1;
        break;
    }
     case 2:
    {
        DiffSet=true; difficulty=2;
        break;
    }
    case 3:
   {
       DiffSet=true; difficulty=3;
       break;
   }

    default:
    {
        DiffSet=false;
        break;
    }
        break;
    }




}


/* int numPlayers;
    std::cout << "Enter the number of players: ";
    std::cin >> numPlayers;

    std::queue<Players> playersQueue; // create queue of players

    // Create and enqueue players based on user input
    for (int i = 1; i <= numPlayers; ++i) {
        playersQueue.push(Players("Player " + std::to_string(i)));
    }

    while (!playersQueue.empty()) {
        Players currentPlayer = playersQueue.front();
        playersQueue.pop();

        std::cout << "It's " << currentPlayer.getname() << "'s turn." << std::endl;

        int xz = currentPlayer.Play(x);
        int sixcounter = 0; // for rolling 3 6s in a row

        while(xz == 6 && sixcounter < 2){  // the roll number is returned if it is a 6 the counter increases by 1
            sixcounter++;
            cout << "It's " << currentPlayer.getname() << "'s turn." << std::endl;
            xz = currentPlayer.Play(x);

            // Check if the player won


        }

        if (xz == 66) { // 66 is returned if the player wins by reaching last tile or takes a ladder connecting to last tile
            std::cout << currentPlayer.getname() << " wins!" << std::endl;
            if(currentPlayer.getnumofmoves()==numofmoves){ // if the player gets the best path they get this message (BFS)
                cout << "You GOT THE LUCKIEST PATH" << endl;
            }
            break;
        }

        // Add the player back to the end of the queue for the next turn
        playersQueue.push(currentPlayer);
    }*/


void MainWindow::on_NumPlayers_currentIndexChanged(int index) // When the number of players is chosen we will use player num in my main instead of cin num of players
{
    switch (index) {
     case 1:
    {
        NumPSet=true; playersNum=1;
        break;
    }
     case 2:
    {
       NumPSet=true; playersNum=2;
        break;
    }
    case 3:
   {
       NumPSet=true; playersNum=3;
       break;
   }
    case 4:
   {
       NumPSet=true; playersNum=4;
       break;
   }

    default:
    {

        NumPSet=false;
        break;
    }
        break;
    }



}





void MainWindow::on_RandomBoard_clicked()
{
    if(NumPSet)
    {
        Delay(1500);
        RandomBoardBuild();        initiatePlayers(playersNum);
        ui->ThrowDice->show();
        ui->GraphicsView->show();
        ui->Diff->hide();
        ui->DiffLabel->hide();
        ui->MessageLabel->hide();
        ui->StartButton->hide();
        ui->BoardSize->hide();
        ui->BoardSizeLabel->hide();
        ui->RandomBoard->hide();
        ui->NumPlayers->hide();
        ui->NumPlayersLabel->hide();

    }
    else
    {
        ui->MessageLabel->setText("Choose the number of players first");
        Delay(1500);
        ui->MessageLabel->setText("");
    }
}

