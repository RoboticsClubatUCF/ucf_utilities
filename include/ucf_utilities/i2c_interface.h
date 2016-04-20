#ifndef I2C_Interface_H
#define I2C_Interface_H

#include <byte_buffer.h>

////////////////////////////////////////////////////////////////////////////////
/// \brief Class providing functionality for interfacing to an I2C bus.
///
/// This class provides basic functionality required for full interface to an
/// I2C bus.  It is indended to be composed with specific device drivers to
/// implement their I2C interface.
///
////////////////////////////////////////////////////////////////////////////////
class I2C_Interface 
{
public:
    //////////////////////////////////////////////////////////////////////////////// 
    /// \brief Constructs a new master I2C_Interface.
    ///
    /// \param bus      The I2C bus to use.
    /// \param address  The slave address of the device to communicate with. 
    //////////////////////////////////////////////////////////////////////////////// 
    I2C_Interface(int bus, char address);

    //////////////////////////////////////////////////////////////////////////////// 
    /// \brief Default I2C_Interface destructor.
    ///
    //////////////////////////////////////////////////////////////////////////////// 
    ~I2C_Interface();
    
    //////////////////////////////////////////////////////////////////////////////// 
    /// \brief Open the I2C interface to the slave device.
    ///
    ////////////////////////////////////////////////////////////////////////////////  
    void openDevice();

    //////////////////////////////////////////////////////////////////////////////// 
    /// \brief Close the I2C interface to the slave device.
    ///
    //////////////////////////////////////////////////////////////////////////////// 
    void closeDevice();

    //////////////////////////////////////////////////////////////////////////////// 
    /// \brief Read a single register containing data of a specified size.
    /// 
    /// \param reg    The register address to read.
    /// \param size   The number of bytes contained in the register.
    //////////////////////////////////////////////////////////////////////////////// 
    ByteBuffer readRegister(int reg, int size) const;

    //////////////////////////////////////////////////////////////////////////////// 
    /// \brief Read a series of registers from the slave device.
    /// 
    /// Reads from the specified register through some number of registers specified
    /// in the function call.  Note that this function does not depend on the 
    /// slave device auto-incrementing an internal register pointer as it
    /// sends a new read request for each register.
    ///
    /// \param reg    The register address to read first.
    /// \param size   The number of bytes contained in each register.
    /// \param count  The number of registers to read in succession.
    //////////////////////////////////////////////////////////////////////////////// 
    ByteBuffer readSuccessiveRegisters(int reg, int size, int count) const;

    ////////////////////////////////////////////////////////////////////////////////
    /// \brief Read a bulk set of data from the slave device.
    ///
    /// Support for bulk reads from devices that support their own internal
    /// automatically incrementing register pointers.  Reads the number of bytes
    /// supplied from the register given as a starting point.  It is the caller's
    /// responsibility to then parse and sort this data.
    ///
    /// \param reg    The register address to start the read from.
    /// \param count  The number of bytes to read.
    ////////////////////////////////////////////////////////////////////////////////
    ByteBuffer readBulkBytes(int reg, int count) const;

    //////////////////////////////////////////////////////////////////////////////// 
    /// \brief Write a single byte to the specified register.
    ///
    /// \param reg    The register address to write to.
    /// \param data   The byte of data to write.
    //////////////////////////////////////////////////////////////////////////////// 
    void writeRegisterByte(int reg, char data) const;

    //////////////////////////////////////////////////////////////////////////////// 
    /// \brief Write the data contained in a ByteBuffer to a target register.
    ///
    /// This function provides a convenient way to write any desired data block
    /// to a single register via use of the ByteBuffer class. 
    ///
    /// \param reg    The register address to write to.
    /// \param buffer The data to write to the register.
    //////////////////////////////////////////////////////////////////////////////// 
    void writeRegisterByteBuffer(int reg, ByteBuffer buffer) const;
    
    //////////////////////////////////////////////////////////////////////////////// 
    /// \brief Write the contents of a ByteBuffer to the I2C bus.
    /// 
    /// This function provides raw bus write capability to the I2C bus. This
    /// has limited practical application as there is then no access to any I2C
    /// handshaking, acknowledgement, clock stretching, etc.
    ///
    /// \param buffer The data to write to the bus.
    //////////////////////////////////////////////////////////////////////////////// 
    void writeByteBuffer(ByteBuffer buffer) const;
private:
    int file_;
    char address_;
    int bus_number_;
};

#endif
