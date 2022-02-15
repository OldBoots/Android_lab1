#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->butt_0, SIGNAL(clicked()), this, SLOT(butt_0_clicked()));
    connect(ui->butt_1, SIGNAL(clicked()), this, SLOT(butt_1_clicked()));
    connect(ui->butt_2, SIGNAL(clicked()), this, SLOT(butt_2_clicked()));
    connect(ui->butt_3, SIGNAL(clicked()), this, SLOT(butt_3_clicked()));
    connect(ui->butt_4, SIGNAL(clicked()), this, SLOT(butt_4_clicked()));
    connect(ui->butt_5, SIGNAL(clicked()), this, SLOT(butt_5_clicked()));
    connect(ui->butt_6, SIGNAL(clicked()), this, SLOT(butt_6_clicked()));
    connect(ui->butt_7, SIGNAL(clicked()), this, SLOT(butt_7_clicked()));
    connect(ui->butt_8, SIGNAL(clicked()), this, SLOT(butt_8_clicked()));
    connect(ui->butt_9, SIGNAL(clicked()), this, SLOT(butt_9_clicked()));

    connect(ui->butt_mult, SIGNAL(clicked()), this, SLOT(butt_mult_clicked()));
    connect(ui->butt_div, SIGNAL(clicked()), this, SLOT(butt_div_clicked()));
    connect(ui->butt_plus, SIGNAL(clicked()), this, SLOT(butt_plus_clicked()));
    connect(ui->butt_min, SIGNAL(clicked()), this, SLOT(butt_min_clicked()));

    connect(ui->butt_com, SIGNAL(clicked()), this, SLOT(butt_com_clicked()));

    connect(ui->butt_del, SIGNAL(clicked()), this, SLOT(butt_del_clicked()));

    connect(ui->butt_sm, SIGNAL(clicked()), this, SLOT(butt_sm_clicked()));

    connect(this, SIGNAL(changing_line()), this, SLOT(butt_clicked()));


}

void MainWindow::butt_0_clicked(){ ans_feild += "0"; emit changing_line(); }
void MainWindow::butt_1_clicked(){ ans_feild += "1"; emit changing_line(); }
void MainWindow::butt_2_clicked(){ ans_feild += "2"; emit changing_line(); }
void MainWindow::butt_3_clicked(){ ans_feild += "3"; emit changing_line(); }
void MainWindow::butt_4_clicked(){ ans_feild += "4"; emit changing_line(); }
void MainWindow::butt_5_clicked(){ ans_feild += "5"; emit changing_line(); }
void MainWindow::butt_6_clicked(){ ans_feild += "6"; emit changing_line(); }
void MainWindow::butt_7_clicked(){ ans_feild += "7"; emit changing_line(); }
void MainWindow::butt_8_clicked(){ ans_feild += "8"; emit changing_line(); }
void MainWindow::butt_9_clicked(){ ans_feild += "9"; emit changing_line(); }

void MainWindow::butt_min_clicked(){ ans_feild += " - "; emit changing_line(); }
void MainWindow::butt_plus_clicked(){ ans_feild += " + "; emit changing_line(); }
void MainWindow::butt_mult_clicked(){ ans_feild += " * "; emit changing_line(); }
void MainWindow::butt_div_clicked(){ ans_feild += " / "; emit changing_line(); }

void MainWindow::butt_com_clicked(){ans_feild += ","; emit changing_line();}

void MainWindow::butt_del_clicked(){
    if(!ans_feild.isEmpty()){
        if(ans_feild.back() == ' '){
            ans_feild.chop(3);
        } else {
            ans_feild.chop(1);
        }
        emit changing_line();
    }
}

QString MainWindow::сalculation(QStringList express){ // (-) - 0, + - 1,  / - 2, * - 3
    QStringList dop_list;
    double num;
    bool av[4];
    while (express.size() > 1){
        qDebug() << express;
        for(int i = 1; i < express.size(); i += 2){
            av[i] = false;
            if(express[i] == "*"){
                av[0] = true;
            } else if(express[i] == "/"){
                av[1] = true;
            } else if(express[i] == "+"){
                av[2] = true;
            } else if(express[i] == "-"){
                av[3] = true;
            }
        }
        bool flag;
        for(int i = 0; i < express.size() - 2; i++){
            flag = false;
            qDebug() << "1 - " << dop_list << Qt::endl << "(" << av[0] << ", " << av[1] << ", " << av[2] << ", " << av[3] << ")";
            //if(express[i + 1] != "*"){}
            qDebug() << express[i + 1] << " " << av[0];
            if(express[i + 1] == "*" && av[0]){
                qDebug("Z");
                num = express[i].toDouble() * express[i + 2].toDouble();
                dop_list << QString::number(num);
                i += 2;
                flag = true;
            } else if(express[i + 1] == "/" && av[1] && !av[0]){
                if(express[i + 2].toDouble() == 0){ qDebug("Error: Division by zero!");}
                num = express[i].toDouble() / express[i + 2].toDouble();
                dop_list << QString::number(num);
                i += 2;
                flag = true;
            } else if(express[i + 1] == "+" && av[2] && !av[1] && !av[0]){
                qDebug("Z");
                num = express[i].toDouble() + express[i + 2].toDouble();
                dop_list << QString::number(num);
                i += 2;
                flag = true;
            } else if(express[i + 1] == "-" && av[3] && !av[2] && !av[1] && !av[0]){
                num = express[i].toDouble() - express[i + 2].toDouble();
                dop_list << QString::number(num);
                i += 2;
                flag = true;
            } else {
                dop_list << express[i];
            }
            qDebug() << "2 - " << dop_list;
            if(flag){
                express = dop_list;
                dop_list.clear();
            }
//            express = dop_list;
//            dop_list.clear();
        }
    }
    return express[0];
}

void MainWindow::butt_sm_clicked(){
    ans_feild.replace(',', '.');
    ans_feild = сalculation(ans_feild.split(" "));
    emit changing_line();
}

void MainWindow::butt_clicked(){ ui->answer_line->setText(ans_feild); }


MainWindow::~MainWindow()
{
    delete ui;
}

