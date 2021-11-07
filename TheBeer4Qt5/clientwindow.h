#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <thread>
#include "beer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWindow; }
QT_END_NAMESPACE

const std::string NodeServerCommand[3] = {
    "register name=", // register command
    "get ip id=",     // get ip command
    "done"            // done command
};

const std::string NodeBackCommand[1] = {
    " port="
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
    pthread_t readProcHandle;
    struct sockaddr_in nodeServerAddr;

private slots:
    void on_Server_Start_clicked();

    void on_Server_End_Button_clicked();

    void on_Server_Start_Button_clicked();

    void on_ConnectButton_clicked();

private:
    static constexpr char* my_ip = "192.168.43.164";
    static constexpr char* node_server_ip = "192.168.43.164";
    std::thread readProc;

};
#endif // CLIENTWINDOW_H
