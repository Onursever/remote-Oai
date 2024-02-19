#include "host.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QFile>
#include <QStandardPaths>

host::host(QObject *parent)
    : QObject{parent}
{}

void host::checkgNB_conf(Ui_MainWindow *ui)
{
    name=ui->userName->toPlainText();
    password=ui->Password->toPlainText();
    if(ui->standAlone->isChecked())
        stanAlone=" --sa";
    if(ui->Cont_Tx->isChecked())
        ContTx=" --continuous-tx";
    if(ui->Ee->isChecked())
        E=" -E";
    static int gnbRxTxTime=0;
    gnbRxTxTime = ui->gNB_Rx_Tx_Time->value();
    if(gnbRxTxTime)
        gNBminRxTxTime =" --gNBs.[0].min_rxtxtime " + QString::number(gnbRxTxTime);
    qDebug() << "cHECK conf gNB'e girdi" << gNBminRxTxTime ;
}

void host::reset() {
    name.clear();
    password.clear();
    confpath.clear();
    stanAlone.clear();
    E.clear();
    ContTx.clear();
}

QString host::generate_ScriptContent_gNB(){
    QString scriptContentgNB;
    scriptContentgNB += "#!/bin/bash\n";
    scriptContentgNB += "password=\"" + password + "\"\n";
    scriptContentgNB += "cd ~/openairinterface5g || exit\n";
    scriptContentgNB += "source oaienv || exit\n";
    scriptContentgNB += "cd cmake_targets/ran_build/build || exit\n";
    scriptContentgNB += "echo \"$password\" | sudo -S ./nr-softmodem " + confpath  + gNBminRxTxTime + stanAlone + E + ContTx + "\n";

    qDebug() << "scriptcontent func" << gNBminRxTxTime ;
    return scriptContentgNB;
}

bool host::writeToFile_gNB(const QString& filePath, const QString& content){
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

void host::select_gNB_Conf(const QString &homePath, Ui_MainWindow *ui)
{
    QString newPath = homePath + "/openairinterface5g";
    confpath = QFileDialog::getOpenFileName(nullptr, "", QStandardPaths::writableLocation(QStandardPaths::HomeLocation), "Conf File (*.conf*)");
    if (!confpath.isEmpty()) {
        QDir homeDir(newPath);
        QString startRelativePath = homeDir.relativeFilePath(confpath);
        confpath = "-O ../../../" + startRelativePath;
        ui->textBrowser->setText(confpath.section('/', -1));
       }
}
