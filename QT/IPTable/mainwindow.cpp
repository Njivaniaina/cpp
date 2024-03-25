#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include <QProcess>
#include <QGroupBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QInputDialog>
#include <QGridLayout>
#include <QScrollArea>
#include <QtDebug>
#include <QMessageBox>
#include <QtWidgets>

bool no_running = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->table_information = new QTabWidget();
    ui->principal->addWidget(this->table_information);

    ui->page->setCurrentIndex(0);

    if(MainWindow::ask_passwd())
        MainWindow::print_information();
    else
        exit(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hide_all()
{
    ui->source->setVisible(false);
    ui->destination->setVisible(false);
    ui->choise_protocole->setVisible(false);
    ui->ports->setVisible(false);
    ui->choise_ports->setVisible(false);
    ui->check_ports_precision->setVisible(false);
    ui->mac->setVisible(false);
    ui->choise_interface_output->setVisible(false);
    ui->choise_interface_input->setVisible(false);

    ui->source_2->setVisible(false);
    ui->destination_2->setVisible(false);
    ui->choise_protocole_2->setVisible(false);
    ui->ports_2->setVisible(false);
    ui->choise_ports_2->setVisible(false);
    ui->check_ports_precision_2->setVisible(false);
    ui->mac_2->setVisible(false);
    ui->choise_interface_output_2->setVisible(false);
    ui->choise_interface_input_2->setVisible(false);

    ui->ports->setText("");
    ui->mac->setText("");
    ui->source->setText("");
    ui->destination->setText("");

    ui->ports_2->setText("");
    ui->mac_2->setText("");
    ui->source_2->setText("");
    ui->destination_2->setText("");

    ui->check_interface_input->setChecked(false);
    ui->check_interface_output->setChecked(false);
    ui->check_source->setChecked(false);
    ui->check_destination->setChecked(false);
    ui->check_mac->setChecked(false);
    ui->check_protocole->setChecked(false);
    ui->check_ports->setChecked(false);
    ui->check_ports_precision->setChecked(false);

    ui->check_interface_input_2->setChecked(false);
    ui->check_interface_output_2->setChecked(false);
    ui->check_source_2->setChecked(false);
    ui->check_destination_2->setChecked(false);
    ui->check_mac_2->setChecked(false);
    ui->check_protocole_2->setChecked(false);
    ui->check_ports_2->setChecked(false);
    ui->check_ports_precision_2->setChecked(false);
}

bool MainWindow::ask_passwd()
{
    QString passwd = QInputDialog::getText(this, "Authentification", "\n\tPour utiliser cette application;\t\n\tentrer votre mot de passe :\t\n", QLineEdit::Password);

    if(passwd != "")
    {
        QStringList arguments;
        QString error;
        std::string errorSTD;
        QProcess *process = new QProcess();

        arguments << "-S";
        arguments << "-v";

        process->start("sudo", arguments);
        process->write(passwd.toUtf8()+"\n");
        process->closeWriteChannel();

        error = process->readAllStandardError();
        std::cout << "OUTPUT : " << process->readAllStandardOutput().toStdString() << std::endl;
        errorSTD = error.toStdString();
        std::cout << "L'error : " << errorSTD << std::endl;

        if(!process->waitForStarted())
        {
            std::cout << "Impossible de démarre le processus!" << std::endl;
        }
        if(!process->waitForFinished())
        {
            std::cout << "Impossible d'arrêter le processus!" << std::endl;
            return false;
        }

        if(error != "")
        {
            QMessageBox msg;
            msg.setIcon(QMessageBox::Critical);
            if((error.toStdString().find("incorrect password") != std::string::npos) || (error.toStdString().find("essayez de nouveau") != std::string::npos))
            {
                msg.setText("Mot de passe incorrect\nL'application IPTables s'est arrêter!!!\n");
                msg.exec();
                return false;
            }
            else if(error.toStdString().find("sudoers") != std::string::npos)
            {
                msg.setText("L'utilisateur actuelle n'est pas dans le sudoers et ne peut pas utiliser cette application!\nL'application IPTables s'est arrêter!!!\n");
                msg.exec();
                return false;
            }
            else if(error.toStdString().find("[sudo] Mot de passe de njiva : ") == std::string::npos){}
        }

        if(!process->exitCode() || error == "[sudo] Mot de passe de njiva : " )
        {
            return true;
        }
        else
        {
            QMessageBox msg;
            msg.setIcon(QMessageBox::Critical);
            msg.setText("Erreur inatendue!!!!\nIPTables s'est arrêter!!!\n");
            msg.exec();
            return false;
        }
    }
    return false;
}

void MainWindow::getData(std::vector<std::string> *chaine, std::vector<std::vector<std::vector<std::string>>> *rules, std::vector<std::string> *police)
{
    std::ifstream file("./../IPTable/data/iptables.txt");
    std::string text;
    std::vector<std::vector<std::string>> one_rules_tmp;

    if(file.is_open())
    {
        while(std::getline(file, text))
        {
            if(text.find("Chain") != std::string::npos)
            {
                std::stringstream flux_tmp(text);
                std::string text_tmp;

                flux_tmp >> text_tmp >> text_tmp;
                chaine->push_back(text_tmp);
                flux_tmp >> text_tmp >> text_tmp;
                text_tmp.pop_back();
                police->push_back(text_tmp);
                one_rules_tmp.clear();
            }
            else if(text.find("target") != std::string::npos);
            else if(text == "")
            {
                rules->push_back(one_rules_tmp);
            }
            else
            {
                std::stringstream flux_tmp(text);
                std::vector<std::string> container_tmp;
                std::string text_tmp;

                flux_tmp >> text_tmp;
                container_tmp.push_back(text_tmp);
                flux_tmp >> text_tmp;
                container_tmp.push_back(text_tmp);
                flux_tmp >> text_tmp;
                container_tmp.push_back(text_tmp);
                flux_tmp >> text_tmp;
                container_tmp.push_back(text_tmp);
                flux_tmp >> text_tmp;
                container_tmp.push_back(text_tmp);
                std::getline(flux_tmp, text_tmp, '\n');
                size_t positon_caracter = text_tmp.find_first_not_of(" ");
                if(positon_caracter != std::string::npos)
                    text_tmp = text_tmp.substr(positon_caracter);
                container_tmp.push_back(text_tmp);

                one_rules_tmp.push_back(container_tmp);
            }
        }
        rules->push_back(one_rules_tmp);

        file.close();
    }
    else
    {
        std::cout << "Erreur lors de l'ouverture du fichier iptables.txt " << std::endl;
    }
}

bool MainWindow::exec_cmd(QString command, QString *result_cmd)
{
    QProcess *process = new QProcess();
    QString error;
    QByteArray result;

    process->start(command);
    if(!process->waitForFinished())
    {
        std::cout << "Impossible d'éxecuter la command " << command.toStdString() << " !!!" << std::endl;
    }
    result = process->readAllStandardOutput();
    if(result!="")
    {
        *result_cmd = result.constData();
    }

    error = process->readAllStandardError();
    if(error != "")
    {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Critical);
        std::cout << "L'erreur du command " << command.toStdString() << " : " << error.toStdString() << std::endl;
        msg.setText(error);
        msg.exec();
    }

    if(process->exitCode())
    {
        return true;
    }
    return false;
}

