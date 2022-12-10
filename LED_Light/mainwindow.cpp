#include "mainwindow.h"
#include "ui_mainwindow.h"

//! Root class constructor destructor
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setFixedSize(849, 561);
    ui->setupUi(this);

    //Config
    config = new Config(
        this,
        Config::config_t{
            .images_width = ui->spinBox_Width->value(),
            .images_height = ui->spinBox_Height->value(),
            .images_dir = "",
            .mask_point_size = ui->spinBox_Point_Size->value(),
            .mask_scan_direction = ui->comboBox_Scan_Direction->currentIndex(),
            .output_clock_divider = ui->spinBox_Clock_Divider->value(),
            .output_pulse = ui->spinBox_Pulse->value(),
            .output_zero = ui->spinBox_Zero->value(),
            .output_one = ui->spinBox_One->value(),
            .output_stop_pulses = ui->spinBox_Stop_Pulses->value(),
            .output_ch = ui->checkBox_CH->isChecked(),
            .output_bin = ui->checkBox_Bin->isChecked(),
            .output_byte_order = ui->comboBox_Byte_Order->currentIndex(),
            .output_dir = ""
        }
    );
    //Apply config to UI
    ui->spinBox_Width->setValue(config->get().images_width);
    ui->spinBox_Height->setValue(config->get().images_height);
    ui->spinBox_Point_Size->setValue(config->get().mask_point_size);
    ui->comboBox_Scan_Direction->setCurrentIndex(config->get().mask_scan_direction);
    ui->spinBox_Clock_Divider->setValue(config->get().output_clock_divider);
    ui->spinBox_Pulse->setValue(config->get().output_pulse);
    ui->spinBox_Zero->setValue(config->get().output_zero);
    ui->spinBox_One->setValue(config->get().output_one);
    ui->spinBox_Stop_Pulses->setValue(config->get().output_stop_pulses);
    ui->checkBox_CH->setChecked(config->get().output_ch);
    ui->checkBox_Bin->setChecked(config->get().output_bin);
    ui->comboBox_Byte_Order->setCurrentIndex(config->get().output_byte_order);

    //Object for exporting data as file
    data_export = new Export(this, ui->tableWidget);

    //Setup table
    on_actionTableResize_triggered();

}
MainWindow::~MainWindow()
{
    delete ui;
}

//! Enables/disables UI elements as necessary
void MainWindow::UIEnableConditional()
{
    if(!ui->listWidget->count() || (!ui->checkBox_Bin->isChecked() && !ui->checkBox_CH->isChecked())){
        //No files
        ui->pushButton_Convert->setEnabled(false);
        ui->pushButton_Browse->setEnabled(true);
        ui->pushButton_Del->setEnabled(false);
        ui->pushButton_Clear->setEnabled(false);
    }else if(ui->listWidget->count() >= IMAGE_MAX_COUNT){
        //Too many files
        ui->pushButton_Convert->setEnabled(true);
        ui->pushButton_Browse->setEnabled(false);
        ui->pushButton_Del->setEnabled(true);
        ui->pushButton_Clear->setEnabled(true);
    }else{
        ui->pushButton_Convert->setEnabled(true);
        ui->pushButton_Browse->setEnabled(true);
        ui->pushButton_Del->setEnabled(true);
        ui->pushButton_Clear->setEnabled(true);
    }
}

//UI Interrupts - Table
void MainWindow::on_actionTableCellChanged_triggered()
{
    if(ui->tableWidget->currentItem()){
        if(ui->tableWidget->currentItem()->background().color() == data_export->unselectedCellColor()){
            ui->tableWidget->currentItem()->setBackground(QBrush(data_export->selectedCellColor()));
            ui->tableWidget->setStyleSheet(QString("QTableView {selection-background-color: rgb(")
                                           .append(QString::number(data_export->selectedCellColor().red()))
                                           .append(", ")
                                           .append(QString::number(data_export->selectedCellColor().green()))
                                           .append(", ")
                                           .append(QString::number(data_export->selectedCellColor().blue()))
                                           .append(");}")
                                           );
        }else{
            ui->tableWidget->currentItem()->setBackground(QBrush(data_export->unselectedCellColor()));
            ui->tableWidget->setStyleSheet(QString("QTableView {selection-background-color: rgb(")
                                           .append(QString::number(data_export->unselectedCellColor().red()))
                                           .append(", ")
                                           .append(QString::number(data_export->unselectedCellColor().green()))
                                           .append(", ")
                                           .append(QString::number(data_export->unselectedCellColor().blue()))
                                           .append(");}")
                                           );
        }
    }
}
void MainWindow::on_actionTableResize_triggered()
{
    //Setup table
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    //Add columns and rows
    ui->tableWidget->model()->insertRows(0, ui->spinBox_Height->value());
    ui->tableWidget->model()->insertColumns(0, ui->spinBox_Width->value());
    //Add cell items
    uint16_t r = 0;
    uint16_t c = 0;
    while(c != ui->tableWidget->model()->columnCount()){
        r = 0;
        while(r != ui->tableWidget->model()->rowCount()){
            QTableWidgetItem *tableitem = new QTableWidgetItem();
            ui->tableWidget->setItem(r,c,tableitem);
            ui->tableWidget->item(r,c)->setBackground(QBrush(data_export->unselectedCellColor()));
            r++;
        }
        c++;
    }
    ui->listWidget->clear();
    UIEnableConditional();

    Config::config_t _config = config->get();
    _config.images_width = ui->spinBox_Width->value();
    _config.images_height = ui->spinBox_Height->value();
    config->save(_config);
}
void MainWindow::on_actionPointSizeChanged_triggered()
{
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(ui->spinBox_Point_Size->value());
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(ui->spinBox_Point_Size->value());

    Config::config_t _config = config->get();
    _config.mask_point_size = ui->spinBox_Point_Size->value();
    config->save(_config);
}

