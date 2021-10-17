/********************************************************************************
** Form generated from reading UI file 'clientwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWINDOW_H
#define UI_CLIENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientWindow
{
public:
    QWidget *centralwidget;
    QListView *IPNodeList;
    QLineEdit *PortBOX;
    QLineEdit *IPBox;
    QLabel *label;
    QLabel *label_2;
    QPlainTextEdit *LogBox;
    QPushButton *Server_Start_Button;
    QPushButton *Server_End_Button;
    QPushButton *ConnectButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ClientWindow)
    {
        if (ClientWindow->objectName().isEmpty())
            ClientWindow->setObjectName(QString::fromUtf8("ClientWindow"));
        ClientWindow->resize(1177, 600);
        centralwidget = new QWidget(ClientWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        IPNodeList = new QListView(centralwidget);
        IPNodeList->setObjectName(QString::fromUtf8("IPNodeList"));
        IPNodeList->setGeometry(QRect(830, 10, 331, 541));
        PortBOX = new QLineEdit(centralwidget);
        PortBOX->setObjectName(QString::fromUtf8("PortBOX"));
        PortBOX->setGeometry(QRect(60, 510, 431, 25));
        IPBox = new QLineEdit(centralwidget);
        IPBox->setObjectName(QString::fromUtf8("IPBox"));
        IPBox->setGeometry(QRect(60, 480, 431, 25));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 480, 67, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 510, 67, 17));
        LogBox = new QPlainTextEdit(centralwidget);
        LogBox->setObjectName(QString::fromUtf8("LogBox"));
        LogBox->setGeometry(QRect(10, 10, 811, 461));
        Server_Start_Button = new QPushButton(centralwidget);
        Server_Start_Button->setObjectName(QString::fromUtf8("Server_Start_Button"));
        Server_Start_Button->setGeometry(QRect(670, 480, 151, 25));
        Server_End_Button = new QPushButton(centralwidget);
        Server_End_Button->setObjectName(QString::fromUtf8("Server_End_Button"));
        Server_End_Button->setGeometry(QRect(670, 510, 151, 25));
        ConnectButton = new QPushButton(centralwidget);
        ConnectButton->setObjectName(QString::fromUtf8("ConnectButton"));
        ConnectButton->setGeometry(QRect(510, 480, 151, 51));
        ClientWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ClientWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1177, 22));
        ClientWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ClientWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ClientWindow->setStatusBar(statusbar);

        retranslateUi(ClientWindow);

        QMetaObject::connectSlotsByName(ClientWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ClientWindow)
    {
        ClientWindow->setWindowTitle(QCoreApplication::translate("ClientWindow", "ClientWindow", nullptr));
        label->setText(QCoreApplication::translate("ClientWindow", "IP", nullptr));
        label_2->setText(QCoreApplication::translate("ClientWindow", "PORT", nullptr));
        Server_Start_Button->setText(QCoreApplication::translate("ClientWindow", "Start", nullptr));
        Server_End_Button->setText(QCoreApplication::translate("ClientWindow", "End", nullptr));
        ConnectButton->setText(QCoreApplication::translate("ClientWindow", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientWindow: public Ui_ClientWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWINDOW_H