void MainWindow::print_css()
{
    ui->actualiser->setIcon(QIcon("../IPTable/icons/actualiser.svg"));
    ui->save->setIcon(QIcon("../IPTable/icons/save.svg"));
    ui->reinitialisation->setIcon(QIcon("../IPTable/icons/reinitialiser.svg"));
    ui->ajout->setIcon(QIcon("../IPTable/icons/add.svg"));
    ui->button_add->setIcon(QIcon("../IPTable/icons/valider.svg"));
    ui->annuler->setIcon(QIcon("../IPTable/icons/annuler.svg"));
}

void MainWindow::get_command_rules(std::vector<std::vector<std::vector<std::string>>> *rules)
{
    std::ifstream rules_file("./../IPTable/data/rules.txt");
//    std::vector<std::vector<std::vector<std::string>>> rules;
    std::vector<std::vector<std::string>>  chaine;
    int m=1;

    if(rules_file.is_open())
    {
        std::vector<std::string> rule;
        std::string text;
        std::vector<std::vector<std::string>> one_rules;

        while(std::getline(rules_file, text))
        {
            std::stringstream flux(text);
            std::string text_tmp;


            while (flux >> text_tmp)
            {
                rule.push_back(text_tmp);
            }

            if(rule.size() < 4)
            {
                chaine.push_back(rule);
            }
            else
            {
                if(m)
                {
                    for(size_t i=0;i<chaine.size();i++)
                    {
                        std::vector<std::vector<std::string>> r;
                        rules->push_back(r);
                    }
                    m=0;
                }

                for(size_t i=0;i<chaine.size();i++)
                {
                    if(rule.at(1) == chaine.at(i).at(1))
                    {
                        rules->at(i).push_back(rule);
                    }
                }
            }

            rule.clear();
        }

        rules_file.close();
    }
    else
    {
        std::cout << "Erreur de l'ouverture du fichier input.txt!!!" << std::endl;
    }
}

