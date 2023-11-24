#include "resistencia.h"
#include "ui_resistencia.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <qmath.h>
#include <qfiledialog.h>

Resistencia::Resistencia(QWidget *parent) : QMainWindow(parent),
                                            ui(new Ui::Resistencia)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

    /// Escondemos los combobox de las R de 4 y 5 valores.
    ui->comboBox_suma2->setHidden(true);
    ui->comboBox_suma2->setDisabled(true);
    ui->comboBox_suma1->setHidden(true);
    ui->comboBox_suma1->setDisabled(true);

    /// Creamos una lista de colores.
    QList<QColor> bgColors{QColor(Qt::black), QColor(153, 76, 0, 255), QColor(Qt::red), QColor(255, 80, 0, 255), QColor(Qt::yellow), QColor(Qt::green), QColor(Qt::blue), QColor(149, 0, 223, 255), QColor(124, 124, 124, 255), QColor(Qt::white), QColor(209, 190, 76, 255), QColor(208, 253, 255, 255)};
    QList<QColor> fgColors{QColor(Qt::black), QColor(Qt::white), QColor(153, 76, 0, 255)};

    /// Rellenamos los colores de los combobox.
    // ui->comboBox_prueba->setItemData(0, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_prueba->setItemData(6, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_prueba->setItemData(7, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_suma1->setItemData(0, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_suma1->setItemData(6, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_suma1->setItemData(7, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_suma2->setItemData(0, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_suma2->setItemData(6, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_suma2->setItemData(7, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_suma3->setItemData(0, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_suma3->setItemData(6, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_suma3->setItemData(7, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_multiplicador->setItemData(0, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_multiplicador->setItemData(6, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_multiplicador->setItemData(7, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_tolerancia->setItemData(0, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_tolerancia->setItemData(6, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // ui->comboBox_tolerancia->setItemData(7, QBrush(fgColors.at(1)), Qt::TextColorRole);
    // for (int var = 0; var < bgColors.count(); ++var)
    // {
    //     ui->comboBox_prueba->setItemData(var, QBrush(bgColors.at(var)), Qt::BackgroundColorRole);
    //     ui->comboBox_suma1->setItemData(var, QBrush(bgColors.at(var)), Qt::BackgroundColorRole);
    //     ui->comboBox_suma2->setItemData(var, QBrush(bgColors.at(var)), Qt::BackgroundColorRole);
    //     ui->comboBox_suma3->setItemData(var, QBrush(bgColors.at(var)), Qt::BackgroundColorRole);
    //     ui->comboBox_multiplicador->setItemData(var, QBrush(bgColors.at(var)), Qt::BackgroundColorRole);
    //     ui->comboBox_tolerancia->setItemData(var, QBrush(bgColors.at(var)), Qt::BackgroundColorRole);
    // }

    QComboBox *comboBoxes[] = {ui->comboBox_prueba, ui->comboBox_suma1, ui->comboBox_suma2, ui->comboBox_suma3, ui->comboBox_multiplicador, ui->comboBox_tolerancia};

    for (QComboBox *comboBox : comboBoxes)
    {
        for (int var = 0; var < bgColors.count(); ++var)
        {
            if (var == 0 || var == 6 || var == 7)
            {
                comboBox->setItemData(var, QBrush(fgColors.at(1)), Qt::TextColorRole);
            }
            comboBox->setItemData(var, QBrush(bgColors.at(var)), Qt::BackgroundColorRole);
        }
    }
}

Resistencia::~Resistencia()
{
    delete ui;
}

///////////////////////////////////////////////////////
/////////////////// \Cálculo de LED ///////////////////
///////////////////////////////////////////////////////

static double vf, v, a, watt, aTemp, resultado;

