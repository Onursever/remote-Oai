#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QObject>
#include <QProcess>

class Ui_MainWindow;

class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QObject *parent = nullptr);

    QString name;
    QString ip;
    QString password;
    QString confpath;
    QString scriptPath;
    QString resourceBlock;
    QString numerology;
    QString band;
    QString c;
    QString rfsim;
    QString sa;
    QString imsi;
    QString compensation;
    QString e;
    QProcess startUE_server;
signals:

public slots:
    void reset();
    void select_UE_Conf(const QString& homePath, Ui_MainWindow *ui);
    void checkUE_conf(Ui_MainWindow *ui);
    QString generate_ScriptContent_UE();
    QString generate_ScriptContent_UE_Server(const QString& UEpath);
    bool writeToFile_UE(const QString& filePath, const QString& content);

};

#endif // CLIENT_H
