#include "export.h"

/*!
    Constructor function, stores table pointer and cell selected/unselected
    colors in global variables
*/
Export::Export(QObject *parent, QTableWidget *table_widget, QColor unselected_cell_color, QColor selected_cell_color) : QObject{parent}
{
    table = table_widget;
    table_color_unselected = unselected_cell_color;
    table_color_selected = selected_cell_color;
}

//! Reverses bits order in byte
uint8_t Export::reverseBits(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}
//! Returns bytes of pixel at x/y position in selcted format if according table cell has not selected color
QByteArray Export::getPixel(QImage *image, int x, int y, uint8_t byte_order)
{
    QByteArray pixel;
    if(table->item(x, y)->background().color() != table_color_selected){
        switch(byte_order){
            case ORDER_GRB:
                pixel.append(reverseBits((uint8_t)image->pixelColor(x,y).green()));
                pixel.append(reverseBits((uint8_t)image->pixelColor(x,y).red()));
                pixel.append(reverseBits((uint8_t)image->pixelColor(x,y).blue()));
            break;
            case ORDER_RGB:
                pixel.append(reverseBits((uint8_t)image->pixelColor(x,y).red()));
                pixel.append(reverseBits((uint8_t)image->pixelColor(x,y).green()));
                pixel.append(reverseBits((uint8_t)image->pixelColor(x,y).blue()));
            break;
        }
    }
    return pixel;
}
//! Returns array of image bytes according to configuration and table cells selection
QByteArray Export::getArrayByTable(QImage *images_data, uint32_t images_count, uint8_t scan_direction, uint8_t byte_order)
{
    QByteArray bdata;
    uint32_t c = 0;
    int w = 0;
    int h = 0;
    while(c != images_count){
        switch(scan_direction)
        {
            case SCAN_LEFT_RIGHT_TOP_BOTTOM_ZIGZAG:
                h = 0;
                while(h != images_data[c].height()){
                    if(!(h % 2)){
                        w = 0;
                        while(w != images_data[c].width()){
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                            w++;
                        }
                    }else{
                        w = images_data[c].width();
                        while(w != 0){
                            w--;
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        }
                    }
                    h++;
                }
            break;

            case SCAN_RIGHT_LEFT_TOP_BOTTOM_ZIGZAG:
                h = 0;
                while(h != images_data[c].height()){
                    if(!(h % 2)){
                        w = images_data[c].width();
                        while(w != 0){
                            w--;
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        }
                    }else{
                        w = 0;
                        while(w != images_data[c].width()){
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                            w++;
                        }
                    }
                    h++;
                }
            break;

            case SCAN_LEFT_RIGHT_BOTTOM_TOP_ZIGZAG:
                h = images_data[c].height();
                while(h != 0){
                    h--;
                    if(!(h % 2)){
                        w = 0;
                        while(w != images_data[c].width()){
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                            w++;
                        }
                    }else{
                        w = images_data[c].width();
                        while(w != 0){
                            w--;
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        }
                    }
                }
            break;

            case SCAN_RIGHT_LEFT_BOTTOM_TOP_ZIGZAG:
                h = images_data[c].height();
                while(h != 0){
                    h--;
                    if(!(h % 2)){
                        w = images_data[c].width();
                        while(w != 0){
                            w--;
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        }
                    }else{
                        w = 0;
                        while(w != images_data[c].width()){
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                            w++;
                        }
                    }
                }
            break;

            case SCAN_TOP_BOTTOM_LEFT_RIGHT_ZIGZAG:
                w = 0;
                while(w != images_data[c].width()){
                    if(!(w % 2)){
                        h = 0;
                        while(h != images_data[c].height()){
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                            h++;
                        }
                    }else{
                        h = images_data[c].height();
                        while(h != 0){
                            h--;
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        }
                    }
                    w++;
                }
            break;

            case SCAN_BOTTOM_TOP_LEFT_RIGHT_ZIGZAG:
                w = 0;
                while(w != images_data[c].width()){
                    if(!(w % 2)){
                        h = images_data[c].height();
                        while(h != 0){
                            h--;
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        }
                    }else{
                        h = 0;
                        while(h != images_data[c].height()){
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                            h++;
                        }
                    }
                    w++;
                }
            break;

            case SCAN_TOP_BOTTOM_RIGHT_LEFT_ZIGZAG:
                w = images_data[c].width();
                while(w != 0){
                    w--;
                    if(!(w % 2)){
                        h = 0;
                        while(h != images_data[c].height()){
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                            h++;
                        }
                    }else{
                        h = images_data[c].height();
                        while(h != 0){
                            h--;
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        }
                    }
                }
            break;

            case SCAN_BOTTOM_TOP_RIGHT_LEFT_ZIGZAG:
                w = images_data[c].width();
                while(w != 0){
                    w--;
                    if(!(w % 2)){
                        h = images_data[c].height();
                        while(h != 0){
                            h--;
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        }
                    }else{
                        h = 0;
                        while(h != images_data[c].height()){
                            bdata.append(getPixel(&images_data[c], w, h, byte_order));
                            h++;
                        }
                    }
                }
            break;

            case SCAN_LEFT_RIGHT_TOP_BOTTOM_LINES:
                h = 0;
                while(h != images_data[c].height()){
                    w = 0;
                    while(w != images_data[c].width()){
                        bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        w++;
                    }
                    h++;
                }
            break;

            case SCAN_RIGHT_LEFT_TOP_BOTTOM_LINES:
                h = 0;
                while(h != images_data[c].height()){
                    w = images_data[c].width();
                    while(w != 0){
                        w--;
                        bdata.append(getPixel(&images_data[c], w, h, byte_order));
                    }
                    h++;
                }
            break;

            case SCAN_LEFT_RIGHT_BOTTOM_TOP_LINES:
                h = images_data[c].height();
                while(h != 0){
                    h--;
                    w = 0;
                    while(w != images_data[c].width()){
                        bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        w++;
                    }
                }
            break;

            case SCAN_RIGHT_LEFT_BOTTOM_TOP_LINES:
                h = images_data[c].height();
                while(h != 0){
                    h--;
                    w = images_data[c].width();
                    while(w != 0){
                        w--;
                        bdata.append(getPixel(&images_data[c], w, h, byte_order));
                    }
                }
            break;

            case SCAN_TOP_BOTTOM_LEFT_RIGHT_LINES:
                w = 0;
                while(w != images_data[c].width()){
                    h = 0;
                    while(h != images_data[c].height()){
                        bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        h++;
                    }
                    w++;
                }
            break;

            case SCAN_BOTTOM_TOP_LEFT_RIGHT_LINES:
                w = 0;
                while(w != images_data[c].width()){
                    h = images_data[c].height();
                    while(h != 0){
                        h--;
                        bdata.append(getPixel(&images_data[c], w, h, byte_order));
                    }
                    w++;
                }
            break;

            case SCAN_TOP_BOTTOM_RIGHT_LEFT_LINES:
                w = images_data[c].width();
                while(w != 0){
                    w--;
                    h = 0;
                    while(h != images_data[c].height()){
                        bdata.append(getPixel(&images_data[c], w, h, byte_order));
                        h++;
                    }
                }
            break;

            case SCAN_BOTTOM_TOP_RIGHT_LEFT_LINES:
                w = images_data[c].width();
                while(w != 0){
                    w--;
                    h = images_data[c].height();
                    while(h != 0){
                        h--;
                        bdata.append(getPixel(&images_data[c], w, h, byte_order));
                    }
                }
            break;

        }
        c++;
    }
    return bdata;
}

