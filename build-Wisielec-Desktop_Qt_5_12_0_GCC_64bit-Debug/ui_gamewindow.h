/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QTextEdit *textEdit;
    QLabel *label;
    QGraphicsView *graphicsView;
    QTableView *tableView;
    QLineEdit *userEdit;
    QLabel *label_2;
    QLineEdit *letterEdit;
    QPushButton *letterBtn;
    QLabel *label_3;

    void setupUi(QWidget *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QString::fromUtf8("GameWindow"));
        GameWindow->resize(481, 379);
        textEdit = new QTextEdit(GameWindow);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setEnabled(false);
        textEdit->setGeometry(QRect(10, 40, 281, 81));
        textEdit->setMidLineWidth(0);
        textEdit->setReadOnly(true);
        label = new QLabel(GameWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 271, 31));
        label->setWordWrap(false);
        graphicsView = new QGraphicsView(GameWindow);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(300, 50, 171, 171));
        graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
        tableView = new QTableView(GameWindow);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 230, 461, 141));
        userEdit = new QLineEdit(GameWindow);
        userEdit->setObjectName(QString::fromUtf8("userEdit"));
        userEdit->setGeometry(QRect(300, 20, 171, 20));
        userEdit->setReadOnly(true);
        label_2 = new QLabel(GameWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(300, 0, 101, 16));
        letterEdit = new QLineEdit(GameWindow);
        letterEdit->setObjectName(QString::fromUtf8("letterEdit"));
        letterEdit->setEnabled(false);
        letterEdit->setGeometry(QRect(10, 130, 51, 31));
        letterBtn = new QPushButton(GameWindow);
        letterBtn->setObjectName(QString::fromUtf8("letterBtn"));
        letterBtn->setEnabled(false);
        letterBtn->setGeometry(QRect(70, 130, 221, 31));
        label_3 = new QLabel(GameWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 195, 111, 21));

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QWidget *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "Form", nullptr));
        textEdit->setHtml(QApplication::translate("GameWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label->setText(QApplication::translate("GameWindow", "<html><head/><body><p>\305\201\304\205czenie z serwerem</p></body></html>", nullptr));
        userEdit->setText(QApplication::translate("GameWindow", "player", nullptr));
        label_2->setText(QApplication::translate("GameWindow", "Nazwa gracza", nullptr));
        letterEdit->setText(QString());
        letterBtn->setText(QApplication::translate("GameWindow", "Podaj liter\304\231", nullptr));
        label_3->setText(QApplication::translate("GameWindow", "Ranking", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