void Resistencia::calcular_Ej2() /// calcula utilizando LineEdit
{
    if (!esVacio())
    { // Enciende el led si no estan los parametros vacios
        vf = ui->lineEdit_voltage1->text().toDouble();
        v = ui->lineEdit_voltage2->text().toDouble();

        if (ui->comboBox_ampere->currentIndex() == 0)
        { // Calculamos el valor de "a = Ampere" segun el comboBox
            aTemp = ui->lineEdit_ampere->text().toDouble();
            a = aTemp / 1000;
        }
        else if (ui->comboBox_ampere->currentIndex() == 1)
        {
            a = ui->lineEdit_ampere->text().toDouble();
        }
        else
        {
            watt = ui->lineEdit_ampere->text().toDouble();
            a = watt / v;
        }

        watt = v * a;

        auto temp = vf - v;
        resultado = temp / a;

        ui->statusBar->showMessage("El valor que necesita "
                                   "para la resistencia es de: " +
                                       QString::number(resultado) + " Ohm",
                                   10);

        ui->label_Watt->setText(QString::number(watt) + " Watt");
        qDebug() << resultado;
        ui->label_info->setText("El valor que necesita "
                                "para la resistencia es de: " +
                                QString::number(resultado) + " Ohm");

        ui->lcdNumber->display(resultado);

        if (resultado >= 0 && resultado != INFINITY)
        {
            ui->label_led_on->setEnabled(true);
        }
        else
        {
            ui->label_led_on->setEnabled(false);
        }
    }
}

