#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QFile>
#include <QFileInfo>

void MainWindow::Settings_Init(){
    //If file does not exist, create empty
    if(!QFile("settings.ini").exists()){
        QFile file(QFileInfo("settings.ini").absoluteFilePath());
        if (file.open(QIODevice::WriteOnly)){
            file.close();
        }
    }

    //Read settings
    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("IMAGES");
    int images_width = settings.value("width", ui->spinBox_Width->value()).toInt();
    int images_height = settings.value("height", ui->spinBox_Height->value()).toInt();
    settings_images_dir = settings.value("dir", "").toString();
    settings.endGroup();

    settings.beginGroup("MASK");
    int mask_point_size = settings.value("point-size", ui->spinBox_Point_Size->value()).toInt();
    int mask_scan_direction = settings.value("scan-direction", ui->comboBox_Scan_Direction->currentIndex()).toInt();
    settings.endGroup();

    settings.beginGroup("OUTPUT");
    int output_clock_divider = settings.value("clock-divider", ui->spinBox_Clock_Divider->value()).toInt();
    int output_pulse = settings.value("pulse", ui->spinBox_Pulse->value()).toInt();
    int output_zero = settings.value("zero", ui->spinBox_Zero->value()).toInt();
    int output_one = settings.value("one", ui->spinBox_One->value()).toInt();
    int output_pulses = settings.value("stop-pulses", ui->spinBox_Stop_Pulses->value()).toInt();
    bool output_ch = settings.value("generate-ch-files", ui->checkBox_CH->isChecked()).toBool();
    bool output_bin = settings.value("generate-bin-file", ui->checkBox_Bin->isChecked()).toBool();
    int byte_order = settings.value("byte-order", ui->comboBox_Byte_Order->currentIndex()).toInt();
    settings_output_dir = settings.value("dir", "").toString();
    settings.endGroup();

    //Apply settings
    ui->spinBox_Width->setValue(images_width);
    ui->spinBox_Height->setValue(images_height);
    ui->spinBox_Point_Size->setValue(mask_point_size);
    ui->comboBox_Scan_Direction->setCurrentIndex(mask_scan_direction);
    ui->spinBox_Clock_Divider->setValue(output_clock_divider);
    ui->spinBox_Pulse->setValue(output_pulse);
    ui->spinBox_Zero->setValue(output_zero);
    ui->spinBox_One->setValue(output_one);
    ui->spinBox_Stop_Pulses->setValue(output_pulses);
    ui->checkBox_CH->setChecked(output_ch);
    ui->checkBox_Bin->setChecked(output_bin);
    ui->comboBox_Byte_Order->setCurrentIndex(byte_order);
}
void MainWindow::Settings_Store(){
    QSettings settings("settings.ini", QSettings::IniFormat);

    //Write settings
    settings.beginGroup("IMAGES");
    settings.setValue("width", ui->spinBox_Width->value());
    settings.setValue("height", ui->spinBox_Height->value());
    settings.setValue("dir", settings_images_dir);
    settings.endGroup();

    settings.beginGroup("MASK");
    settings.setValue("point-size", ui->spinBox_Point_Size->value());
    settings.setValue("scan-direction", ui->comboBox_Scan_Direction->currentIndex());
    settings.endGroup();

    settings.beginGroup("OUTPUT");
    settings.setValue("clock-divider", ui->spinBox_Clock_Divider->value());
    settings.setValue("pulse", ui->spinBox_Pulse->value());
    settings.setValue("zero", ui->spinBox_Zero->value());
    settings.setValue("one", ui->spinBox_One->value());
    settings.setValue("stop-pulses", ui->spinBox_Stop_Pulses->value());
    settings.setValue("byte-order", ui->comboBox_Byte_Order->currentIndex());
    settings.setValue("generate-ch-files", ui->checkBox_CH->isChecked());
    settings.setValue("generate-bin-file", ui->checkBox_Bin->isChecked());
    settings.setValue("dir", settings_output_dir);
    settings.endGroup();
}
