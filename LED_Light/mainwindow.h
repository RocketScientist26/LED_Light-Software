#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "export.h"
#include "config.h"
#include "crc32.h"

//Images list
#define IMAGE_MAX_COUNT 2000
#define IMAGE_THUMBNAIL_WIDTH 160
#define IMAGE_THUMBNAIL_HEIGHT 100

namespace Ui{ class MainWindow; }
class MainWindow : public QMainWindow{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_actionBrowse_triggered();
        void on_actionDel_triggered();
        void on_actionClear_triggered();
        void on_actionTableCellChanged_triggered();
        void on_actionTableResize_triggered();
        void on_actionPointSizeChanged_triggered();
        void on_actionPulseChanged_triggered();
        void on_actionCheckBoxGenerate_triggered();
        void on_actionClockZeroOneStopSpinBoxChanged_triggered();
        void on_actionConvert_triggered();

    private:
        Config *config;
        Export *data_export;
        QImage images[IMAGE_MAX_COUNT];

        Ui::MainWindow *ui;

        void UIEnableConditional();
};

#endif // MAINWINDOW_H
