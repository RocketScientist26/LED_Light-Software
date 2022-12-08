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
        uint32_t crc;
};

#endif // CRC32_H
