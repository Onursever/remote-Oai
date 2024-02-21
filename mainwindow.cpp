#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "host.h"
#include "client.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gNB_unit_settings_clear();
    UE_unit_settings_clear();
    homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// -----*** gNB Part ***-----
// -----*** gNB Part ***-----
// -----*** gNB Part ***-----

void MainWindow::on_gNBconfSelect_clicked()
{
    hostuser.select_gNB_Conf(homePath,ui);
}

void MainWindow::on_chech_gNB_cont_plane_clicked()
{
    hostuser.checkgNB_conf(ui);
    QString filepathgNB = homePath + "/server_gNB.sh";
    QString scriptContentgNB = hostuser.generate_ScriptContent_gNB();
    hostuser.reset();

    if (hostuser.writeToFile_gNB(filepathgNB, scriptContentgNB)) {
        qDebug() << "Dosya oluşturuldu: " << filepathgNB;
    } else {
        qDebug() << "Dosya oluşturulamadı: " << filepathgNB;
    }
    gNB_unit_settings_clear();
}


void MainWindow::gNB_unit_settings_clear()
{
    ui->gNB_Rx_Tx_Time->setRange(6,10);
    ui->userName->clear();
    ui->Password->clear();
    ui->gNB_Rx_Tx_Time->setValue(6);
    ui->textBrowser->setText("../.conf");
    ui->standAlone->setChecked(false);
    ui->Ee->setChecked(false);
    ui->Cont_Tx->setChecked(false);

}

// -----*** UE Part ***-----
// -----*** UE Part ***-----
// -----*** UE Part ***-----


void MainWindow::on_UeconfSelect_clicked()
{
    clientuser.select_UE_Conf(homePath,ui);
}

void MainWindow::on_check_UE_cont_plane_clicked()
{
    clientuser.checkUE_conf(ui);
    QString filepathUE = homePath + "/server_UE_start.sh";
    QString filepathUE_Server = homePath + "/Server_UE.sh";
    QString scriptContentUE = clientuser.generate_ScriptContent_UE();
    QString scriptContentUE_Server = clientuser.generate_ScriptContent_UE_Server(filepathUE);
    clientuser.reset();

    if(clientuser.writeToFile_UE(filepathUE_Server, scriptContentUE_Server)){
        qDebug() << "Dosya oluşturuldu: " << filepathUE;
    } else {
        qDebug() << "Dosya oluşturulamadı: " << filepathUE;
    }

    if(clientuser.writeToFile_UE(filepathUE, scriptContentUE)){
        qDebug() << "Dosya oluşturuldu: " << filepathUE_Server;
    } else {
        qDebug() << "Dosya oluşturulamadı: " << filepathUE_Server;
    }

    UE_unit_settings_clear();
}

void MainWindow::UE_unit_settings_clear()
{
    QDoubleValidator *validator = new QDoubleValidator(this);
    QRegularExpressionValidator *validatorr = new QRegularExpressionValidator(QRegularExpression("(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"));
    ui->Ip_UE->setPlaceholderText("e.g. 192.168.2.1");
    ui->Ip_UE->setValidator(validatorr);
    ui->R_Block_UE->setRange(30,130);
    ui->R_Block_UE->setValue(106);
    ui->Numerology_UE->setRange(0,6);
    ui->Numerology_UE->setValue(1);
    ui->Band_UE->setRange(1,262);
    ui->Band_UE->setValue(78);
    ui->C_UE->setDecimals(0);
    ui->C_UE->setRange(0, 3619200100);
    ui->C_UE->setValue(3619200000);
    ui->IMSI_UE->setValidator(validator);
    ui->IMSI_UE->setText("001010000000001");
    ui->Text_Path_UE->setText("../.conf");
    ui->userName_UE->clear();
    ui->Password_UE->clear();
    ui->Ip_UE->clear();
    qDebug() << "UE clear çalıştı";

}

void MainWindow::on_Start_UE_clicked()
{
    QStringList UE_process_arg;
    UE_process_arg << "-c" << "chmod +x Server_UE.sh && ./Server_UE.sh";
    startProcess(&clientuser.startUE_server, homePath, UE_process_arg);
}


void MainWindow::on_start_gNB_clicked()
{
    QStringList gNB_process_arg;
    gNB_process_arg << "-c" << "chmod +x server_gNB.sh && ./server_gNB.sh";
    startProcess(&hostuser.start_gNB_process, homePath, gNB_process_arg);
}


void MainWindow::on_close_gNB_clicked()
{
    hostuser.start_gNB_process.kill();
}



void MainWindow::startProcess(QProcess *process, const QString &workingDirectory, const QStringList &arguments){
    process->setWorkingDirectory(workingDirectory);
    process->start("bash", arguments);
    qDebug()<< "homepath"<<workingDirectory << arguments;
}

void MainWindow::on_Close_UE_clicked()
{
    clientuser.startUE_server.kill();
}

