#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define EXPORT_ARRAY_BYTES_PER_LINE 15
#define MAX_IMAGE_COUNT 2000
#define IMAGE_THUMBNAIL_WIDTH 160
#define IMAGE_THUMBNAIL_HEIGHT 100
#define TABLE_NORMAL_COLOR 100, 100, 100
#define TABLE_SELECTED_COLOR 255, 0, 0

QT_BEGIN_NAMESPACE
namespace Ui{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionConvertAction_triggered();
    void on_actionBrowseAction_triggered();
    void on_actionDelAction_triggered();
    void on_actionTableCellChangedAction_triggered();
    void on_actionTableResizeAction_triggered();
    void on_actionPulseChangedAction_triggered();
    void on_actionPointSizeChangedAction_triggered();
    void on_actionCheckBoxGenerateAction_triggered();
    void on_actionClockZeroOneStopSpinBoxChangedAction_triggered();
    void on_actionClearAction_triggered();

private:
    QImage image[MAX_IMAGE_COUNT];
    QColor table_normal_color = QColor(QColor::fromRgb(TABLE_NORMAL_COLOR));
    QColor table_selected_color = QColor(QColor::fromRgb(TABLE_SELECTED_COLOR));

    uint32_t CRC32_Get(uint32_t *data, uint32_t length);

    QByteArray Export_Get_Pixel(int image_n, int x, int y);
    uint8_t Export_Reverse_Bits(uint8_t b);
    QByteArray Export_Data();
    void Export_CH(QString *file_dir, const QByteArray &data);
    void Export_Bin(QString *file_dir, const QByteArray &data);

    void Settings_Init();
    void Settings_Store();

    void UIEnableConditional();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
