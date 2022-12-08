#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QVideoFrame>
#include <QFile>
#include <QFileInfo>
#include "config.h"
#include "crc32.h"

#define EXPORT_ARRAY_BYTES_PER_LINE 15
#define MAX_IMAGE_COUNT 2000
#define IMAGE_THUMBNAIL_WIDTH 160
#define IMAGE_THUMBNAIL_HEIGHT 100
#define TABLE_NORMAL_COLOR 100, 100, 100
#define TABLE_SELECTED_COLOR 255, 0, 0

namespace Ui{ class MainWindow; }

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionConvert_triggered();
    void on_actionBrowse_triggered();
    void on_actionDel_triggered();
    void on_actionTableCellChanged_triggered();
    void on_actionTableResize_triggered();
    void on_actionPulseChanged_triggered();
    void on_actionPointSizeChanged_triggered();
    void on_actionCheckBoxGenerate_triggered();
    void on_actionClockZeroOneStopSpinBoxChanged_triggered();
    void on_actionClear_triggered();

private:
    Config *config;


    QImage image[MAX_IMAGE_COUNT];
    QColor table_normal_color = QColor(QColor::fromRgb(TABLE_NORMAL_COLOR));
    QColor table_selected_color = QColor(QColor::fromRgb(TABLE_SELECTED_COLOR));

    uint32_t CRC32_Get(uint32_t *data, uint32_t length);

    QByteArray Export_Get_Pixel(int image_n, int x, int y);
    uint8_t Export_Reverse_Bits(uint8_t b);
    QByteArray Export_Data();
    void Export_CH(QString *file_dir, const QByteArray &data);
    void Export_Bin(QString *file_dir, const QByteArray &data);

    void UIEnableConditional();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
