/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|       EEEEEE       sSSSS  MM       MM     EEEEEE                      LAPORTE Nathan 2Z2                                                              EEEEEE       sSSSS  MM       MM     EEEEEE
|       EE         sS       MMMM   MMMM     EE                          laporte_n@esme.fr                           NOVEMBRE 2017                       EE         sS       MMMM   MMMM     EE
|       EEEEE       sSS     MM  MM   MM     EEEEEE                      https://github.com/Sysmetryx/               PARTIE 4                            EEEEE       sSS     MM  MM   MM     EEEEEE
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
        tabButton[i] = i;
    }
    shuffle(tabButton, BUTTON_NBR);
    for(i = 0; i < BUTTON_NBR; i++)
    {
        m_pButton[i] = new QPushButton(QString::number(tabButton[i]), this);
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
    m_pButtonO->setEnabled(false);
    m_pButtonO->setStyleSheet("background-color: red;");
    connect (m_pButtonO, &QPushButton::clicked, this, &MainWindow::OnClickedPushButton);
    mainLayout->addWidget(m_pButtonO, 3, 0, 1, 5);
    this->setCentralWidget (new QWidget(this));
    this->centralWidget()->setLayout(mainLayout);
}

void MainWindow::OnClickedPushButton()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if(clickedButton->text() != "Ouvrir !")
    {
        bool ok = false;
        int nombre = clickedButton->text().toInt(&ok, 10);
        validator(nombre);
        if(isvalid()){
            m_pButtonO->setStyleSheet("background-color: green;");
            m_pButtonO->setEnabled(true);}
        if (!isvalid()){
            m_pButtonO->setStyleSheet("background-color: red;");
            m_pButtonO->setEnabled(false);}

    }
    else
    {
        if(isvalid())
        {
            QMessageBox::about(this, "Message", "Code juste");
            close();
        }
        else
            QMessageBox::about(this, "Message", "Code faux!");
    }
}

bool MainWindow::isvalid()
{
    int i;
    bool juste = true;
    for(i = 0; i < 4; i++)
    {
        if(val[i] == false)
            juste = false;
    }
    return juste;
}

void MainWindow::validator(int n)
{
    if(n == code[valid_n])
    {
        val[valid_n] = true;
        valid_n++;
    }
    else
    {
        for(int i = 0; i < 4;i++)
        {
            val[i] = false;
        }
        valid_n = 0;
    }
}

void MainWindow::OpenButton()
{

}



MainWindow::~MainWindow()
{

}

void MainWindow::shuffle(int * tab, int taille)
{
    srand(time(NULL));
    int i, temp, indice;
    for (i = 0; i < taille; ++i)
    {
        indice = (int) rand()%taille;
        temp = tab[i];
        tab[i] = tab[indice];
        tab[indice] = temp;
    }
}