//! Returns currently used unselected cell color
QColor Export::unselectedCellColor()
{
    return table_color_unselected;
}
//! Returns currently used selected cell color
QColor Export::selectedCellColor()
{
    return table_color_selected;
}
//! Writes binary data file into selected directory
void Export::writeBin(QString *dir, export_t config)
{
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

        QByteArray data = getArrayByTable(config.images_data, config.images_count, config.scan_direction, config.byte_order);
        QByteArray bdata;
        //[TOTAL_LENGTH 4]
        uint32_t length = data.length() + 23;
        while(length % 4){
            length++;
        }
        bdata.append((const char *)&length, 4);
        //[ANIMATION_DATA_CLKDIV 2]
        bdata.append((const char *)&config.clock_divider, 2);
        //[ANIMATION_DATA_PULSE 1]
        bdata.append((const char *)&config.pulse, 1);
        //[ANIMATION_DATA_BIT_0 1]
        bdata.append(config.zero);
        //[ANIMATION_DATA_BIT_1 1]
        bdata.append(config.one);
        //[ANIMATION_DATA_STOP_PULSES 2]
        bdata.append((const char *)&config.stop_pulses, 2);
        //[ANIMATION_DATA_IMAGES 4]
        bdata.append((const char *)&config.images_count, 4);
        //[ANIMATION_DATA_IMAGE_SIZE 4]
        uint32_t image_size_bytes = data.length() / config.images_count;
        bdata.append((const char *)&image_size_bytes, 4);
        //[IMAGE_DATA ***]
        bdata.append(data);
        //[PADDING_TO_32]
        while(bdata.length() % 4){
            bdata.append((uint8_t)0);
        }
        //[CRC 4]
        uint32_t crc = Crc32((uint32_t *)&bdata.data()[0], bdata.length() / 4).getCrc();
        bdata.append((const char *)&crc, 4);

        //Save file
        QFile bfile(QFileInfo(*dir).absoluteFilePath().append("/animation_data.img"));
        if (bfile.open(QIODevice::WriteOnly)){
            bfile.write(bdata);
            bfile.close();
        }
}
//! Writes *.c and *.h files into selected directory
void Export::writeCH(QString *file_dir, export_t config)
{
        QByteArray data = getArrayByTable(config.images_data, config.images_count, config.scan_direction, config.byte_order);
        ///H File
        QString hdata;
        hdata.append("#define ANIMATION_DATA_CLKDIV ").append(QString::number(config.clock_divider)).append("\n");
        hdata.append("#define ANIMATION_DATA_PULSE ").append(QString::number(config.pulse)).append("\n");
        hdata.append("#define ANIMATION_DATA_BIT_0 ").append(QString::number(config.zero)).append("\n");
        hdata.append("#define ANIMATION_DATA_BIT_1 ").append(QString::number(config.one)).append("\n");
        hdata.append("#define ANIMATION_DATA_STOP_PULSES ").append(QString::number(config.stop_pulses)).append("\n");
        hdata.append("#define ANIMATION_DATA_IMAGES ").append(QString::number(config.images_count)).append("\n");
        hdata.append("#define ANIMATION_DATA_IMAGE_SIZE ").append(QString::number(data.length() / config.images_count)).append("\n\n");
        hdata.append("enum{\n");
        //Generate "enum" list of image identifiers
        uint32_t i = 0;
        while(i != config.images_count){
            hdata.append(QString("\tANIMATION_DATA_IMAGE_").append(QString::number(i + 1)));
            i++;
            if(i != config.images_count){
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
        uint32_t c = 0;
        while(c != config.images_count){
            cdata.append("\n\t{\n\t\t");

            i = 0;
            while(i != data.length() / config.images_count){
                cdata.append(QString("0x").append(QString(QStringLiteral("%1").arg((uint8_t)data.at(((data.length() / config.images_count) * c) + i), 2, 16, QLatin1Char('0')))));
                i++;
                if(!(i % EXPORT_ARRAY_BYTES_PER_LINE) && (i != data.length() / config.images_count)){
                    cdata.append(",\n\t\t");
                }else if(i != data.length() / config.images_count){
                    cdata.append(", ");
                }
            }

            cdata.append("\n\t}");
            if(c + 1 != config.images_count){
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
