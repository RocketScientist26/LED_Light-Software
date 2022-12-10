//! Class for generating STM32 compatible 32bit CRC
#ifndef CRC32_H
#define CRC32_H

#include <QObject>

class Crc32 : public QObject
{
    Q_OBJECT
    public:
        explicit Crc32(uint32_t *data, uint32_t length);
        uint32_t getCrc();

    private:
        //Variable where we store generated CRC from "*data"
        uint32_t crc;
};

#endif // CRC32_H
