#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"0");
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"1");
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"2");
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"3");
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"4");
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"5");
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"6");
}


void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"7");
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"8");
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"9");
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+".");
}


void MainWindow::on_pushButton_17_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"-");
}


void MainWindow::on_pushButton_16_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"+");
}


void MainWindow::on_pushButton_18_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"/");
}


void MainWindow::on_pushButton_15_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"*");
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->lineEdit->setText("");
}


void MainWindow::on_pushButton_13_clicked()
{
    QString text = ui->lineEdit->text();
    text.remove(text.length()-1, text.length());
    ui->lineEdit->setText(text);
}

/******************************************
 **************Bouton égale****************
 *****************************************/

//Des entête util dans le calcule
void affiche(std::vector<QString> s);
bool There_are_parenthese(QString expression);
QString calcule2(QString expression);
QString calcule1(QString expression);


//Calcule en générale
QString calcule(QString expression)
{
    if(expression.length() == 0)
    {
        return "0";
    }
    else
    {
        if(There_are_parenthese(expression))
        {
            //std::cout << "calcule 1 lancer" << std::endl;
            return calcule1(expression);
        }
        else
        {
            //std::cout << "calcule 2 lancer" << std::endl;
            return calcule2(expression);
        }
    }
}

//affichage d'une vector qui contient des éléments QString
void affiche(std::vector<QString> s)
{
    for(int i=0;i<s.size();i++)
    {
        std::cout << s[i].toStdString() << std::endl;
    }
    std::cout << std::endl;
}

//Verification si il y a des parentheses
bool There_are_parenthese(QString expression)
{
    bool verifie=false;
    for(int i=0;i<expression.length();i++)
    {
        if(expression.at(i) == '(')
        {
            verifie = true;
        }
    }
    return verifie;
}

//Calcule des simples entiers (pas de parenthèse)
QString calcule2(QString expression)
{
    int n=0;
    int retour=1;
    std::vector<QString> list;
    list.push_back("");

    //Pour séparer les éléments dans le chaine
    for(int i=0;i<expression.length();i++)
    {
        if(i==0 || expression[i].isDigit() || (!expression[i].isDigit() && expression[i] == '.'))
        {
            list.at(n) += QChar(expression[i]);
        }
        else
        {
            n++;
            list.push_back("");
            list[n] += QChar(expression[i]);
        }
    }

    //Boucle pour les signe * et /
    while(retour)
    {
        for(int i=1;i<list.size();i++)
        {
            if(list[i].at(0) == '*' || list[i].at(0) == '/')
            {
                QString tmp = list[i];
                tmp.remove(0, 1);
                if(list[i].at(0) == '*')
                {
                    QChar c = list[i-1].at(0);
                    if(!c.isDigit())
                    {
                        QString tmp1 = list[i-1];
                        tmp1.remove(0, 1);
                        double r = tmp1.toDouble()*tmp.toDouble();
                        list[i-1] = QString::number(r);
                        list[i-1].insert(0, c);
                    }
                    else
                    {
                        double r = list[i-1].toDouble()*tmp.toDouble();
                        list[i-1] = QString::number(r);
                    }
                }
                else
                {
                    QChar c = list[i-1].at(0);
                    if(!c.isDigit())
                    {
                        QString tmp1 = list[i-1];
                        tmp1.remove(0, 1);
                        double r = tmp1.toDouble()/tmp.toDouble();
                        list[i-1] = QString::number(r);
                        list[i-1].insert(0, c);
                    }
                    else
                    {
                        double r = list[i-1].toDouble()/tmp.toDouble();
                        list[i-1] = QString::number(r);
                    }
                }
                list.erase(list.begin()+i);
                i--;
            }
        }
        if(list.size()>1)
        {
            int m=0;
            for(QString s : list)
            {
                if(s.at(0) == '*' || s.at(0) == '/')
                {
                    m=1;
                }
            }
            if(!m)
            {
                retour=0;
            }
        }
        else
        {
            retour=0;
        }
    }

    //Boucle pour les signe + et -
    while(list.size()>1)
    {
        for(int i=1;i<list.size();i++)
        {
            if(list[i].at(0) == '+' || list[i].at(0) == '-')
            {
                QString tmp = list[i];
                tmp.remove(0, 1);
                if(list[i].at(0) == '+')
                {
                    double r = list[i-1].toDouble() + tmp.toDouble();
                    list[i-1] = QString::number(r);
                }
                else
                {
                    double r = list[i-1].toDouble() - tmp.toDouble();
                    list[i-1] = QString::number(r);
                }
                list.erase(list.begin()+i);
                i--;
            }
        }
    }

    return list[0];
}

