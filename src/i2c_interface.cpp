#include <i2c_interface.h>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

I2C_Interface::I2C_Interface(int bus_number, char address) :
    bus_number_(bus_number), address_(address)
{
}
    
I2C_Interface::~I2C_Interface()
{
    closeDevice();
}

void I2C_Interface::openDevice()
{
    switch(bus_number_)
    {
        case 0:
            printf("Bus 0 is not implemented on any club used devices.\n");
            break;
        case 1:
            file_ = open("/dev/i2c-1", O_RDWR);
            break;
        case 2:
            file_ = open("/dev/i2c-2", O_RDWR);
            break;
        default:
            break;
    }

    if((ioctl(file_, I2C_SLAVE, address_)) < 0)
    {
        printf("Unable to connect to device\n");
    }
}

void I2C_Interface::closeDevice()
{
    close(file_);
}

ByteBuffer I2C_Interface::readRegister(int reg, int size) const
{
    ByteBuffer return_buffer;

    // Temporary buffer for both register location reset and read data.
    char* temp_buffer = new char[size];

    // Reset read address
    temp_buffer[0] = (char)reg;
    if ((write(file_, temp_buffer, 1)) != 1)
    {
        printf("I2C device failed to write new read address\n");
    }

    // Read the data from the device.
    int read_count = read(file_, temp_buffer, size);
    if (read_count != size)
    {
        printf("I2C bytes read does not match expected size\n");
    }

    // Add all read bytes into the return structure.
    for (int i = 0; i < read_count; i++)
    {
        return_buffer.appendByte(temp_buffer[i]);
    }

    delete [] temp_buffer;

    return return_buffer;
}

ByteBuffer I2C_Interface::readSuccessiveRegisters(int reg, int size, int count) const
{
    ByteBuffer return_buffer;
    ByteBuffer temp_buffer;

    for (int i = 0; i < count; i++)
    {
        temp_buffer = readRegister(reg+i, size);
        return_buffer.appendByteBuffer(temp_buffer);
    }

    return return_buffer;
}

ByteBuffer I2C_Interface::readBulkBytes(int reg, int count) const
{
    ByteBuffer return_buffer;

    char* temp_buffer = new char[count];
    int read_count = read(file_, temp_buffer, count);
    if (read_count != count)
    {
        printf("I2C bulk read does not match expected count\n");
    }

    for (int i = 0; i < read_count; i++)
    {
        return_buffer.appendByte(temp_buffer[i]);
    }

    delete [] temp_buffer;

    return return_buffer;
}

void I2C_Interface::writeRegisterByte(int reg, char data) const
{
    char temp_buffer[2] = {(char)reg, data};
    int write_count = write(file_, temp_buffer, 2);
    if (write_count != 2)
    {
        printf("I2C bytes written does not match expected size\n");
    }
}

void I2C_Interface::writeRegisterByteBuffer(int reg, ByteBuffer buffer) const
{
    // Push the register address to the front of the buffer for communications.
    buffer.prependByte(reg);
    int write_count = write(file_, buffer.getDataPointer(), buffer.getSize());
    if (write_count != buffer.getSize())
    {
        printf("I2C bytes written does not match expected size\n");
    }
    // Remove the register address that was added for communication.
    buffer.removeNextByte();
}

void I2C_Interface::writeByteBuffer(ByteBuffer buffer) const
{
    int write_count = write(file_, buffer.getDataPointer(), buffer.getSize());
    if (write_count != buffer.getSize())
    {
        printf("I2C bytes written does not match expected size\n");
    }
}


