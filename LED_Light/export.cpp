#include "mainwindow.h"
#include "ui_mainwindow.h"

uint8_t MainWindow::Export_Reverse_Bits(uint8_t b){
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}
QByteArray MainWindow::Export_Get_Pixel(int image_n, int x, int y){
    QByteArray pixel;
    if(ui->tableWidget->item(y,x)->background().color() != table_selected_color){
        if(!ui->comboBox_Byte_Order->currentIndex()){
            pixel.append(Export_Reverse_Bits((uint8_t)image[image_n].pixelColor(x,y).green()));
            pixel.append(Export_Reverse_Bits((uint8_t)image[image_n].pixelColor(x,y).red()));
        }else{
            pixel.append(Export_Reverse_Bits((uint8_t)image[image_n].pixelColor(x,y).red()));
            pixel.append(Export_Reverse_Bits((uint8_t)image[image_n].pixelColor(x,y).green()));
        }
        pixel.append(Export_Reverse_Bits((uint8_t)image[image_n].pixelColor(x,y).blue()));
    }
    return pixel;
}
QByteArray MainWindow::Export_Data(){
    QByteArray bdata;
    int c = 0;
    int w = 0;
    int h = 0;
    while(c != ui->listWidget->count()){
        switch(ui->comboBox_Scan_Direction->currentIndex()){
            ///Zig-zag
            //Left to Right / Top to Bottom
            case 0:
                h = 0;
                while(h != image[c].height()){
                    if(!(h % 2)){
                        w = 0;
                        while(w != image[c].width()){
                            bdata.append(Export_Get_Pixel(c, w, h));
                            w++;
                        }
                    }else{
                        w = image[c].width();
                        while(w != 0){
                            w--;
                            bdata.append(Export_Get_Pixel(c, w, h));
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
                            bdata.append(Export_Get_Pixel(c, w, h));
                        }
                    }else{
                        w = 0;
                        while(w != image[c].width()){
                            bdata.append(Export_Get_Pixel(c, w, h));
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
                            bdata.append(Export_Get_Pixel(c, w, h));
                            w++;
                        }
                    }else{
                        w = image[c].width();
                        while(w != 0){
                            w--;
                            bdata.append(Export_Get_Pixel(c, w, h));
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
                            bdata.append(Export_Get_Pixel(c, w, h));
                        }
                    }else{
                        w = 0;
                        while(w != image[c].width()){
                            bdata.append(Export_Get_Pixel(c, w, h));
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
                            bdata.append(Export_Get_Pixel(c, w, h));
                            h++;
                        }
                    }else{
                        h = image[c].height();
                        while(h != 0){
                            h--;
                            bdata.append(Export_Get_Pixel(c, w, h));
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
                            bdata.append(Export_Get_Pixel(c, w, h));
                        }
                    }else{
                        h = 0;
                        while(h != image[c].height()){
                            bdata.append(Export_Get_Pixel(c, w, h));
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
                            bdata.append(Export_Get_Pixel(c, w, h));
                            h++;
                        }
                    }else{
                        h = image[c].height();
                        while(h != 0){
                            h--;
                            bdata.append(Export_Get_Pixel(c, w, h));
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
                            bdata.append(Export_Get_Pixel(c, w, h));
                        }
                    }else{
                        h = 0;
                        while(h != image[c].height()){
                            bdata.append(Export_Get_Pixel(c, w, h));
                            h++;
                        }
                    }
                }
            break;

            ///Lines
            //Left to Right / Top to Bottom
            case 8:
                h = 0;
                while(h != image[c].height()){
                    w = 0;
                    while(w != image[c].width()){
                        bdata.append(Export_Get_Pixel(c, w, h));
                        w++;
                    }
                    h++;
                }
            break;

            //Right to Left / Top to Bottom
            case 9:
                h = 0;
                while(h != image[c].height()){
                    w = image[c].width();
                    while(w != 0){
                        w--;
                        bdata.append(Export_Get_Pixel(c, w, h));
                    }
                    h++;
                }
            break;

            //Left to Right / Bottom to Top
            case 10:
                h = image[c].height();
                while(h != 0){
                    h--;
                    w = 0;
                    while(w != image[c].width()){
                        bdata.append(Export_Get_Pixel(c, w, h));
                        w++;
                    }
                }
            break;

            //Right to Left / Bottom to Top
            case 11:
                h = image[c].height();
                while(h != 0){
                    h--;
                    w = image[c].width();
                    while(w != 0){
                        w--;
                        bdata.append(Export_Get_Pixel(c, w, h));
                    }
                }
            break;

            //Top to Bottom / Left to Right
            case 12:
                w = 0;
                while(w != image[c].width()){
                    h = 0;
                    while(h != image[c].height()){
                        bdata.append(Export_Get_Pixel(c, w, h));
                        h++;
                    }
                    w++;
                }
            break;

            //Bottom to Top / Left to Right
            case 13:
                w = 0;
                while(w != image[c].width()){
                    h = image[c].height();
                    while(h != 0){
                        h--;
                        bdata.append(Export_Get_Pixel(c, w, h));
                    }
                    w++;
                }
            break;

            //Top to Bottom / Right to Left
            case 14:
                w = image[c].width();
                while(w != 0){
                    w--;
                    h = 0;
                    while(h != image[c].height()){
                        bdata.append(Export_Get_Pixel(c, w, h));
                        h++;
                    }
                }
            break;

            //Bottom to Top / Right to Left
            case 15:
                w = image[c].width();
                while(w != 0){
                    w--;
                    h = image[c].height();
                    while(h != 0){
                        h--;
                        bdata.append(Export_Get_Pixel(c, w, h));
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
        //Binary IMG File
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
        tmp = Crc32((uint32_t *)&bdata.data()[0], bdata.length() / 4).getCrc();
        bdata.append((const char *)&tmp, 4);

        //Save file
        QFile bfile(QFileInfo(*file_dir).absoluteFilePath().append("/animation_data.img"));
        if (bfile.open(QIODevice::WriteOnly)){
            bfile.write(bdata);
            bfile.close();
        }
}