void MainWindow::print_information()
{
    std::vector<std::string> chaine;
    std::vector<std::vector<std::vector<std::string>>> rules;
    std::vector<std::string> interface;
    std::vector<std::string> police_active;
    std::vector<std::vector<std::vector<std::string>>> command_rules;

    while(this->table_information->count() > 0)
    {
        this->table_information->removeTab(0);
    }
    
// Execution du commande iptables -L pour le list
    QString cmd = QString("sudo iptables -L");
    QString result  = QString();
    QString result1 = QString();
    MainWindow::exec_cmd(cmd, &result);
    MainWindow::exec_cmd("rm ./../IPTable/data/iptables.txt", nullptr);

// Placer le resultat dans le fichier iptables.txt¨
    std::ofstream file("./../IPTable/data/iptables.txt");
    if(file.is_open())
    {
        file << result.toStdString();
        file.close();
    }
    else
    {
        std::cout << "Erreur de l'ouverture de ./../IPTable/data/iptables.txt !!" << std::endl;
    }

    MainWindow::exec_cmd("sudo iptables --list-rules", &result1);
    std::ofstream file1("./../IPTable/data/rules.txt");
    if(file1.is_open())
    {
        file1 << result1.toStdString();
        file1.close();
    }
    else
    {
        std::cout << "Erreur de l'ouverture de ./../IPTable/data/rules.txt !!" << std::endl;
    }


// Affiche les css
    MainWindow::print_css();

// Avoir les données utiles
    MainWindow::getData(&chaine, &rules, &police_active);
    MainWindow::get_command_rules(&command_rules);

    for(size_t i=0;i<chaine.size();i++)
    {     
        QScrollArea *scroll_information = new QScrollArea;
        QWidget *widget_information = new QWidget;

        QGridLayout *container_rules = new QGridLayout();
        QLabel *target = new QLabel("TARGET");
        QLabel *protocole = new QLabel("PROTOCOLE");
        QLabel *opt = new QLabel("OPTION");
        QLabel *source = new QLabel("SOURCE");
        QLabel *destination = new QLabel("DESTIONATION");
        QLabel *description = new QLabel("DESCRIPTION");
        QLabel *modify = new QLabel("MODIFICATION");
        QLabel *del = new QLabel("SUPPRESSION");

        QVBoxLayout *list = new QVBoxLayout();
        QHBoxLayout *police = new QHBoxLayout();
        QLabel *c = new QLabel("Police du chaine "+QString::fromStdString(chaine.at(i)));
        QComboBox *p = new QComboBox();
        QWidget *widget = new QWidget();

        target->setFixedWidth(200);
        protocole->setFixedWidth(100);
        opt->setFixedWidth(100);
        source->setFixedWidth(200);
        destination->setFixedWidth(200);
        description->setFixedWidth(200);

        container_rules->addWidget(target, 0, 0);
        container_rules->addWidget(protocole, 0, 1);
        container_rules->addWidget(opt, 0, 2);
        container_rules->addWidget(source, 0, 3);
        container_rules->addWidget(destination, 0, 4);
        container_rules->addWidget(description, 0, 5);
        container_rules->addWidget(modify, 0, 6);
        container_rules->addWidget(del, 0, 7);

        for(size_t j=0;j<rules.at(i).size();j++)
        {
            QLabel *target1 = new QLabel(QString::fromStdString(rules.at(i).at(j).at(0)));
            QLabel *protocole1 = new QLabel(QString::fromStdString(rules.at(i).at(j).at(1)));
            QLabel *opt1 = new QLabel(QString::fromStdString(rules.at(i).at(j).at(2)));
            QLabel *source1 = new QLabel(QString::fromStdString(rules.at(i).at(j).at(3)));
            QLabel *destination1 = new QLabel(QString::fromStdString(rules.at(i).at(j).at(4)));
            QLabel *description1 = new QLabel(QString::fromStdString(rules.at(i).at(j).at(5)));
            QPushButton *del1 = new QPushButton("Supprimer");
            del1->setIcon(QIcon("./../IPTable/icons/delete.svg"));
            del1->setStyleSheet(""
                                "border-radius: 5px;"
                                "color: black;"
                                "background: rgb(212, 212, 212);"
                                "");
            QPushButton *modify1 = new QPushButton("Modifier");
            modify1->setIcon(QIcon("../IPTable/icons/modify.svg"));
            modify1->setStyleSheet(""
                                "border-radius: 5px;"
                                "color: black;"
                                "background: rgb(212, 212, 212);"
                                "");


            source1->setWordWrap(true);
            destination1->setWordWrap(true);
            description1->setWordWrap(true);

            QString ch = QString(QString::fromStdString(chaine.at(i)));
            QObject::connect(del1, &QPushButton::clicked ,this ,[this, ch, i, j]()
            {
                QString c = "sudo iptables -D ";
                QString t = QString::number(j+1);
                c += ch;
                c += " ";
                c += t;

                this->exec_cmd(c, nullptr);
                this->print_information();
            });

//            if(command_rules.at(i).size() > 0)
//                std::cout << "La longueur de la vecteur est :" << command_rules.at(i).size() << std::endl ;

            QObject::connect( modify1, &QPushButton::clicked, this, [=]()
            {
                ui->page->setCurrentIndex(2);
                std::vector<std::string> interface;
                std::cout << "rules = command_rules (correspondant) " << std::endl;
                std::vector<std::string> rule(command_rules.at(i).at(j));

                interface = MainWindow::getInterface();
                ui->choise_interface_input_2->clear();
                ui->choise_interface_output_2->clear();
                for(size_t t=0;t<interface.size();t++)
                {
                    ui->choise_interface_output_2->addItem(QString::fromStdString(interface.at(t)));
                }
                for(size_t t=0;t<interface.size();t++)
                {
                    ui->choise_interface_input_2->addItem(QString::fromStdString(interface.at(t)));
                }

                ui->chaine->setText(QString::fromStdString(chaine.at(i)));
                //std::cout << "La longueur de la vecteur est :" << command_rules.at(i).at(j+1).size() << std::endl ;
                for(size_t l=0;l<rule.size();l++)
                {
                    if(rule.at(l) == "-j")
                    {
                        if(rule.at(l+1) != "INPUT" && rule.at(l+1) != "OUTPUT" && rule.at(l+1) != "FORWARD")
                        {
                            //ui->choise_target_2->addItem(chaine.at(i));
                            ui->choise_target_2->setCurrentText(QString::fromStdString(rule.at(l+1)));
                        }
                    }
                    else if(rule.at(l) == "-i")
                    {
                        ui->check_interface_input_2->setChecked(true);
                        ui->choise_interface_input_2->setVisible(true);
                        ui->choise_interface_input_2->setCurrentText(QString::fromStdString(rule.at(l+1)));
                    }
                    else if(rule.at(l) == "-o")
                    {
                        ui->check_interface_output_2->setChecked(true);
                        ui->choise_interface_output_2->setVisible(true);
                        ui->choise_interface_output_2->setCurrentText(QString::fromStdString(rule.at(l+1)));
                    }
                    else if(rule.at(l) == "-s")
                    {
                        ui->check_source_2->setChecked(true);
                        ui->source_2->setVisible(true);
                        ui->source_2->setText(QString::fromStdString(rule.at(l+1)));
                    }
                    else if(rule.at(l) == "-d")
                    {
                        ui->check_destination_2->setChecked(true);
                        ui->destination_2->setVisible(true);
                        ui->destination_2->setText(QString::fromStdString(rule.at(l+1)));
                    }
                    else if(rule.at(l) == "mac")
                    {
                        ui->check_mac_2->setChecked(true);
                        ui->mac_2->setVisible(true);
                        ui->mac_2->setText(QString::fromStdString(rule.at(l+1)));
                    }
                    else if(rule.at(l) == "-p")
                    {
                        std::cout << "Le protocole est :" << rule.at(l+1) << std::endl;
                        ui->check_protocole_2->setChecked(true);
                        ui->choise_protocole_2->setVisible(true);
                        ui->choise_protocole_2->setCurrentText(QString::fromStdString(rule.at(l+1)));
                    }
                    else if(rule.at(l) == "multiport")
                    {
                        if(rule.at(l+1) == "--sports")
                        {
                            ui->check_ports_2->setChecked(true);
                            ui->ports_2->setVisible(true);
                            ui->ports_2->setText(QString::fromStdString(rule.at(l+2)));
                            ui->check_ports_precision_2->setChecked(true);
                            ui->choise_ports_2->setCurrentIndex(0);
                        }
                        else if(rule.at(l+1) == "--dports")
                        {
                            ui->check_ports_2->setChecked(true);
                            ui->ports_2->setVisible(true);
                            ui->ports_2->setText(QString::fromStdString(rule.at(l+2)));
                            ui->check_ports_precision_2->setChecked(true);
                            ui->choise_ports_2->setCurrentIndex(1);
                        }
                        else
                        {
                            ui->check_ports_2->setChecked(true);
                            ui->ports_2->setVisible(true);
                            ui->ports_2->setText(QString::fromStdString(rule.at(l+2)));
                            ui->check_ports_precision_2->setChecked(false);
                        }
                    }
                }

                QObject::connect(ui->modify, &QPushButton::clicked, this, [=]()
                {
                    MainWindow::modify_clicked(j+1, chaine.at(i));
                });
            });

            target1->setFixedWidth(200);
            protocole1->setFixedWidth(100);
            opt1->setFixedWidth(100);
            source1->setFixedWidth(200);
            destination1->setFixedWidth(200);
            description1->setFixedWidth(200);

            container_rules->addWidget(target1, j+1, 0);
            container_rules->addWidget(protocole1, j+1, 1);
            container_rules->addWidget(opt1, j+1, 2);
            container_rules->addWidget(source1, j+1, 3);
            container_rules->addWidget(destination1, j+1, 4);
            container_rules->addWidget(description1, j+1, 5);
            container_rules->addWidget(modify1, j+1, 6);
            container_rules->addWidget(del1 , j+1, 7);
        }

        widget_information->setLayout(container_rules);
        scroll_information->setWidget(widget_information);
        list->addWidget(scroll_information);

        if(police_active.at(i) == "ACCEPT"  || police_active.at(i) == "DROP" || police_active.at(i) == "REJECT" )
        {
            p->addItem("ACCEPT");
            p->addItem("DROP");
            p->addItem("REJECT");
            p->setCurrentText(QString::fromStdString(police_active.at(i)));
        }
        else
        {
            p->addItem("UNKNOWN");
        }

        QObject::connect(p, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int){
            QString command = "sudo iptables -P "+QString::fromStdString(chaine.at(i));
            QString text = p->currentText();
            QMessageBox msg;
            QString information = "Voulez-vous changer varaiment la police  de "+QString::fromStdString(chaine.at(i))+ " en "+text+ " ?";

            command += " "+text;

            msg.setText("Changement de la police.");
            msg.setInformativeText(information);
            msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msg.setWindowTitle("Changement de police");
            msg.setIcon(QMessageBox::Warning);

            int n = msg.exec();

            if(n == QMessageBox::Ok)
            {
                this->exec_cmd(command, nullptr);
                this->print_information();
            }
            else
            {
                this->print_information();
            }
        });

        police->addWidget(c);
        police->addWidget(p);
        list->addLayout(police);

        widget->setLayout(list);
        this->table_information->addTab(widget , QString::fromStdString(chaine.at(i)));
        MainWindow::hide_all();
    }

    interface = MainWindow::getInterface();
    ui->choise_interface_input->clear();
    ui->choise_interface_output->clear();
    for(size_t i=0;i<interface.size();i++)
    {
        ui->choise_interface_output->addItem(QString::fromStdString(interface.at(i)));
    }
    for(size_t i=0;i<interface.size();i++)
    {
        ui->choise_interface_input->addItem(QString::fromStdString(interface.at(i)));
    }
}

