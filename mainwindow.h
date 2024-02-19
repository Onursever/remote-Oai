#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "host.h"
#include "client.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    host hostuser;
    QString homePath;
    client clientuser;

public slots:
    void on_chech_gNB_cont_plane_clicked();
    void gNB_unit_settings_clear();
    void on_gNBconfSelect_clicked();
    void UE_unit_settings_clear();

private slots:

    void on_UeconfSelect_clicked();

    void on_check_UE_cont_plane_clicked();

private:

};
#endif // MAINWINDOW_H
