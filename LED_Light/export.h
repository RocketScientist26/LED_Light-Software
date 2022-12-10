//! Class for exporting images array into MCU understandable format
#ifndef EXPORT_H
#define EXPORT_H

#include <QObject>
#include <QImage>
#include <QFile>
#include <QFileInfo>
#include <QTableWidget>
#include "crc32.h"

class Export : public QObject
{
    Q_OBJECT
    public:
        //Export
        #define EXPORT_ARRAY_BYTES_PER_LINE 15
        //Table
        #define TABLE_COLOR_UNSELECTED 100, 100, 100
        #define TABLE_COLOR_SELECTED 255, 0, 0

        enum{
            ORDER_GRB,
            ORDER_RGB
        };
        enum{
            SCAN_LEFT_RIGHT_TOP_BOTTOM_ZIGZAG,
            SCAN_RIGHT_LEFT_TOP_BOTTOM_ZIGZAG,
            SCAN_LEFT_RIGHT_BOTTOM_TOP_ZIGZAG,
            SCAN_RIGHT_LEFT_BOTTOM_TOP_ZIGZAG,
            SCAN_TOP_BOTTOM_LEFT_RIGHT_ZIGZAG,
            SCAN_BOTTOM_TOP_LEFT_RIGHT_ZIGZAG,
            SCAN_TOP_BOTTOM_RIGHT_LEFT_ZIGZAG,
            SCAN_BOTTOM_TOP_RIGHT_LEFT_ZIGZAG,
            SCAN_LEFT_RIGHT_TOP_BOTTOM_LINES,
            SCAN_RIGHT_LEFT_TOP_BOTTOM_LINES,
            SCAN_LEFT_RIGHT_BOTTOM_TOP_LINES,
            SCAN_RIGHT_LEFT_BOTTOM_TOP_LINES,
            SCAN_TOP_BOTTOM_LEFT_RIGHT_LINES,
            SCAN_BOTTOM_TOP_LEFT_RIGHT_LINES,
            SCAN_TOP_BOTTOM_RIGHT_LEFT_LINES,
            SCAN_BOTTOM_TOP_RIGHT_LEFT_LINES
        };

        typedef struct{
            uint16_t clock_divider;
            uint8_t pulse;
            uint8_t zero;
            uint8_t one;
            uint16_t stop_pulses;
            uint32_t images_count;
            QImage *images_data;
            uint8_t scan_direction;
            uint8_t byte_order;
        }export_t;

        explicit Export(
                QObject *parent = nullptr,
                QTableWidget *table_widget = new QTableWidget(),
                QColor unselected_cell_color = QColor::fromRgb(TABLE_COLOR_UNSELECTED),
                QColor selected_cell_color = QColor::fromRgb(TABLE_COLOR_SELECTED)
            );
        QColor unselectedCellColor();
        QColor selectedCellColor();
        void writeBin(QString *dir, export_t config);
        void writeCH(QString *dir, export_t config);

    private:
        QColor table_color_unselected;
        QColor table_color_selected;
        QTableWidget *table;

        uint8_t reverseBits(uint8_t b);
        QByteArray getPixel(QImage *image, int x, int y, uint8_t byte_order);
        QByteArray getArrayByTable(QImage *images_data, uint32_t images_count, uint8_t scan_direction, uint8_t byte_order);
};

#endif // EXPORT_H