std::vector<std::string> MainWindow::getInterface()
{
    std::vector<std::string> interface;
    std::string text_tmp;
    system("ip a > ./interface.txt");
    std::ifstream file("./interface.txt");

    if(file.is_open())
    {
        while(std::getline(file, text_tmp))
        {
            if((text_tmp.find("UP") != std::string::npos) || (text_tmp.find("UNKNOWN") != std::string::npos))
            {
                std::stringstream flux_text(text_tmp);
                std::string text;
                flux_text >> text >> text;
                text = text.substr(0, text.size()-1);
                interface.push_back(text);
            }
        }
        file.close();
        system("rm ./interface.txt");
    }
    else
    {
        std::cout << "Erreur lors de l'ouverture du fichier!" << std::endl;
    }
    return interface;
}

void MainWindow::on_actualiser_clicked()
{
    MainWindow::print_information();
}

// Check 1
void MainWindow::on_check_protocole_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->choise_protocole->setVisible(false);
        ui->check_protocole->setText("Désactiver");
    }
    else
    {
        ui->choise_protocole->setVisible(true);
        ui->check_protocole->setText("Activer");
    }
}

void MainWindow::on_check_source_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->source->setVisible(false);
        ui->check_source->setText("Désactiver");
    }
    else
    {
        ui->source->setVisible(true);
        ui->check_source->setText("Activer");
    }
}

