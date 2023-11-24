#ifndef RESISTENCIA_H
#define RESISTENCIA_H

#include <QMainWindow>

namespace Ui {
class Resistencia;
}

class Resistencia : public QMainWindow
{
    Q_OBJECT

public:
    explicit Resistencia(QWidget *parent = nullptr);
    ~Resistencia();

private slots:
    ///////////////////////////////////////////////////////
    ////////////// \Cálculo de LED ////////////////////
    ///////////////////////////////////////////////////////
    void calcular_Ej2();
    bool esVacio();

    void on_lineEdit_voltage1_textChanged();
    void on_lineEdit_voltage2_textChanged();
    void on_lineEdit_ampere_textChanged();
    void on_comboBox_ampere_currentIndexChanged();

    ///////////////////////////////////////////////////////
    ////////////// \Cálculo de Colores ////////////////////
    ///////////////////////////////////////////////////////
    void calcular_Color();

    void on_radioButton_3bandas_clicked();
    void on_radioButton_4bandas_clicked();
    void on_radioButton_5bandas_clicked();

    /// @brief 
    /// @param index 
    /// @return 
    QString obten_colores_del_boton(int index); /// es de prueba
    void on_comboBox_suma1_currentIndexChanged(int index);
    void on_comboBox_suma2_currentIndexChanged(int index);
    void on_comboBox_suma3_currentIndexChanged(int index);

    void on_comboBox_multiplicador_currentIndexChanged(int index);
    void on_comboBox_tolerancia_currentIndexChanged();

    void on_comboBox_prueba_currentIndexChanged(int index); /// es de prueba

    ///////////////////////////////////////////////////////
    ////////////// \Barra de Actividades ////////////////////
    ///////////////////////////////////////////////////////
    void on_actionAcerca_triggered();
    void on_actionLey_de_Ohm_triggered();

private:
    Ui::Resistencia *ui;
};

#endif // RESISTENCIA_H
