#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <sys/signal.h>

#include <QStringList>
#include <QMessageBox>
#include <QDate>

#define BEER_FAILURE(X) if (X == BEERSOCK_FAIL)

char ip[INET_ADDRSTRLEN];

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
    , beer(new Beer(this->my_ip, 9999))
{
    ui->setupUi(this);
    QStringList Header;
    Header << "Name" << "IP";
    ui->IPList->setColumnCount(2);
    ui->IPList->setHorizontalHeaderLabels(Header);
    ui->IPList->horizontalHeader()->setStretchLastSection(true);
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

static void closeNodeServer(ClientWindow* ui){
    std::string doneCommand = NodeServerCommand[2]; // done
    write(ui->nodeServer, doneCommand.c_str(), doneCommand.size());
    closeServer(ui->nodeServer);
}

 static void MessageReader(ClientWindow* win){
    memset(&win->beer->msg, 0, 256);
    printf("Test Message");
    while(1){
        win->beer->mtx.lock();
//        if(win->beer->server_open == true){
//            printf("Test Message");
            BEER_FAILURE(win->beer->readClient()){
                printf("Read Error\n");
            }
            printf("%s\n", win->beer->msg);
//        }
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
    closeNodeServer(this);
    beer->server_end();
    beer->server_open = false;
    pthread_cancel(this->readProcHandle);
}

QString ChatMessageSave(QString str){
    QString filename = "save_message"
            + QString::number(QDate::currentDate().year())
            + QString::number(QDate::currentDate().month())
            + QString::number(QDate::currentDate().day())
            + QString::number(QTime::currentTime().hour())
            + QString::number(QTime::currentTime().minute())
            + QString::number(QTime::currentTime().second())
            + QString::number(QTime::currentTime().msec());
    int fd = open(filename.toStdString().c_str(), O_WRONLY | O_CREAT, 0644);
    write(fd, str.toStdString().c_str(), str.toStdString().size());
    close(fd);
    return filename;
}

void ClientWindow::on_Server_Start_Button_clicked()
{
    char msg[256];
    ui->LogBox->insertPlainText("Server Start!\n");
    beer->server_start();
    while(!beer->server_open)
        QApplication::processEvents();
    if(!beer->client_open){
        inet_ntop(AF_INET, &(beer->clntAddr), ip, INET_ADDRSTRLEN);
        beer->connectServer(ip, 9999);
    }
    ui->LogBox->insertPlainText("Welcome! " + QString(ip) + "\n");
    readProc = std::thread(MessageReader, this);
    readProcHandle = readProc.native_handle();
    readProc.detach();
//    while(!beer->server_open){
//        QApplication::processEvents();
//    }
//    char ip[INET_ADDRSTRLEN];
//    inet_ntop(AF_INET, &(beer->clntAddr), ip, INET_ADDRSTRLEN);
//    beer->connectServer(ip, 9999);
    connectNodeServer(node_server_ip, 10000, this);
    std::string command = NodeServerCommand[0] + ui->userName->text().toStdString();
    write(nodeServer, command.c_str(), command.size()); // regist my ip & username

//    write(nodeServer, "Test", 4);
//    read(nodeServer, &msg, 256);
//    printf("Server: %s\n", msg);
//    write(nodeServer, "register name=IamGod", 20);
//    read(nodeServer, &msg, 256);
//    write(nodeServer, "done", 4);
//    closeServer(nodeServer);

    while(1){
        if(strlen(beer->msg) > 0){
            //printf("Message %s\n", beer->msg);
            ui->LogBox->insertPlainText(QString(ip) + " : " + QString(beer->msg) + "\n");
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
    strcpy(ip, ui->IPBox->text().toStdString().c_str());
    beer->client_open = true;
}

void ClientWindow::on_sendButton_clicked()
{
    beer->writeServer(ui->lineEdit->text().toStdString().c_str());
    ui->LogBox->insertPlainText("Me: " + ui->lineEdit->text() + "\n");
}


void ClientWindow::on_lineEdit_returnPressed()
{
    beer->writeServer(ui->lineEdit->text().toStdString().c_str());
    ui->LogBox->insertPlainText("Me: " + ui->lineEdit->text() + "\n");
    ui->lineEdit->setText("");
}


void ClientWindow::on_actionLoad_Chat_triggered()
{

}


void ClientWindow::on_actionSave_Chat_triggered()
{
    QString file = ChatMessageSave(ui->LogBox->toPlainText());
}