//UI Interrupts - Export config
void MainWindow::on_actionPulseChanged_triggered()
{
    ui->spinBox_One->setMaximum(ui->spinBox_Pulse->value());
    ui->spinBox_Zero->setMaximum(ui->spinBox_Pulse->value());

    Config::config_t _config = config->get();
    _config.output_pulse = ui->spinBox_Pulse->value();
    config->save(_config);
}
void MainWindow::on_actionCheckBoxGenerate_triggered()
{
    UIEnableConditional();

    Config::config_t _config = config->get();
    _config.output_bin = ui->checkBox_Bin->isChecked();
    _config.output_ch = ui->checkBox_CH->isChecked();
    config->save(_config);
}
void MainWindow::on_actionClockZeroOneStopSpinBoxChanged_triggered()
{
    Config::config_t _config = config->get();
    _config.output_zero = ui->spinBox_Zero->value();
    _config.output_one = ui->spinBox_One->value();
    _config.output_stop_pulses = ui->spinBox_Stop_Pulses->value();
    _config.output_clock_divider = ui->spinBox_Clock_Divider->value();
    _config.output_byte_order = ui->comboBox_Byte_Order->currentIndex();
    _config.mask_scan_direction = ui->comboBox_Scan_Direction->currentIndex();
    config->save(_config);
}

//UI Interrupts - Convert
void MainWindow::on_actionConvert_triggered()
{
    //Export
    QString file_dir = QFileDialog::getExistingDirectory(this, tr("Choose directory"), config->get().output_dir, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(file_dir.length() > 0){
        Config::config_t _config = config->get();
        _config.output_dir = file_dir;
        config->save(_config);

        Export::export_t export_data = {
            .clock_divider = (uint16_t)ui->spinBox_Clock_Divider->value(),
            .pulse = (uint8_t)ui->spinBox_Pulse->value(),
            .zero = (uint8_t)ui->spinBox_Zero->value(),
            .one = (uint8_t)ui->spinBox_One->value(),
            .stop_pulses = (uint16_t)ui->spinBox_Stop_Pulses->value(),
            .images_count = (uint32_t)ui->listWidget->count(),
            .images_data = images,
            .scan_direction = (uint8_t)ui->comboBox_Scan_Direction->currentIndex(),
            .byte_order = (uint8_t)ui->comboBox_Byte_Order->currentIndex()
        };

        if(ui->checkBox_CH->isChecked()){
            data_export->writeCH(&file_dir, export_data);
        }
        if(ui->checkBox_Bin->isChecked()){
            data_export->writeBin(&file_dir, export_data);
        }
    }
}

//UI Interrupts - Add/remove images
void MainWindow::on_actionBrowse_triggered()
{
    QStringList file_names = QFileDialog::getOpenFileNames(this, QString("Browse for ").append(QString::number(ui->spinBox_Width->value())).append("x").append(QString::number(ui->spinBox_Height->value())).append(" pixels image files"), config->get().images_dir, "Image files (*.bmp *.gif *.jpeg *.jpg *.png)");
    file_names.sort(Qt::CaseInsensitive);
    if(file_names.length()){
        Config::config_t _config = config->get();
        _config.images_dir = file_names.at(0).chopped(file_names.at(0).length() - file_names.at(0).lastIndexOf('/'));
        config->save(_config);
    }
    int i = 0;
    while((i != file_names.length()) && (ui->listWidget->count() < IMAGE_MAX_COUNT)){
        QImage tmpimage;
        if(file_names.at(i).length() > 0){
            if (tmpimage.load(QFileInfo(file_names.at(i)).absoluteFilePath())){
                if((tmpimage.width() == ui->spinBox_Width->value()) && (tmpimage.height() == ui->spinBox_Height->value())){
                    if(tmpimage.format()){
                        images[ui->listWidget->count()] = tmpimage;
                        images[ui->listWidget->count()].convertTo(QImage::Format_RGB888);

                        //Set Thumbnail
                        QLabel *label = new QLabel();
                        label->setFixedWidth(IMAGE_THUMBNAIL_WIDTH);
                        label->setFixedHeight(IMAGE_THUMBNAIL_HEIGHT);
                        label->setScaledContents(false);
                        label->setAlignment(Qt::AlignCenter);
                        label->setPixmap(QPixmap::fromImage(images[ui->listWidget->count()]).scaled(IMAGE_THUMBNAIL_WIDTH, IMAGE_THUMBNAIL_HEIGHT,Qt::KeepAspectRatio));
                        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                        item->setSizeHint(QSize(IMAGE_THUMBNAIL_WIDTH, IMAGE_THUMBNAIL_HEIGHT + 4));
                        ui->listWidget->addItem(item);
                        ui->listWidget->setItemWidget(item, label);
                        UIEnableConditional();
                    }
                }
            }
        }
        i++;
    }
    UIEnableConditional();
}
void MainWindow::on_actionDel_triggered()
{
    if(ui->listWidget->count()){
        QListWidgetItem *item;
        item = ui->listWidget->takeItem(ui->listWidget->count() - 1);
        if(item != nullptr){
            delete item;
        }
    }
    UIEnableConditional();
}
void MainWindow::on_actionClear_triggered()
{
    int i = ui->listWidget->count();
    while(i != 0){
        i--;
        QListWidgetItem *item;
        item = ui->listWidget->takeItem(i);
        if(item != nullptr){
            delete item;
        }
    }
    UIEnableConditional();
}
