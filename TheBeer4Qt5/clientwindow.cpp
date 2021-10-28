#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <sys/signal.h>

#include <QMessageBox>

#define BEER_FAILURE(X) if (X == BEERSOCK_FAIL)

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
    , beer(new Beer(this->my_ip, 9999))
{
    ui->setupUi(this);
}

ClientWindow::~ClientWindow()
{
    delete beer;
    delete ui;
}

static void connectNodeServer(const char* ip, uint16_t port, ClientWindow* ui){
    ui->nodeServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    ui->nodeServerAddr.sin_addr.s_addr = inet_addr(ip);
    ui->nodeServerAddr.sin_port = htons(port);
    ui->nodeServerAddr.sin_family = AF_INET;
    if(connect(ui->nodeServer, (struct sockaddr*)&ui->nodeServerAddr, sizeof(ui->nodeServerAddr)) == -1){
        printf("Connect Error...\n");
    }
}

static void closeServer(int fd){
    close(fd);
}

 static void MessageReader(ClientWindow* win){
    memset(&win->beer->msg, 0, 256);
//    printf("Test Message");
    while(1){
        win->beer->mtx.lock();
        if(win->beer->server_open == true){
//            printf("Test Message");
            BEER_FAILURE(win->beer->readClient()){
                printf("Read Error\n");
            }
        }
        win->beer->mtx.unlock();
    }
}

void ClientWindow::on_Server_Start_clicked()
{
}

void ClientWindow::on_Server_End_Button_clicked()
{
    ui->LogBox->setPlainText(ui->LogBox->toPlainText() + "Server End!\n");
    if(beer->server_open == true){
        ui->LogBox->setPlainText(ui->LogBox->toPlainText() + "True!\n");
    }
    else{
        ui->LogBox->setPlainText(ui->LogBox->toPlainText() + "False!\n");
    }
    beer->server_end();
    beer->server_open = false;
}

void ClientWindow::on_Server_Start_Button_clicked()
{
    char msg[256];
    ui->LogBox->setPlainText(ui->LogBox->toPlainText() + "Server Start!\n");
    beer->server_start();
    readProc = std::thread(MessageReader, this);
    readProc.detach();
    connectNodeServer("10.80.162.236", 10000, this);

    write(nodeServer, "Test", 4);
    read(nodeServer, &msg, 256);
    printf("Server: %s\n", msg);
    write(nodeServer, "register name=IamGod", 20);
    read(nodeServer, &msg, 256);
    write(nodeServer, "done", 4);
    closeServer(nodeServer);

    while(1){
        if(strlen(beer->msg) > 0){
            printf("Message %s\n", beer->msg);
            ui->LogBox->setPlainText(ui->LogBox->toPlainText() + QString(beer->msg) + "\n");
            memset(&beer->msg, 0, 1024);
        }
        QApplication::processEvents();
    }


//    readProc = fork();
//    if(readProc == 0){
//        memset(&beer->msg, 0, 256);
//        printf("Test Message");
//        ui->LogBox->setPlainText(ui->LogBox->toPlainText() + QString("beer->msg"));
//        while(1){
//            printf("Test Message");
//            BEER_FAILURE(beer->readClient(&beer->msg)){
//                printf("Read Error\n");
//            }
//            if(strlen(beer->msg) > 0){
//                printf("Message %s\n", beer->msg);
//                ui->LogBox->setPlainText(ui->LogBox->toPlainText() + QString(beer->msg));
//            }
//        }
//    }
}

void ClientWindow::on_ConnectButton_clicked()
{
    beer->connectServer(ui->IPBox->text().toStdString().c_str(), ui->PortBOX->text().toUShort());
}