bool Resistencia::esVacio()
{
    if (ui->lineEdit_voltage1->text() == "" || ui->lineEdit_voltage2->text() == "" || ui->lineEdit_ampere->text() == "")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Resistencia::on_lineEdit_voltage1_textChanged()
{
    calcular_Ej2();
}

void Resistencia::on_lineEdit_voltage2_textChanged()
{
    calcular_Ej2();
}

void Resistencia::on_lineEdit_ampere_textChanged()
{
    // ui->lineEdit_ampere->selectAll(); ///hay q implementarlo para cuando se de click en el lineEdit
    calcular_Ej2();
}

void Resistencia::on_comboBox_ampere_currentIndexChanged()
{
    calcular_Ej2();
}

///////////////////////////////////////////////////////
////////////// \Cálculo de Colores ////////////////////
///////////////////////////////////////////////////////

QString Resistencia::obten_colores_del_boton(int index)
{
    // Definir una estructura para asociar el índice del combo box con el estilo
    struct ComboBoxStyle
    {
        int index;
        QString style;
    };

    // Crear un arreglo de colores y estilos correspondientes
    QList<ComboBoxStyle> comboBoxStyles = {
        {0, "QComboBox { background-color: black; color: white; selection-background-color: rgb(0,0,0,0); selection-color: rgb(255, 255, 255); }"},
        {1, "QComboBox { background-color: rgb(153,76,0); selection-background-color: rgb(0,0,0,0); }"},
        {2, "QComboBox { background-color: red; selection-background-color: rgb(0,0,0,0); }"},
        {3, "QComboBox { background-color: rgb(255,80,0); selection-background-color: rgb(0,0,0,0); }"},
        {4, "QComboBox { background-color: yellow; color: black; selection-background-color: rgb(0,0,0,0); selection-color: rgb(70, 70, 70); }"},
        {5, "QComboBox { background-color: green; selection-background-color: rgb(0,0,0,0); selection-color: rgb(255, 255, 255); }"},
        {6, "QComboBox { background-color: blue; selection-background-color: rgb(0,0,0,0); selection-color: rgb(255, 255, 255); }"},
        {7, "QComboBox { background-color: rgb(149,0,223,255); selection-background-color: rgb(0,0,0,0); selection-color: rgb(255, 255, 255); }"},
        {8, "QComboBox { background-color: rgb(124,124,124,255); selection-background-color: rgb(0,0,0,0); selection-color: rgb(255, 255, 255); }"},
        {9, "QComboBox { background-color: white; color: black; selection-background-color: rgb(0,0,0,0); selection-color: rgb(70, 70, 70); }"},
        {10, "QComboBox { background-color: rgb(209,190,76,180); selection-background-color: rgb(0,0,0,0); selection-color: rgb(255, 255, 255); }"},
        {11, "QComboBox { background-color: rgb(208,253,255,180); color: black; selection-background-color: rgb(0,0,0,0); selection-color: rgb(70, 70, 70); }"},
        // Agregar el resto de los estilos
    };

    // Obtener el índice actual del combo box
    // int currentIndex = ui->comboBox_prueba->currentIndex();
    int currentIndex = index;

    // Buscar el estilo correspondiente al índice en el arreglo de estilos
    QString style;
    for (const ComboBoxStyle &comboBoxStyle : comboBoxStyles)
    {
        if (comboBoxStyle.index == currentIndex)
        {
            style = comboBoxStyle.style;
            break;
        }
    }
    return style;
}

void Resistencia::on_comboBox_prueba_currentIndexChanged(int index)
{
    // Aplicar el estilo al combo box
    ui->comboBox_prueba->setStyleSheet(obten_colores_del_boton(index));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Resistencia::calcular_Color()
{
    int suma1 = ui->comboBox_suma1->currentIndex() * 100;
    int suma2 = ui->comboBox_suma2->currentIndex() * 10;
    int suma3 = ui->comboBox_suma3->currentIndex();
    int suma;

    if (ui->radioButton_3bandas->isChecked())
    {
        suma = suma3;
    }
    else if (ui->radioButton_4bandas->isChecked())
    {
        suma = suma3 + suma2;
    }
    else
    {
        suma = suma3 + suma2 + suma1;
    }

    long multiplicador = pow(10, ui->comboBox_multiplicador->currentIndex());

    long resul = suma * multiplicador;
    qDebug() << resul;
    ui->label_ohm->setText(QString::number(resul));
}

void Resistencia::on_radioButton_3bandas_clicked()
{
    ui->comboBox_suma2->setHidden(true);
    ui->comboBox_suma2->setDisabled(true);
    ui->comboBox_suma1->setHidden(true);
    ui->comboBox_suma1->setDisabled(true);
}

void Resistencia::on_radioButton_4bandas_clicked()
{
    ui->comboBox_suma2->setHidden(false);
    ui->comboBox_suma2->setDisabled(false);
    ui->comboBox_suma1->setHidden(true);
    ui->comboBox_suma1->setDisabled(true);
}

void Resistencia::on_radioButton_5bandas_clicked()
{
    ui->comboBox_suma2->setHidden(false);
    ui->comboBox_suma2->setDisabled(false);
    ui->comboBox_suma1->setHidden(false);
    ui->comboBox_suma1->setDisabled(false);
}

void Resistencia::on_comboBox_suma1_currentIndexChanged(int index)
{
    calcular_Color();
    // Aplicar el estilo al combo box
    ui->comboBox_suma1->setStyleSheet(obten_colores_del_boton(index));
}

void Resistencia::on_comboBox_suma2_currentIndexChanged(int index)
{
    calcular_Color();
    // Aplicar el estilo al combo box
    ui->comboBox_suma2->setStyleSheet(obten_colores_del_boton(index));
}

void Resistencia::on_comboBox_suma3_currentIndexChanged(int index)
{
    calcular_Color();
    // Aplicar el estilo al combo box
    ui->comboBox_suma3->setStyleSheet(obten_colores_del_boton(index));
}

void Resistencia::on_comboBox_multiplicador_currentIndexChanged(int index)
{
    calcular_Color();
    // Aplicar el estilo al combo box
    ui->comboBox_multiplicador->setStyleSheet(obten_colores_del_boton(index));
}

void Resistencia::on_comboBox_tolerancia_currentIndexChanged()
{
    calcular_Color();
}

///////////////////////////////////////////////////////
////////////// \Barra de Actividades //////////////////
///////////////////////////////////////////////////////

void Resistencia::on_actionAcerca_triggered()
{
    QMessageBox::information(this, tr("Acerca"), tr("<h2>Este programa fue creado por: </h2>"
                                                    "<p>Ronal Zambrano Ferrer. (Mr. Virus ®)"
                                                    "<blockquote>"
                                                    "<p>Santiago de Cuba (Cuba)"
                                                    "<p>Movil: <strong>+53 53843778</strong> "
                                                    "<p><a href=\"https://wa.me/qr/OYEYTBZMFJWWI1\"><font color=green>WhatsApp.</font>" /// LINK  https://wa.me/qr/OYEYTBZMFJWWI1
                                                    "<a href=\"https://t.me/MrVirus_CU\"><strong>Telegram.</strong></a>"
                                                    "</blockquote>"));
}

void Resistencia::on_actionLey_de_Ohm_triggered()
{
    QMessageBox::about(this, tr("Acerca"), "");
}