//Calcule avec des parentheses
QString calcule1(QString expression)
{
    std::vector<QString> list;
    int n=0;
    int p=0;
    list.push_back("");
    QString result="";

    for(int i=0;i<expression.length();i++)
    {
        if(expression.at(i) == '(')
        {
            p++;
        }
        if(expression.at(i) == ')')
        {
            p--;
        }

        if(!p && expression.at(i) != ')')
        {
            if(i==0 || expression[i].isDigit() || (!expression[i].isDigit() && expression[i] == '.'))
            {
                list.at(n) += QChar(expression[i]);
            }
            else
            {
                n++;
                list.push_back("");
                list[n] += QChar(expression[i]);
            }
        }
        if(p || expression.at(i) == ')')
        {
            list[n] += QChar(expression[i]);
        }
    }

//    affiche(list);

    for(int i=0;i<list.size();i++)
    {
        QString tmp = list[i];
        QChar c;

        if(!tmp.at(0).isDigit())
        {
            if(tmp.at(0) == '-' || tmp.at(0) == '+' || tmp.at(0) == '/' || tmp.at(0) == '*')
            {

                c = tmp.at(0);
                tmp.remove(0, 1);
                if(tmp.at(0) == '(')
                {
                    tmp.remove(0, 1);
                    tmp.remove(tmp.length()-1, 1);
                }
            }
            if(tmp.at(0) == '(')
            {
                tmp.remove(0, 1);
                tmp.remove(tmp.length()-1, 1);
            }
        }
        list[i]=c+calcule(tmp);
    }

//    affiche(list);

    for(int i=0;i<list.size();i++)
    {
        result += list[i];
    }

//    std::cout << "Le result est " << result.toStdString() << std::endl;
//    for(QChar c : result)
//    {
//        std::cout << c.toLatin1() << std::endl;
//    }

    result.remove(0, 1);
    //std::cout << calcule(result).toStdString() << std::endl;

    return calcule(result);
}

//Vérification de la texte
bool isValide(QString expression)
{
    int n=0;

    if(expression != "")
    {
        if(expression.at(expression.length()-1) == '+' || expression.at(expression.length()-1) == '-' ||expression.at(expression.length()-1) == '*' ||expression.at(expression.length()-1) == '/' )
        {
            return false;
        }
        for(int i=0;i<expression.length();i++)
        {
            if(expression.at(i) == '(')
            {
                n++;
            }
            if(expression.at(i) == ')')
            {
                n--;
            }
            if(n<0)
            {
                return false;
            }
            if((expression.at(i) == '+' || expression.at(i) == '-' ||expression.at(i) == '*' || expression.at(i) == '/') && (expression.at(i+1) == '+' || expression.at(i+1) == '-' ||expression.at(i+1) == '*' || expression.at(i+1) == '/'))
            {
                return false;
            }
            if((expression.at(i) == '(') && (i != 0) && (expression.at(i-1) != '+' && expression.at(i-1) != '-' && expression.at(i-1) != '*' && expression.at(i-1) != '/'))
            {
                return false;
            }
        }
        if(n)
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

void MainWindow::on_pushButton_14_clicked()
{
    QString texte = ui->lineEdit->text();

    if(isValide(texte))
    {
        ui->lineEdit_2->setText(calcule(texte));
        ui->label->setText("");
    }
    else
    {
        ui->label->setText("Syntax Error");
        ui->lineEdit_2->setText("0");
    }

}

/******************************************
 *********Fin de la bouton égal************
 ******************************************/

void MainWindow::on_pushButton_20_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"(");
}


void MainWindow::on_pushButton_19_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+")");
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString texte = ui->lineEdit->text();

    if(isValide(texte))
    {
        ui->lineEdit_2->setText(calcule(texte));
        ui->label->setText("");
    }
    else
    {
        ui->lineEdit_2->setText("");
    }
}

