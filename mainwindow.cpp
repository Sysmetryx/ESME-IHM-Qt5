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
#include "mainwindow.h"

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
    m_pButtonC = new QPushButton("Chiffrer", this);
    mainLayout->addWidget(m_pButtonC, 13, 0, 1, 2);
    connect (m_pButtonC, &QPushButton::clicked, this, &MainWindow::chiffrage);
    m_pButtonD = new QPushButton("Déchiffrer", this);
    mainLayout->addWidget(m_pButtonD, 13, 3, 1, 2);
    connect (m_pButtonD, &QPushButton::clicked, this, &MainWindow::dechiffrage);
    m_pButtonD->setEnabled(false);
    m_pButtonD->setStyleSheet("background-color: red;");
    m_pButtonO = new QPushButton("Ouvrir", this);
    mainLayout->addWidget(m_pButtonO, 14, 0, 1, 2);
    connect(m_pButtonO, &QPushButton::clicked, this, &MainWindow::Fopen);
    m_pButtonS = new QPushButton("Sauvegarder", this);
    mainLayout->addWidget(m_pButtonS, 14, 3, 1, 2);
    connect(m_pButtonS, &QPushButton::clicked, this, &MainWindow::Fsave);
    this->setCentralWidget (new QWidget(this));
    this->centralWidget()->setLayout(mainLayout);
}

void MainWindow::OnClickedPushButton()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
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

void MainWindow::chiffrage()
{
    QString strIn = m_pTextEdit->toPlainText(), strOut = "";
    QByteArray strBA = strIn.toLatin1();
    int ascii = 0;
    for(int i = 0; i < strIn.length(); i++)
    {
        ascii = (int)strBA.at(i);
        if(ascii < 100)
        {
            strOut.append(QString::number(ascii));
            strOut.append(" ");
        }
        else
        {
            strOut += strBA.at(i);
            strOut.append(" ");
        }
    }
    m_pTextEdit->setPlainText(strOut);
}

void MainWindow::dechiffrage()
{
    QString strIn = m_pTextEdit->toPlainText(), word = "", strOut;
    QChar c;
    int ascii =  0;
    bool ok = false;
    for(int i = 0; i < strIn.length(); i++)
    {
        while(strIn[i] != ' ' && i < strIn.length())
        {
            word += strIn[i];
            i++;
        }
        if(isNum(word))
        {
            ok = false;
            ascii = word.toInt(&ok, 10);
            c = *(new QChar(ascii));
            strOut += c;
        }
        else
        {
            strOut.append(word);
        }
        word = "";
    }
    m_pTextEdit->setPlainText(strOut);
    m_pButtonD->setStyleSheet("background-color: red;");
    m_pButtonD->setEnabled(false);
    for(int i = 0; i < 4; i++)
    {
        val[i] = false;
    }

}

bool MainWindow::isNum(QString word)
{
    bool rvalue = true;
    for(int i = 0; i < word.length(); i++)
    {
        if(word.at(i) < 48 || word.at(i) > 57)
            rvalue = false;
    }
    return rvalue;
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

void MainWindow::Fopen()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir", "", "Texte chiffre (*.ch);; Texte dechiffre (*.dech)");
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream (&file);
    m_pTextEdit->setText(stream.readAll());
}

void MainWindow::Fsave()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarde", "", "Texte chiffre (*.ch);; Texte dechiffre (*.dech)");
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        close();
    }
    else
    {
        QTextStream stream(&file);
        stream << m_pTextEdit->toPlainText() << endl;
        file.close();
    }
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
