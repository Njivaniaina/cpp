#include "calculer.h"

Calculer::Calculer()
{

}

Calculer::~Calculer()
{

}

double Calculer::calcule_1(QString expression)
{
    double result = 0;
    std::vector<double> c;
    QStringList list = expression.split(QRegExp("-+*/"));
    QStringList list_operator = expression.split(QRegExp("1234567890."));

    for(int i=0;i<list.length();i++)
    {
        if(list_operator.at(i-1) == "-")
        {
            c.push_back(-list.at(i).toDouble());
        }
        else
        {
            c.push_back(-list.at(i).toDouble());
        }
    }

//    for(int i=0;i<list_operator.length();i++)
//    {
//        if((list_operator.at(i) == "*") || (list_operator.at(i) == "/"))
//        {
//            QString l = list.at(i);
//            QString l1 = list.at(i+1);
//            double r = 0;

//            if(list_operator.at(i) == "*")
//            {
//                r = l.toDouble()*l1.toDouble();
//            }
//            else
//            {
//                r = l.toDouble()/l1.toDouble();
//            }
//            for(int j=i+1;i<list.length();j++)
//            {
//                list.at(j)=list.at(j+1);
//            }
//            list.at(i)=QString::number(r);
//            list.removeLast();

//            list_operator.removeAt(i);
//            for(int j=i;i<list_operator.length();j++)
//            {
//                list_operator.at(j)=list_operator.at(j+1);
//            }
//            list_operator.removeLast();
//        }
//        i--;
//    }

//    result = list.at(0).toDouble();
//    for(int i=1;i<list.length();i++)
//    {
//        if(list_operator.at(i) == "-")
//        {
//            result = result-list.at(i).toDouble();
//        }
//        else
//        {
//            result = result+list.at(i).toDouble();
//        }
//    }

    return result;
}

double Calculer::calclue(QString expression)
{
    double resultat=0;

    return resultat;
}
