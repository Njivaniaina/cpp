#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool ask_passwd();

private slots:

    void on_actualiser_clicked();

    // check 1
    void on_check_protocole_stateChanged(int arg1);

    void on_check_source_stateChanged(int arg1);

    void on_check_destination_stateChanged(int arg1);

    void on_check_ports_stateChanged(int arg1);

    void on_check_mac_stateChanged(int arg1);

    void on_check_interface_output_stateChanged(int arg1);

    void on_check_interface_input_stateChanged(int arg1);

    void on_check_ports_precision_stateChanged(int arg1);

    // check 2
    void on_check_protocole_2_stateChanged(int arg1);

    void on_check_source_2_stateChanged(int arg1);

    void on_check_destination_2_stateChanged(int arg1);

    void on_check_ports_2_stateChanged(int arg1);

    void on_check_mac_2_stateChanged(int arg1);

    void on_check_interface_output_2_stateChanged(int arg1);

    void on_check_interface_input_2_stateChanged(int arg1);

    void on_check_ports_precision_2_stateChanged(int arg1);



    void on_annuler_clicked();

    void on_button_add_clicked();

    void on_reinitialisation_clicked();

    void on_save_clicked();

    void on_ajout_clicked();

    void on_annuler_2_clicked();

private:
    Ui::MainWindow *ui;
    QTabWidget *table_information;

    void hide_all();

    void get_command_rules(std::vector<std::vector<std::vector<std::string>>> *rules);

    void getData(std::vector<std::string> *chaine, std::vector<std::vector<std::vector<std::string>>> *rules, std::vector<std::string> *police);

    void print_information();

    bool exec_cmd(QString command, QString *result_cmd);

    std::vector<std::string> getInterface();

    void modify_clicked(int n, std::string chaine);

    void print_css();
};
#endif // MAINWINDOW_H
