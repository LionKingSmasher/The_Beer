#include "clientwindow.h"
#include "ui_clientwindow.h"

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

void ClientWindow::on_Server_Start_clicked()
{
}

void ClientWindow::on_Server_End_Button_clicked()
{
    ui->LogBox->setPlainText(ui->LogBox->toPlainText() + "Server End!\n");
    beer->server_end();
}

void ClientWindow::on_Server_Start_Button_clicked()
{
    ui->LogBox->setPlainText(ui->LogBox->toPlainText() + "Server Start!\n");
    beer->server_start();
}

void ClientWindow::on_ConnectButton_clicked()
{
    beer->connectServer(ui->IPBox->text().toStdString().c_str(), ui->PortBOX->text().toUShort());
}
