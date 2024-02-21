#include "mainwindow.h"

#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString qssFilePath = "/home/nuc/Downloads/Integrid.qss";

    // QSS dosyasını okuyun
    QFile qssFile(qssFilePath);
    qssFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(qssFile.readAll());

    // QApplication'e QSS dosyasından tema uygulayın
    a.setStyleSheet(styleSheet);
    MainWindow w;
    w.show();
    return a.exec();
}
