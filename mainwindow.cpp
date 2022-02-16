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
    if(!ans_feild.isEmpty()){
        if(ans_feild.back() == ' '){
            ans_feild.chop(3);
        } else {
            ans_feild.chop(1);
        }
        emit changing_line();
    }
}

void MainWindow::butt_sm_clicked(){
    ans_feild.replace(',', '.');
//    ans_feild = сalculation(ans_feild.split(" "));
    emit changing_line();
}

bool MainWindow::check_simbol(QString str){
    bool flg = 0;
    for(int i = 0; i < simbol.size(); i++){
        if(use_simbol[i] == '1' && str == simbol[i]){
            flg = true;
        }
    }
    use_simbol = "000000000000000";
    return flg;
}

void MainWindow::butt_clicked(){ ui->answer_line->setText(ans_feild); }

bool MainWindow::check_ins_null(){
    bool flg = false;
    use_simbol = "011111111100001";
    for(int i = ans_feild.size() - 2; i >= 0; i--){
        if(check_simbol(ans_feild[i])){
            flg = true;
        }
    }
    return flg;
}

QString MainWindow::check_input(QString str){
    if(ans_feild.isEmpty()){
        use_simbol = "111111111100010";
        if(check_simbol(str)){
            return str;
        }
    } else if(ans_feild.size() == 1){
        if (ans_feild[0] == '-' ){
            use_simbol = "111111111100000";
            if(check_simbol(str)){
                return str;
            }
        } else {
            if(str == "0" && ans_feild[ans_feild.size() - 1] == '0'){
                if(check_ins_null()){
                    return str;
                }
            } else {
                use_simbol = "111111111100000";
                if(check_simbol(str)){
                    return str;
                }
            }
        }
    } else {
        if(str == "0" && ans_feild[ans_feild.size() - 1] == '0'){
            if(check_ins_null()){
                return str;
            }
        } else {
            use_simbol = "111111111100000";
            if(check_simbol(str)){
                return str;
            }
        }
    }
    return "";
}

MainWindow::~MainWindow()
{
    delete ui;
}


