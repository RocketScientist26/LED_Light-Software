#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImage>
#include <QVideoFrame>

extern QString settings_images_dir;

//Init
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    this->setFixedSize(849, 561);
    ui->setupUi(this);

    //Settings
    Settings_Init();
    //Setup table
    on_actionTableResizeAction_triggered();
}
MainWindow::~MainWindow(){
    delete ui;
}

//Convert
void MainWindow::on_actionConvertAction_triggered(){
    //Export
    QString file_dir = QFileDialog::getExistingDirectory(this, tr("Choose directory"), "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(file_dir.length() > 0){
        if(ui->checkBox_CH->isChecked()){
            Export_CH(&file_dir, Export_Data());
        }
        if(ui->checkBox_Bin->isChecked()){
            Export_Bin(&file_dir, Export_Data());
        }
    }
}

//Add remove images
void MainWindow::on_actionBrowseAction_triggered(){
    QStringList file_names = QFileDialog::getOpenFileNames(this, QString("Browse for ").append(QString::number(ui->spinBox_Width->value())).append("x").append(QString::number(ui->spinBox_Height->value())).append(" pixels image files"), settings_images_dir, "Image files (*.bmp *.gif *.jpeg *.jpg *.png)");
    file_names.sort(Qt::CaseInsensitive);
    if(file_names.length()){
        settings_images_dir = file_names.at(0).chopped(file_names.at(0).length() - file_names.at(0).lastIndexOf('/'));
        Settings_Store();
    }
    int i = 0;
    while((i != file_names.length()) && (ui->listWidget->count() < MAX_IMAGE_COUNT)){
        QImage tmpimage;
        if(file_names.at(i).length() > 0){
            if (tmpimage.load(QFileInfo(file_names.at(i)).absoluteFilePath())){
                if((tmpimage.width() == ui->spinBox_Width->value()) && (tmpimage.height() == ui->spinBox_Height->value())){
                    if(tmpimage.format()){
                        image[ui->listWidget->count()] = tmpimage;
                        image[ui->listWidget->count()].convertTo(QImage::Format_RGB888);

                        //Set Thumbnail
                        QLabel *label = new QLabel();
                        label->setFixedWidth(IMAGE_THUMBNAIL_WIDTH);
                        label->setFixedHeight(IMAGE_THUMBNAIL_HEIGHT);
                        label->setScaledContents(false);
                        label->setAlignment(Qt::AlignCenter);
                        label->setPixmap(QPixmap::fromImage(image[ui->listWidget->count()]).scaled(IMAGE_THUMBNAIL_WIDTH, IMAGE_THUMBNAIL_HEIGHT,Qt::KeepAspectRatio));
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
void MainWindow::on_actionDelAction_triggered(){
    if(ui->listWidget->count()){
        QListWidgetItem *item;
        item = ui->listWidget->takeItem(ui->listWidget->count() - 1);
        if(item != nullptr){
            //Delete garbage if any
            delete item;
        }
    }
    UIEnableConditional();
}
void MainWindow::on_actionClearAction_triggered(){
    int i = ui->listWidget->count();
    while(i != 0){
        i--;
        QListWidgetItem *item;
        item = ui->listWidget->takeItem(i);
        if(item != nullptr){
            //Delete garbage if any
            delete item;
        }
    }
    UIEnableConditional();
}

//UI
void MainWindow::UIEnableConditional(){
    if(!ui->listWidget->count() || (!ui->checkBox_Bin->isChecked() && !ui->checkBox_CH->isChecked())){
        //No files
        ui->pushButton_Convert->setEnabled(false);
        ui->pushButton_Browse->setEnabled(true);
        ui->pushButton_Del->setEnabled(false);
        ui->pushButton_Clear->setEnabled(false);
    }else if(ui->listWidget->count() >= MAX_IMAGE_COUNT){
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
void MainWindow::on_actionTableCellChangedAction_triggered(){
    if(ui->tableWidget->currentItem()){
        if(ui->tableWidget->currentItem()->background().color() == table_normal_color){
            ui->tableWidget->currentItem()->setBackground(QBrush(table_selected_color));
            ui->tableWidget->setStyleSheet(QString("QTableView {selection-background-color: rgb(")
                                           .append(QString::number(table_selected_color.red()))
                                           .append(", ")
                                           .append(QString::number(table_selected_color.green()))
                                           .append(", ")
                                           .append(QString::number(table_selected_color.blue()))
                                           .append(");}")
                                           );
        }else{
            ui->tableWidget->currentItem()->setBackground(QBrush(table_normal_color));
            ui->tableWidget->setStyleSheet(QString("QTableView {selection-background-color: rgb(")
                                           .append(QString::number(table_normal_color.red()))
                                           .append(", ")
                                           .append(QString::number(table_normal_color.green()))
                                           .append(", ")
                                           .append(QString::number(table_normal_color.blue()))
                                           .append(");}")
                                           );
        }
    }
}
void MainWindow::on_actionTableResizeAction_triggered(){
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
            ui->tableWidget->item(r,c)->setBackground(QBrush(table_normal_color));
            r++;
        }
        c++;
    }
    ui->listWidget->clear();
    UIEnableConditional();
    Settings_Store();
}
void MainWindow::on_actionPulseChangedAction_triggered(){
    ui->spinBox_One->setMaximum(ui->spinBox_Pulse->value());
    ui->spinBox_Zero->setMaximum(ui->spinBox_Pulse->value());
    Settings_Store();
}
void MainWindow::on_actionPointSizeChangedAction_triggered(){
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(ui->spinBox_Point_Size->value());
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(ui->spinBox_Point_Size->value());
    Settings_Store();
}
void MainWindow::on_actionCheckBoxGenerateAction_triggered(){
    UIEnableConditional();
    Settings_Store();
}
void MainWindow::on_actionClockZeroOneStopSpinBoxChangedAction_triggered(){
    Settings_Store();
}