void MainWindow::on_check_destination_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->destination->setVisible(false);
        ui->check_destination->setText("Désactiver");
    }
    else
    {
        ui->destination->setVisible(true);
        ui->check_destination->setText("Activer");
    }
}

void MainWindow::on_check_ports_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->check_ports_precision->setVisible(false);
        ui->ports->setVisible(false);
        ui->choise_ports->setVisible(false);
        ui->check_ports->setText("Désactiver");
    }
    else
    {
        ui->check_ports_precision->setVisible(true);
        ui->ports->setVisible(true);
        if(ui->check_ports_precision->isChecked())
            ui->choise_ports->setVisible(true);
        ui->check_ports->setText("Activer");
    }
}


void MainWindow::on_check_mac_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->mac->setVisible(false);
        ui->check_mac->setText("Désactiver");
    }
    else
    {
        ui->mac->setVisible(true);
        ui->check_mac->setText("Activer");
    }
}

void MainWindow::on_check_interface_output_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->choise_interface_output->setVisible(false);
        ui->check_interface_output->setText("Désactiver");
    }
    else
    {
        ui->choise_interface_output->setVisible(true);
        ui->check_interface_output->setText("Activer");
    }
}


void MainWindow::on_check_interface_input_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->choise_interface_input->setVisible(false);
        ui->check_interface_input->setText("Désactiver");
    }
    else
    {
        ui->choise_interface_input->setVisible(true);
        ui->check_interface_input->setText("Activer");
    }
}

