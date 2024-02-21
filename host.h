#ifndef HOST_H
#define HOST_H
#include <QObject>
#include <QString>
#include <QProcess>

class Ui_MainWindow;

class host : public QObject
{
    Q_OBJECT
public:
    explicit host(QObject *parent = nullptr);
    QString name;
    QString password;
    QString confpath;
    QString gNBminRxTxTime;
    QString stanAlone;
    QString E;
    QString ContTx;
    QProcess start_gNB_process;

signals:

public slots:
    void reset();
    void checkgNB_conf(Ui_MainWindow *ui);
    QString generate_ScriptContent_gNB();
    bool writeToFile_gNB(const QString& filePath, const QString& content);
    void select_gNB_Conf(const QString& homePath, Ui_MainWindow *ui);

private:


};

#endif // HOST_H
