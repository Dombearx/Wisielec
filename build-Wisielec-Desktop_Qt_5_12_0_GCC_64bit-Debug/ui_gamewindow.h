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
    QTableView *rankingView;
    QLineEdit *userEdit;
    QLabel *label_2;
    QLineEdit *letterEdit;
    QPushButton *letterBtn;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *pointsView;

    void setupUi(QWidget *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QString::fromUtf8("GameWindow"));
        GameWindow->setWindowModality(Qt::NonModal);
        GameWindow->resize(530, 310);
        textEdit = new QTextEdit(GameWindow);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setEnabled(false);
        textEdit->setGeometry(QRect(10, 200, 501, 91));
        textEdit->setMidLineWidth(0);
        textEdit->setReadOnly(true);
        label = new QLabel(GameWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 0, 271, 31));
        label->setWordWrap(false);
        graphicsView = new QGraphicsView(GameWindow);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(340, 10, 171, 171));
        graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
        rankingView = new QTableView(GameWindow);
        rankingView->setObjectName(QString::fromUtf8("rankingView"));
        rankingView->setGeometry(QRect(110, 30, 221, 101));
        userEdit = new QLineEdit(GameWindow);
        userEdit->setObjectName(QString::fromUtf8("userEdit"));
        userEdit->setGeometry(QRect(10, 50, 71, 25));
        userEdit->setReadOnly(true);
        label_2 = new QLabel(GameWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 30, 101, 16));
        letterEdit = new QLineEdit(GameWindow);
        letterEdit->setObjectName(QString::fromUtf8("letterEdit"));
        letterEdit->setEnabled(false);
        letterEdit->setGeometry(QRect(10, 140, 51, 41));
        letterBtn = new QPushButton(GameWindow);
        letterBtn->setObjectName(QString::fromUtf8("letterBtn"));
        letterBtn->setEnabled(false);
        letterBtn->setGeometry(QRect(70, 140, 261, 41));
        label_3 = new QLabel(GameWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 10, 231, 21));
        label_4 = new QLabel(GameWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 80, 67, 17));
        pointsView = new QLineEdit(GameWindow);
        pointsView->setObjectName(QString::fromUtf8("pointsView"));
        pointsView->setGeometry(QRect(10, 100, 71, 25));

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QWidget *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "Wisielec", nullptr));
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
        label_3->setText(QApplication::translate("GameWindow", "<html><head/><body><p align=\"right\">Ranking</p></body></html>", nullptr));
        label_4->setText(QApplication::translate("GameWindow", "Punkty", nullptr));
        pointsView->setText(QApplication::translate("GameWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
