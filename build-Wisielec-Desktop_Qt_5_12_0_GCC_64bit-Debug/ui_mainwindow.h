/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *hostLineEdit;
    QSpinBox *portSpinBox;
    QPushButton *joinGameBtn;
    QPushButton *newGameBtn;
    QSpinBox *portSpinBox_2;
    QLabel *label_2;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(391, 145);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        hostLineEdit = new QLineEdit(centralwidget);
        hostLineEdit->setObjectName(QString::fromUtf8("hostLineEdit"));
        hostLineEdit->setGeometry(QRect(10, 20, 201, 21));
        portSpinBox = new QSpinBox(centralwidget);
        portSpinBox->setObjectName(QString::fromUtf8("portSpinBox"));
        portSpinBox->setGeometry(QRect(220, 20, 71, 21));
        portSpinBox->setMinimum(1);
        portSpinBox->setMaximum(65535);
        portSpinBox->setValue(1234);
        joinGameBtn = new QPushButton(centralwidget);
        joinGameBtn->setObjectName(QString::fromUtf8("joinGameBtn"));
        joinGameBtn->setGeometry(QRect(300, 20, 81, 23));
        newGameBtn = new QPushButton(centralwidget);
        newGameBtn->setObjectName(QString::fromUtf8("newGameBtn"));
        newGameBtn->setGeometry(QRect(90, 70, 81, 21));
        portSpinBox_2 = new QSpinBox(centralwidget);
        portSpinBox_2->setObjectName(QString::fromUtf8("portSpinBox_2"));
        portSpinBox_2->setGeometry(QRect(10, 70, 71, 21));
        portSpinBox_2->setMinimum(1);
        portSpinBox_2->setMaximum(65535);
        portSpinBox_2->setValue(1234);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 101, 16));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 0, 151, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 391, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Wisielec", nullptr));
        hostLineEdit->setText(QApplication::translate("MainWindow", "localhost", nullptr));
        joinGameBtn->setText(QApplication::translate("MainWindow", "Do\305\202\304\205cz", nullptr));
        newGameBtn->setText(QApplication::translate("MainWindow", "Stw\303\263rz gr\304\231", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Stw\303\263rz nowy serwer", nullptr));
        label->setText(QApplication::translate("MainWindow", "Do\305\202\304\205cz do istniej\304\205cego serwera", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
