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
    connect(ui->butt_del, SIGNAL(pressed()), this, SLOT(start_time()));
    connect(ui->butt_del, SIGNAL(released()), this, SLOT(stop_time()));
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(end_time()));

    connect(ui->butt_sm, SIGNAL(clicked()), this, SLOT(butt_sm_clicked()));

    connect(this, SIGNAL(changing_line()), this, SLOT(butt_clicked()));

    express.resize(3);
    index = 0;
}

void MainWindow::start_time(){
    timer->start(1000);
}
void MainWindow::stop_time(){
    timer->stop();
}
void MainWindow::end_time(){
    timer->stop();
        express[0].clear();
        express[1].clear();
        express[2].clear();
        ans_feild.clear();
        index = 0;
        emit changing_line();
}
void MainWindow::butt_0_clicked(){ ans_feild += check_input("0"); emit changing_line(); }
void MainWindow::butt_1_clicked(){ ans_feild += check_input("1"); emit changing_line(); }
void MainWindow::butt_2_clicked(){ ans_feild += check_input("2"); emit changing_line(); }
void MainWindow::butt_3_clicked(){ ans_feild += check_input("3"); emit changing_line(); }
void MainWindow::butt_4_clicked(){ ans_feild += check_input("4"); emit changing_line(); }
void MainWindow::butt_5_clicked(){ ans_feild += check_input("5"); emit changing_line(); }
void MainWindow::butt_6_clicked(){ ans_feild += check_input("6"); emit changing_line(); }
void MainWindow::butt_7_clicked(){ ans_feild += check_input("7"); emit changing_line(); }
void MainWindow::butt_8_clicked(){ ans_feild += check_input("8"); emit changing_line(); }
void MainWindow::butt_9_clicked(){ ans_feild += check_input("9"); emit changing_line(); }

void MainWindow::butt_min_clicked(){ ans_feild += check_input("-"); emit changing_line(); }
void MainWindow::butt_plus_clicked(){ ans_feild += check_input("+"); emit changing_line(); }
void MainWindow::butt_mult_clicked(){ ans_feild += check_input("*"); emit changing_line(); }
void MainWindow::butt_div_clicked(){ ans_feild += check_input("/"); emit changing_line(); }

void MainWindow::butt_com_clicked(){ans_feild += check_input(","); emit changing_line();}

void MainWindow::butt_del_clicked(){
    if(index == 2){
        if (!express[2].isEmpty()){            // Second num
            express[2].chop(1);
            ans_feild.chop(1);
        } else {
            express[1] = "";
            ans_feild.chop(3);
            index = 0;
        }
    }
    if(index == 0){
        if (!express[0].isEmpty()){
            express[0].chop(1);
            ans_feild.chop(1);
        }
    }
    emit changing_line();
}

void MainWindow::сalculation(){
    double ans;
    if(express[1] == "*"){
        ans = express[0].toDouble() * express[2].toDouble();
    } else if(express[1] == "/"){
        ans = express[0].toDouble() / express[2].toDouble();
    } else if(express[1] == "+"){
        ans = express[0].toDouble() + express[2].toDouble();
    } else {
        ans = express[0].toDouble() - express[2].toDouble();
    }
    express[0] = ans_feild = QString::number(ans);
    ans_feild.replace('.', ',');
    express[1].clear();
    express[2].clear();
    index = 0;
}

void MainWindow::butt_sm_clicked(){
    if(check_num(express[0]) && !express[0].isEmpty() && check_num(express[2])){
        if(express[1] == "/" && express[2].toDouble() == 0){
            qDebug("Error: Division on null!");
            QMessageBox::warning(this, "Error","You divide by zero!");
            return;
        } else {
           сalculation();
        }
    } else {
        qDebug("Error: Express is empty!");
        QMessageBox::warning(this, "Error","You haven't fully entered the expression!");
        return;
    }
    emit changing_line();
}

bool MainWindow::check_simbol(QString str, QString use_simbol){
    return use_simbol.contains(str);
}

void MainWindow::butt_clicked(){ ui->answer_line->setText(ans_feild); }

bool MainWindow::check_ins_null(){
    for(int i = express[index].size() - 1; i >= 0; i--){
        if(check_simbol(express[index][i], "123456789.")){
            return true;
        }
    }
    return false;
}

bool MainWindow::check_num(QString str){
    for(int i = 0; i < str.size(); i++){
        if(check_simbol(str[i], "0123456789")){
            return true;
        }
    }
    return false;
}

bool MainWindow::check_express(){
    if(index == 2){
        return false;
    }
    return check_num(express[index]);
}

bool MainWindow::check_size(){
    if(express[index].size() <= 10){
        return true;
    }
    return false;
}

QString MainWindow::check_input(QString str){
    if(express[index].isEmpty()) {                                                                    // First simbol
        if (check_simbol(str, "0123456789-")){
            express[index] += str;
            return str;
        }
    }
    if(str == "," && !express[index].contains(".") && check_size()){                                  // Check .
        express[index] += ".";
        return str;
    }
    if((check_simbol(str, "*/+-") && check_express() && check_size())){                               // Input */+-
        index = 2;
        express[1] += str;
        return " " + str + " ";
    }
    if(express[index][express[index].size() - 1] == '0' && check_size()){                             // Check 0
        if(check_ins_null()){
            express[index] += str;
            return str;
        }
    } else if(check_simbol(str, "0123456789") && check_size()){
        express[index] += str;
        return str;
    }
    return "";
}

MainWindow::~MainWindow()
{
    delete ui;
}