void MainWindow::on_check_ports_precision_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->choise_ports->setVisible(false);
        ui->check_ports_precision->setText("Non préciser");
    }
    else
    {
        ui->choise_ports->setVisible(true);
        ui->check_ports_precision->setText("Préciser");
    }
}

// Check 2
void MainWindow::on_check_protocole_2_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->choise_protocole_2->setVisible(false);
        ui->check_protocole_2->setText("Désactiver");
    }
    else
    {
        ui->choise_protocole_2->setVisible(true);
        ui->check_protocole_2->setText("Activer");
    }
}

void MainWindow::on_check_source_2_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->source_2->setVisible(false);
        ui->check_source_2->setText("Désactiver");
    }
    else
    {
        ui->source_2->setVisible(true);
        ui->check_source_2->setText("Activer");
    }
}

void MainWindow::on_check_destination_2_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->destination_2->setVisible(false);
        ui->check_destination_2->setText("Désactiver");
    }
    else
    {
        ui->destination_2->setVisible(true);
        ui->check_destination_2->setText("Activer");
    }
}

void MainWindow::on_check_ports_2_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->check_ports_precision_2->setVisible(false);
        ui->ports_2->setVisible(false);
        ui->choise_ports_2->setVisible(false);
        ui->check_ports_2->setText("Désactiver");
    }
    else
    {
        ui->check_ports_precision_2->setVisible(true);
        ui->ports_2->setVisible(true);
        if(ui->check_ports_precision_2->isChecked())
            ui->choise_ports_2->setVisible(true);
        ui->check_ports_2->setText("Activer");
    }
}


