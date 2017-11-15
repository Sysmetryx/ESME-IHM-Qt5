/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|       EEEEEE       sSSSS  MM       MM     EEEEEE                      LAPORTE Nathan 2Z2                                                              EEEEEE       sSSSS  MM       MM     EEEEEE
|       EE         sS       MMMM   MMMM     EE                          laporte_n@esme.fr                           NOVEMBRE 2017                       EE         sS       MMMM   MMMM     EE
|       EEEEE       sSS     MM  MM   MM     EEEEEE                      https://github.com/Sysmetryx/               TD2 - PARTIE 1                       EEEEE       sSS     MM  MM   MM     EEEEEE
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
    mainLayout->addWidget(m_pTextEdit, 1, 0, 10, 5 );
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
           mainLayout->addWidget(m_pButton[i], 11, i);
        }
        else
        {
           mainLayout->addWidget(m_pButton[i], 12, i-5);
        }

    }
    //m_pButtonO = new QPushButton("Ouvrir !", this);
    //m_pButtonO->setEnabled(false);
    //m_pButtonO->setStyleSheet("background-color: red;");
    //connect (m_pButtonO, &QPushButton::clicked, this, &MainWindow::OnClickedPushButton);
    //mainLayout->addWidget(m_pButtonO, 13, 0, 1, 5);
    m_pButtonC = new QPushButton("Chiffrer", this);
    mainLayout->addWidget(m_pButtonC, 13, 0, 1, 2);
    connect (m_pButtonC, &QPushButton::clicked, this, &MainWindow::chiffrage);
    m_pButtonD = new QPushButton("Déchiffrer", this);
    connect (m_pButtonD, &QPushButton::clicked, this, &MainWindow::dechiffrage);
    m_pButtonD->setEnabled(false);
    m_pButtonD->setStyleSheet("background-color: red;");
    mainLayout->addWidget(m_pButtonD, 13, 3, 1, 2);
    this->setCentralWidget (new QWidget(this));
    this->centralWidget()->setLayout(mainLayout);
}

void MainWindow::OnClickedPushButton()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if(clickedButton->text() != "Chiffrer")
    {
        bool ok = false;
        int nombre = clickedButton->text().toInt(&ok, 10);
        validator(nombre);
        if(isvalid()){
            m_pButtonD->setStyleSheet("background-color: green;");
            m_pButtonD->setEnabled(true);}
        if (!isvalid()){
            m_pButtonD->setStyleSheet("background-color: red;");
            m_pButtonD->setEnabled(false);}

    }
    else
    {
        if(isvalid())
        {
            QMessageBox::about(this, "Message", "Code juste");

        }
    }
}

void MainWindow::chiffrage()
{
    QString str;
    str = m_pTextEdit->toPlainText();
    str = str.toUpper();
    m_pTextEdit->setPlainText(str);
}

void MainWindow::dechiffrage()
{
    QString str;
    str = m_pTextEdit->toPlainText();
    str = str.toLower();
    m_pTextEdit->setPlainText(str);
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
