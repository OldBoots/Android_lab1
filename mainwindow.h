#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct oper{
    char op;
    char prrt;
    int index;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void butt_clicked();
    void butt_0_clicked();
    void butt_1_clicked();
    void butt_2_clicked();
    void butt_3_clicked();
    void butt_4_clicked();
    void butt_5_clicked();
    void butt_6_clicked();
    void butt_7_clicked();
    void butt_8_clicked();
    void butt_9_clicked();
    void butt_min_clicked();
    void butt_plus_clicked();
    void butt_mult_clicked();
    void butt_div_clicked();
    void butt_del_clicked();
    void butt_com_clicked();
    void butt_sm_clicked();

signals:
void changing_line();
void error_sign();

private:
void сalculation();
QString check_input(QString str);
bool check_simbol(QString str, QString use_simbol);
bool check_ins_null();
bool check_express();
bool check_size();
bool check_num(QString str);

private:
    int index;
    QStringList express;
    QString ans_feild;
    QString simbol = "0123456789*/+-.";
    QString use_simbol;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