void MainWindow::on_check_mac_2_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->mac_2->setVisible(false);
        ui->check_mac_2->setText("Désactiver");
    }
    else
    {
        ui->mac_2->setVisible(true);
        ui->check_mac_2->setText("Activer");
    }
}

void MainWindow::on_check_interface_output_2_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->choise_interface_output_2->setVisible(false);
        ui->check_interface_output_2->setText("Désactiver");
    }
    else
    {
        ui->choise_interface_output_2->setVisible(true);
        ui->check_interface_output_2->setText("Activer");
    }
}


void MainWindow::on_check_interface_input_2_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->choise_interface_input_2->setVisible(false);
        ui->check_interface_input_2->setText("Désactiver");
    }
    else
    {
        ui->choise_interface_input_2->setVisible(true);
        ui->check_interface_input_2->setText("Activer");
    }
}

void MainWindow::on_check_ports_precision_2_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->choise_ports_2->setVisible(false);
        ui->check_ports_precision_2->setText("Non préciser");
    }
    else
    {
        ui->choise_ports_2->setVisible(true);
        ui->check_ports_precision_2->setText("Préciser");
    }
}


void MainWindow::on_annuler_clicked()
{
    MainWindow::hide_all();
    ui->page->setCurrentIndex(0);
}


void MainWindow::on_button_add_clicked()
{
    QString command = "sudo iptables ";
    QString chaine  = ui->choise_chaine->currentText();
    QString protocole = ui->choise_protocole->currentText();
    QString ports = ui->ports->text();
    QString interface_input = ui->choise_interface_output->currentText();
    QString interface_output = ui->choise_interface_input->currentText();
    QString mac = ui->mac->text();
    QString source = ui->source->text();
    QString destination = ui->destination->text();
    QString target = ui->choise_target->currentText();


    command += " -A "+chaine;
    command += " -j "+target;
    if(ui->check_protocole->isChecked())
    {
        command += " -p "+protocole;
    }
    if(ui->check_ports->isChecked())
    {
        if(ui->check_ports_precision->isChecked())
        {
            int n=ui->choise_ports->currentIndex();
            if(n==0)
                command += " -m multiport --sports "+ports;
            else
                command += " -m multiport --dports "+ports;
        }
        else
        {
            command += " -m multiport --ports "+ports;
        }
    }
    if(ui->check_interface_input->isChecked())
    {
        command += " -i "+interface_input;
    }
    if(ui->check_interface_output->isChecked())
    {
        command += " -o "+interface_output;
    }
    if(ui->check_mac->isChecked())
    {
        command += " -m mac --mac-source "+mac;
    }
    if(ui->check_source->isChecked())
    {
        command += " -s "+source;
    }
    if(ui->check_destination->isChecked())
    {
        command += " -d "+destination;
    }

    MainWindow::exec_cmd(command, nullptr);
    MainWindow::print_information();
    ui->page->setCurrentIndex(0);
}

