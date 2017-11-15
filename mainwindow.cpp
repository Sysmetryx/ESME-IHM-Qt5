/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|       EEEEEE       sSSSS  MM       MM     EEEEEE                      LAPORTE Nathan 2Z2                                                              EEEEEE       sSSSS  MM       MM     EEEEEE
|       EE         sS       MMMM   MMMM     EE                          laporte_n@esme.fr                           NOVEMBRE 2017                       EE         sS       MMMM   MMMM     EE
|       EEEEE       sSS     MM  MM   MM     EEEEEE                      https://github.com/Sysmetryx/               PARTIE 1                            EEEEE       sSS     MM  MM   MM     EEEEEE
|       EE            Ss    MM       MM     EE                                                                      GUI                                 EE            Ss    MM       MM     EE
|       EEEEE    SSSSs      MM       MM     EEEEEE                                                                  IHM sous Qt                         EEEEE    SSSSs      MM       MM     EEEEEE                                                                                                                                                                                                                              
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________
*/
#include "mainwindow.h"
#include <QMessageBox>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int i;
    QGridLayout *mainLayout = new QGridLayout;
    for(i = 0; i < BUTTON_NBR; i++)
    {
        m_pButton[i] = new QPushButton(QString::number(i), this);
        connect (m_pButton[i], &QPushButton::clicked, this, &MainWindow::OnClickedPushButton);

        if(i < 5)
        {
           mainLayout->addWidget(m_pButton[i], 1, i);
        }
        else
        {
           mainLayout->addWidget(m_pButton[i], 2, i-5);
        }

    }
    m_pButtonO = new QPushButton("Ouvrir !", this);
    connect (m_pButtonO, &QPushButton::clicked, this, &MainWindow::OpenButton);
    mainLayout->addWidget(m_pButtonO, 3, 0, 1, 5);
    this->setCentralWidget (new QWidget(this));
    this->centralWidget()->setLayout(mainLayout);
}

void MainWindow::OnClickedPushButton()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QMessageBox::about(this, "message", "You pushed the button " + clickedButton->text());
}

void MainWindow::OpenButton()
{
    QMessageBox::about(this, "message", "Vous avez essayé d'Ouvrir !");
}



MainWindow::~MainWindow()
{
    //QMessageBox::about(this, "Message", "Bye bye.");
}
