#include "ui_mainwindow.h"
#include "client.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QFile>
#include <QStandardPaths>

client::client(QObject *parent)
    : QObject{parent}
{}

void client::reset(){
    name.clear();
    ip.clear();
    password.clear();
    confpath.clear();
    scriptPath.clear();
    resourceBlock.clear();
    band.clear();
    c.clear();
    e.clear();
    sa.clear();
    imsi.clear();
    compensation.clear();
}

void client::select_UE_Conf(const QString &homePath, Ui_MainWindow *ui)
{
    static QString newPath = homePath + "/openairinterface5g";
    confpath = QFileDialog::getOpenFileName(nullptr, "", QStandardPaths::writableLocation(QStandardPaths::HomeLocation), "Tüm dosyalar (*.conf*)");
    if (!confpath.isEmpty()) {
        QDir homeDir(newPath);
        QString startRelativePath = homeDir.relativeFilePath(confpath);
        confpath = "-O ../../../" + startRelativePath;
        ui->Text_Path_UE->setText(confpath.section('/', -1));
    }
}

void client::checkUE_conf(Ui_MainWindow *ui)
{
    name=ui->userName_UE->toPlainText();
    password=ui->Password_UE->toPlainText();
    ip=ui->Ip_UE->text();
    resourceBlock=" -r " + QString::number(ui->R_Block_UE->value());
    numerology=" --numerology " + QString::number(ui->Numerology_UE->value());
    c=" -C " + QString::number(ui->C_UE->value(),'f', 0);
    band=" --band " + QString::number(ui->Band_UE->value());
    imsi=" --uicc0.imsi " +ui->IMSI_UE->text();
    if(ui->UE_fo_comp->isChecked())
        compensation=" --ue-fo-compensation";
    if(ui->StandAlone_Ue->isChecked())
        sa=" --sa";
    if (ui->E_Ue->isChecked())
        e=" -E";

}

QString client::generate_ScriptContent_UE()
{
    QString scriptContentUE;
    scriptContentUE += "#!/bin/bash\n";
    scriptContentUE += "password=\"" + password + "\"\n";
    scriptContentUE += "cd ~/openairinterface5g || exit\n";
    scriptContentUE += "source oaienv || exit\n";
    scriptContentUE += "cd cmake_targets/ran_build/build || exit\n";
    scriptContentUE += "echo \"$password\" | sudo -S ./nr-uesoftmodem " + confpath + resourceBlock + numerology + c + band + imsi + compensation + sa + e + "\n";
    return scriptContentUE;

}

QString client::generate_ScriptContent_UE_Server(const QString& UEpath)
{
    QString scriptContentUE_Server;
    scriptContentUE_Server += "#!/bin/bash\n";
    scriptContentUE_Server += "source_file=\"" + UEpath +"\"\n";
    scriptContentUE_Server += "destination_name=\"" + name + "\"\n";
    scriptContentUE_Server += "destination_ip=\"" + ip + "\"\n";
    scriptContentUE_Server += "destination_path=\"/home/" + name + "/\"\n";
    scriptContentUE_Server += "password=\"" + password + "\"\n";
    scriptContentUE_Server += "sshpass -p \"$password\" scp \"$source_file\" \"$destination_name@$destination_ip:$destination_path\"\n";
    scriptContentUE_Server += "sshpass -p \"$password\" ssh -t \"$destination_name@$destination_ip\" << EOF\n";
    scriptContentUE_Server += "chmod +x server_UE_start.sh\n";
    scriptContentUE_Server += "./server_UE_start.sh\n";
    scriptContentUE_Server += "EOF";
    return scriptContentUE_Server;
}

bool client::writeToFile_UE(const QString &filePath, const QString &content)
{

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Dosya açılamadı: " << filePath;
        return false;
    }

    QTextStream out(&file);
    out << content;

    file.close();
    qDebug() << "Dosya yazıldı: " << filePath;

    return true;
}
