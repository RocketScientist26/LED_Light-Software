#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileInfo>

QByteArray MainWindow::Export_Data(){
    //!TBD
    QByteArray bdata;
    int c = 0;
    int w = 0;
    int h = 0;
    while(c != ui->listWidget->count()){
        switch(ui->comboBox_Scan_Direction->currentIndex()){
            //Left to Right / Top to Bottom
            case 0:
                h = 0;
                while(h != image[c].height()){
                    if(!(h % 2)){
                        w = 0;
                        while(w != image[c].width()){
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                            w++;
                        }
                    }else{
                        w = image[c].width();
                        while(w != 0){
                            w--;
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                        }
                    }
                    h++;
                }
            break;

            //Right to Left / Top to Bottom
            case 1:
                h = 0;
                while(h != image[c].height()){
                    if(!(h % 2)){
                        w = image[c].width();
                        while(w != 0){
                            w--;
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                        }
                    }else{
                        w = 0;
                        while(w != image[c].width()){
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                            w++;
                        }
                    }
                    h++;
                }
            break;

            //Left to Right / Bottom to Top
            case 2:
                h = image[c].height();
                while(h != 0){
                    h--;
                    if(!(h % 2)){
                        w = 0;
                        while(w != image[c].width()){
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                            w++;
                        }
                    }else{
                        w = image[c].width();
                        while(w != 0){
                            w--;
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                        }
                    }
                }
            break;

            //Right to Left / Bottom to Top
            case 3:
                h = image[c].height();
                while(h != 0){
                    h--;
                    if(!(h % 2)){
                        w = image[c].width();
                        while(w != 0){
                            w--;
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                        }
                    }else{
                        w = 0;
                        while(w != image[c].width()){
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                            w++;
                        }
                    }
                }
            break;

            //Top to Bottom / Left to Right
            case 4:
                w = 0;
                while(w != image[c].width()){
                    if(!(w % 2)){
                        h = 0;
                        while(h != image[c].height()){
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                            h++;
                        }
                    }else{
                        h = image[c].height();
                        while(h != 0){
                            h--;
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                        }
                    }
                    w++;
                }
            break;

            //Bottom to Top / Left to Right
            case 5:
                w = 0;
                while(w != image[c].width()){
                    if(!(w % 2)){
                        h = image[c].height();
                        while(h != 0){
                            h--;
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                        }
                    }else{
                        h = 0;
                        while(h != image[c].height()){
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                            h++;
                        }
                    }
                    w++;
                }
            break;

            //Top to Bottom / Right to Left
            case 6:
                w = image[c].width();
                while(w != 0){
                    w--;
                    if(!(w % 2)){
                        h = 0;
                        while(h != image[c].height()){
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                            h++;
                        }
                    }else{
                        h = image[c].height();
                        while(h != 0){
                            h--;
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                        }
                    }
                }
            break;

            //Bottom to Top / Right to Left
            case 7:
                w = image[c].width();
                while(w != 0){
                    w--;
                    if(!(w % 2)){
                        h = image[c].height();
                        while(h != 0){
                            h--;
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                        }
                    }else{
                        h = 0;
                        while(h != image[c].height()){
                            if(ui->tableWidget->item(h,w)->background().color() != table_selected_color){
                                bdata.append((uint8_t)image[c].pixelColor(w,h).green());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).red());
                                bdata.append((uint8_t)image[c].pixelColor(w,h).blue());
                            }
                            h++;
                        }
                    }
                }
            break;
        }
        c++;
    }
    return bdata;
}
void MainWindow::Export_CH(QString *file_dir, const QByteArray &data){
        ///H File
        QString hdata;
        hdata.append("#define ANIMATION_DATA_CLKDIV ").append(QString::number(ui->spinBox_Clock_Divider->value())).append("\n");
        hdata.append("#define ANIMATION_DATA_PULSE ").append(QString::number(ui->spinBox_Pulse->value())).append("\n");
        hdata.append("#define ANIMATION_DATA_BIT_0 ").append(QString::number(ui->spinBox_Zero->value())).append("\n");
        hdata.append("#define ANIMATION_DATA_BIT_1 ").append(QString::number(ui->spinBox_One->value())).append("\n");
        hdata.append("#define ANIMATION_DATA_STOP_PULSES ").append(QString::number(ui->spinBox_Stop_Pulses->value())).append("\n");
        hdata.append("#define ANIMATION_DATA_IMAGES ").append(QString::number(ui->listWidget->count())).append("\n");
        hdata.append("#define ANIMATION_DATA_IMAGE_SIZE ").append(QString::number(data.length() / ui->listWidget->count())).append("\n\n");
        hdata.append("enum{\n");
        //Generate "enum" list of image identifiers
        int i = 0;
        while(i != ui->listWidget->count()){
            hdata.append(QString("\tANIMATION_DATA_IMAGE_").append(QString::number(i + 1)));
            i++;
            if(i != ui->listWidget->count()){
                hdata.append(",");
            }
            hdata.append("\n");
        }
        hdata.append("};");
        //Save H file
        QFile hfile(QFileInfo(*file_dir).absoluteFilePath().append("/animation_data.h"));
        if (hfile.open(QIODevice::WriteOnly)){
            hfile.write(QByteArray::fromRawData(hdata.toUtf8().data(), hdata.length()));
            hfile.close();
        }

        ///C File
        QString cdata;
        cdata.append("#include <stdint.h>\n");
        cdata.append("#include \"animation_data.h\"\n\n");
        cdata.append("uint8_t animation_data[ANIMATION_DATA_IMAGES][ANIMATION_DATA_IMAGE_SIZE] = {");
        int c = 0;
        while(c != ui->listWidget->count()){
            cdata.append("\n\t{\n\t\t");

            i = 0;
            while(i != data.length() / ui->listWidget->count()){
                cdata.append(QString("0x").append(QString(QStringLiteral("%1").arg((uint8_t)data.at(((data.length() / ui->listWidget->count()) * c) + i), 2, 16, QLatin1Char('0')))));
                i++;
                if(!(i % EXPORT_ARRAY_BYTES_PER_LINE) && (i != data.length() / ui->listWidget->count())){
                    cdata.append(",\n\t\t");
                }else if(i != data.length() / ui->listWidget->count()){
                    cdata.append(", ");
                }
            }

            cdata.append("\n\t}");
            if(c + 1 != ui->listWidget->count()){
                cdata.append(",");
            }
            c++;
        }
        cdata.append("\n};");
        //Save C file
        QFile cfile(QFileInfo(*file_dir).absoluteFilePath().append("/animation_data.c"));
        if (cfile.open(QIODevice::WriteOnly)){
            cfile.write(QByteArray::fromRawData(cdata.toUtf8().data(), cdata.length()));
            cfile.close();
        }
}
void MainWindow::Export_Bin(QString *file_dir, const QByteArray &data){
        //BIN File
        /*
            [TOTAL_LENGTH 4]
            [ANIMATION_DATA_CLKDIV 2]
            [ANIMATION_DATA_PULSE 1]
            [ANIMATION_DATA_BIT_0 1]
            [ANIMATION_DATA_BIT_1 1]
            [ANIMATION_DATA_STOP_PULSES 2]
            [ANIMATION_DATA_IMAGES 4]
            [ANIMATION_DATA_IMAGE_SIZE 4]
            [IMAGE_DATA ***]
            [IMAGE_DATA ***]
            [IMAGE_DATA ***]
            [***]
            [PADDING_TO_32]
            [CRC 4]
        */

        QByteArray bdata;
        //[TOTAL_LENGTH 4]
        uint32_t tmp = data.length() + 23;
        while(tmp % 4){
            tmp++;
        }
        bdata.append((const char *)&tmp, 4);
        //[ANIMATION_DATA_CLKDIV 2]
        tmp = (uint16_t)ui->spinBox_Clock_Divider->value();
        bdata.append((const char *)&tmp, 2);
        //[ANIMATION_DATA_PULSE 1]
        tmp = (uint8_t)ui->spinBox_Pulse->value();
        bdata.append((const char *)&tmp, 1);
        //[ANIMATION_DATA_BIT_0 1]
        bdata.append((uint8_t)ui->spinBox_Zero->value());
        //[ANIMATION_DATA_BIT_1 1]
        bdata.append((uint8_t)ui->spinBox_One->value());
        //[ANIMATION_DATA_STOP_PULSES 2]
        tmp = (uint16_t)ui->spinBox_Stop_Pulses->value();
        bdata.append((const char *)&tmp, 2);
        //[ANIMATION_DATA_IMAGES 4]
        tmp = ui->listWidget->count();
        bdata.append((const char *)&tmp, 4);
        //[ANIMATION_DATA_IMAGE_SIZE 4]
        uint32_t image_size_bytes = data.length() / ui->listWidget->count();
        bdata.append((const char *)&image_size_bytes, 4);
        //[IMAGE_DATA ***]
        bdata.append(Export_Data());
        //[PADDING_TO_32]
        while(bdata.length() % 4){
            bdata.append((uint8_t)0);
        }
        //[CRC 4]
        tmp = CRC32_Get((uint32_t *)&bdata.data()[0], bdata.length());
        bdata.append((const char *)&tmp, 4);

        //Save file
        QFile bfile(QFileInfo(*file_dir).absoluteFilePath().append("/animation_data.bin"));
        if (bfile.open(QIODevice::WriteOnly)){
            bfile.write(bdata);
            bfile.close();
        }
}
