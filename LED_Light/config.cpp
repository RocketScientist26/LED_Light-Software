#include "config.h"

/*!
    Constructor function, creates empty "config.ini" file in
    programs root directory if it does not already exists.
    Reads values from "config.ini" or reads as default values.
*/
Config::Config(QObject *parent, config_t def_vals) : QObject{ parent }
{
    //Create empty file if does not exist
    if(!QFile("config.ini").exists()){
        QFile file(QFileInfo("config.ini").absoluteFilePath());
        if (file.open(QIODevice::WriteOnly)){
            file.close();
        }
    }

    settings = new QSettings("config.ini", QSettings::IniFormat);
    _def_vals = def_vals;
    read();
}

//! Reads "config.ini" from disc to variables
void Config::read()
{
    settings->beginGroup("IMAGES");
    _config.images_width = settings->value("width", _def_vals.images_width).toInt();
    _config.images_height = settings->value("height", _def_vals.images_height).toInt();
    _config.images_dir = settings->value("dir", _def_vals.images_dir).toString();
    settings->endGroup();

    settings->beginGroup("MASK");
    _config.mask_point_size = settings->value("point-size", _def_vals.mask_point_size).toInt();
    _config.mask_scan_direction = settings->value("scan-direction", _def_vals.mask_scan_direction).toInt();
    settings->endGroup();

    settings->beginGroup("OUTPUT");
    _config.output_clock_divider = settings->value("clock-divider", _def_vals.output_clock_divider).toInt();
    _config.output_pulse = settings->value("pulse", _def_vals.output_pulse).toInt();
    _config.output_zero = settings->value("zero", _def_vals.output_zero).toInt();
    _config.output_one = settings->value("one", _def_vals.output_one).toInt();
    _config.output_stop_pulses = settings->value("stop-pulses", _def_vals.output_stop_pulses).toInt();
    _config.output_ch = settings->value("generate-ch-files", _def_vals.output_ch).toBool();
    _config.output_bin = settings->value("generate-bin-file", _def_vals.output_bin).toBool();
    _config.output_byte_order = settings->value("byte-order", _def_vals.output_byte_order).toInt();
    _config.output_dir = settings->value("dir", _def_vals.output_dir).toString();
    settings->endGroup();
}
//! Returns all configuration variables as "config_t" struct
Config::config_t Config::get()
{
    return _config;
}
//! Stores all variables from "config_t" struct to "config.ini"
void Config::save(config_t config)
{
    _config = config;
    settings->beginGroup("IMAGES");
    settings->setValue("width", _config.images_width);
    settings->setValue("height", _config.images_height);
    settings->setValue("dir", _config.images_dir);
    settings->endGroup();

    settings->beginGroup("MASK");
    settings->setValue("point-size", _config.mask_point_size);
    settings->setValue("scan-direction", _config.mask_scan_direction);
    settings->endGroup();

    settings->beginGroup("OUTPUT");
    settings->setValue("clock-divider", _config.output_clock_divider);
    settings->setValue("pulse", _config.output_pulse);
    settings->setValue("zero", _config.output_zero);
    settings->setValue("one", _config.output_one);
    settings->setValue("stop-pulses", _config.output_stop_pulses);
    settings->setValue("byte-order", _config.output_byte_order);
    settings->setValue("generate-ch-files", _config.output_ch);
    settings->setValue("generate-bin-file", _config.output_bin);
    settings->setValue("dir", _config.output_dir);
    settings->endGroup();
}