void MainWindow::on_reinitialisation_clicked()
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Warning);
    msg.setText("Voulez-vous vraiment réinitialiser les regles des tables?");
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int n = msg.exec();
    if(n == QMessageBox::Ok)
    {
        MainWindow::exec_cmd("sudo iptables -F", nullptr);
        MainWindow::print_information();
    }
}


void MainWindow::on_save_clicked()
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Warning);
    msg.setText("Voulez-vous vraiment sauvegarder les regles des tables?");
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int n = msg.exec();
    if(n == QMessageBox::Ok)
    {
        MainWindow::exec_cmd("sudo iptables-save", nullptr);
    }
}


void MainWindow::on_ajout_clicked()
{
    ui->page->setCurrentIndex(1);
}


void MainWindow::on_annuler_2_clicked()
{
    MainWindow::hide_all();
    ui->page->setCurrentIndex(0);
}

void MainWindow::modify_clicked(int n, std::string chaine)
{
    QString command = "sudo iptables ";
    QString protocole = ui->choise_protocole_2->currentText();
    QString ports = ui->ports_2->text();
    QString interface_input = ui->choise_interface_output_2->currentText();
    QString interface_output = ui->choise_interface_input_2->currentText();
    QString mac = ui->mac_2->text();
    QString source = ui->source_2->text();
    QString destination = ui->destination_2->text();
    QString target = ui->choise_target_2->currentText();
    QString ligne = QString::number(n);


    command += " -R "+QString::fromStdString(chaine)+" "+ligne;
    if(target != "UNKNOWN")
        command += " -j "+target;
    if(ui->check_protocole_2->isChecked())
    {
        command += " -p "+protocole;
    }
    if(ui->check_ports_2->isChecked())
    {
        if(ui->check_ports_precision_2->isChecked())
        {
            int n=ui->choise_ports_2->currentIndex();
            if(n==0)
                command += " -m multiport --sports "+ports;
            else
                command += " -m multiport --dports "+ports;
        }
        else
        {
            command += " -m multiport --ports "+ports;
        }
    }
    if(ui->check_interface_input_2->isChecked())
    {
        command += " -i "+interface_input;
    }
    if(ui->check_interface_output_2->isChecked())
    {
        command += " -o "+interface_output;
    }
    if(ui->check_mac_2->isChecked())
    {
        command += " -m mac --mac-source "+mac;
    }
    if(ui->check_source_2->isChecked())
    {
        command += " -s "+source;
    }
    if(ui->check_destination_2->isChecked())
    {
        command += " -d "+destination;
    }

    MainWindow::exec_cmd(command, nullptr);
    MainWindow::print_information();
    ui->page->setCurrentIndex(0);
}

