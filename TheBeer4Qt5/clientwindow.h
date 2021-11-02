#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <thread>
#include "beer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWindow; }
QT_END_NAMESPACE

const std::string NodeServerCommand[2] = {
    "register name=", // register command
    "get ip id=",     // get ip command
};

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();
    Beer* beer;
    Ui::ClientWindow *ui;
    int nodeServer;
    struct sockaddr_in nodeServerAddr;

private slots:
    void on_Server_Start_clicked();

    void on_Server_End_Button_clicked();

    void on_Server_Start_Button_clicked();

    void on_ConnectButton_clicked();

private:
    static constexpr char* my_ip = "10.80.162.236";
    std::thread readProc;

};
#endif // CLIENTWINDOW_H
