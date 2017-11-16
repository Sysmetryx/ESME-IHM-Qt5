/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|       EEEEEE       sSSSS  MM       MM     EEEEEE                      LAPORTE Nathan 2Z2                                                              EEEEEE       sSSSS  MM       MM     EEEEEE
|       EE         sS       MMMM   MMMM     EE                          laporte_n@esme.fr                           NOVEMBRE 2017                       EE         sS       MMMM   MMMM     EE
|       EEEEE       sSS     MM  MM   MM     EEEEEE                      https://github.com/Sysmetryx/               TD2 - PARTIE 3                       EEEEE       sSS     MM  MM   MM     EEEEEE
|       EE            Ss    MM       MM     EE                                                                      GUI                                 EE            Ss    MM       MM     EE
|       EEEEE    SSSSs      MM       MM     EEEEEE                                                                  IHM sous Qt                         EEEEE    SSSSs      MM       MM     EEEEEE
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QtextEdit>
#include <QMessageBox>
#include <QGridLayout>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QString>


#define BUTTON_NBR 10

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void OnClickedPushButton();
    void chiffrage();
    void dechiffrage();
    void OpenButton();
    void validator(int n);
    bool isvalid();
    void shuffle(int * tab, int taille);
    bool isNum(QString word);
    void Fopen();
    void Fsave();
    ~MainWindow();
private:
    QLabel *m_pLabel;
    QPushButton *m_pButton[BUTTON_NBR];
    QPushButton *m_pButtonC;
    QPushButton *m_pButtonD;
    QPushButton *m_pButtonO;
    QPushButton *m_pButtonS;
    QTextEdit *m_pTextEdit = new QTextEdit();
    int valid_n = 0;
    int tabButton[BUTTON_NBR];
    int const code[4] = {1, 9, 8, 1};
    bool val[4] = {false, false, false, false};
};

#endif // MAINWINDOW_H
