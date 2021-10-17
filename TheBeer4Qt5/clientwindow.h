#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include "beer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWindow; }
QT_END_NAMESPACE

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private slots:
    void on_Server_Start_clicked();

    void on_Server_End_Button_clicked();

    void on_Server_Start_Button_clicked();

private:
    static constexpr char* my_ip = "10.80.163.172";
    Ui::ClientWindow *ui;
    Beer* beer;

};
#endif // CLIENTWINDOW_H
