#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QSettings>

class Config : public QObject
{
    Q_OBJECT
    public:
        //Data type
        typedef struct{
            //Images
            int images_width;
            int images_height;
            QString images_dir;
            //Images mask
            int mask_point_size;
            int mask_scan_direction;
            //Output
            int output_clock_divider;
            int output_pulse;
            int output_zero;
            int output_one;
            int output_stop_pulses;
            bool output_ch;
            bool output_bin;
            int output_byte_order;
            QString output_dir;
        }config_t;

        //Functions
        explicit Config(
                QObject *parent = nullptr,
                config_t def_vals = {
                    //Images
                    .images_width = 8,
                    .images_height = 8,
                    .images_dir = "",
                    //Images mask
                    .mask_point_size = 16,
                    .mask_scan_direction = 0,
                    //Output
                    .output_clock_divider = 4,
                    .output_pulse = 104,
                    .output_zero = 2,
                    .output_one = 15,
                    .output_stop_pulses = 40,
                    .output_ch = true,
                    .output_bin = true,
                    .output_byte_order = 0,
                    .output_dir = ""
                }
        );
        void read();
        config_t get();
        void save(config_t config);

    private:
        QSettings *settings;

        //Default values storage
        config_t _def_vals;

        //Read data storage
        config_t _config;
};

#endif // CONFIG_H
