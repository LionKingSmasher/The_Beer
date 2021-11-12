/********************************************************************************
** Form generated from reading UI file 'clientwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWINDOW_H
#define UI_CLIENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientWindow
{
public:
    QAction *actionSave_Chat;
    QAction *actionLoad_Chat;
    QWidget *centralwidget;
    QLineEdit *PortBOX;
    QLineEdit *IPBox;
    QLabel *label;
    QLabel *label_2;
    QPlainTextEdit *LogBox;
    QPushButton *Server_Start_Button;
    QPushButton *Server_End_Button;
    QPushButton *ConnectButton;
    QLineEdit *userName;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QTableWidget *IPList;
    QPushButton *sendButton;
    QMenuBar *menubar;
    QMenu *menuSave;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ClientWindow)
    {
        if (ClientWindow->objectName().isEmpty())
            ClientWindow->setObjectName(QString::fromUtf8("ClientWindow"));
        ClientWindow->resize(1177, 675);
        actionSave_Chat = new QAction(ClientWindow);
        actionSave_Chat->setObjectName(QString::fromUtf8("actionSave_Chat"));
        actionLoad_Chat = new QAction(ClientWindow);
        actionLoad_Chat->setObjectName(QString::fromUtf8("actionLoad_Chat"));
        centralwidget = new QWidget(ClientWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        PortBOX = new QLineEdit(centralwidget);
        PortBOX->setObjectName(QString::fromUtf8("PortBOX"));
        PortBOX->setGeometry(QRect(70, 600, 431, 25));
        IPBox = new QLineEdit(centralwidget);
        IPBox->setObjectName(QString::fromUtf8("IPBox"));
        IPBox->setGeometry(QRect(70, 560, 431, 25));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 560, 67, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 600, 67, 17));
        LogBox = new QPlainTextEdit(centralwidget);
        LogBox->setObjectName(QString::fromUtf8("LogBox"));
        LogBox->setGeometry(QRect(10, 10, 811, 461));
        Server_Start_Button = new QPushButton(centralwidget);
        Server_Start_Button->setObjectName(QString::fromUtf8("Server_Start_Button"));
        Server_Start_Button->setGeometry(QRect(670, 520, 151, 41));
        Server_End_Button = new QPushButton(centralwidget);
        Server_End_Button->setObjectName(QString::fromUtf8("Server_End_Button"));
        Server_End_Button->setGeometry(QRect(670, 574, 151, 41));
        ConnectButton = new QPushButton(centralwidget);
        ConnectButton->setObjectName(QString::fromUtf8("ConnectButton"));
        ConnectButton->setGeometry(QRect(510, 520, 151, 101));
        userName = new QLineEdit(centralwidget);
        userName->setObjectName(QString::fromUtf8("userName"));
        userName->setGeometry(QRect(70, 520, 431, 25));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 520, 67, 17));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 480, 651, 25));
        IPList = new QTableWidget(centralwidget);
        if (IPList->columnCount() < 2)
            IPList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        IPList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        IPList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        IPList->setObjectName(QString::fromUtf8("IPList"));
        IPList->setGeometry(QRect(830, 20, 331, 591));
        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(670, 470, 151, 36));
        ClientWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ClientWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1177, 29));
        menuSave = new QMenu(menubar);
        menuSave->setObjectName(QString::fromUtf8("menuSave"));
        ClientWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ClientWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ClientWindow->setStatusBar(statusbar);

        menubar->addAction(menuSave->menuAction());
        menuSave->addAction(actionSave_Chat);
        menuSave->addAction(actionLoad_Chat);

        retranslateUi(ClientWindow);

        QMetaObject::connectSlotsByName(ClientWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ClientWindow)
    {
        ClientWindow->setWindowTitle(QCoreApplication::translate("ClientWindow", "ClientWindow", nullptr));
        actionSave_Chat->setText(QCoreApplication::translate("ClientWindow", "Save Chat", nullptr));
        actionLoad_Chat->setText(QCoreApplication::translate("ClientWindow", "Load Chat", nullptr));
        label->setText(QCoreApplication::translate("ClientWindow", "IP", nullptr));
        label_2->setText(QCoreApplication::translate("ClientWindow", "PORT", nullptr));
        Server_Start_Button->setText(QCoreApplication::translate("ClientWindow", "Start Server", nullptr));
        Server_End_Button->setText(QCoreApplication::translate("ClientWindow", "End Server", nullptr));
        ConnectButton->setText(QCoreApplication::translate("ClientWindow", "Connect", nullptr));
        label_3->setText(QCoreApplication::translate("ClientWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem = IPList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ClientWindow", "NAME", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = IPList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ClientWindow", "IP", nullptr));
        sendButton->setText(QCoreApplication::translate("ClientWindow", "PushButton", nullptr));
        menuSave->setTitle(QCoreApplication::translate("ClientWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientWindow: public Ui_ClientWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWINDOW_H
