#include <byte_buffer.h>

ByteBuffer::ByteBuffer()
{
}

ByteBuffer::ByteBuffer(int size) : buffer(size, 0)
{
}

ByteBuffer::ByteBuffer(std::vector<unsigned char> data) : buffer(data)
{
}

ByteBuffer::~ByteBuffer()
{

}

void ByteBuffer::appendByte(unsigned char data)
{
    buffer.push_back(data);
}

void ByteBuffer::prependByte(unsigned char data)
{
    buffer.insert(buffer.begin(), data);
}

void ByteBuffer::appendByteBuffer(ByteBuffer buf)
{
    for (int i = 0; i < buf.getSize(); i++)
    {
        appendByte(buf[i]);
    }
}

unsigned char ByteBuffer::peekNextByte() const
{
    unsigned char value = buffer[0];
    return value;
}
    
unsigned char ByteBuffer::removeNextByte()
{
    unsigned char value = buffer[0];
    buffer.erase(buffer.begin());
    return value;
}

void ByteBuffer::clear()
{
    buffer.clear();
}

int ByteBuffer::getSize() const
{
    return buffer.size();
}

bool ByteBuffer::isEmpty() const
{
    return buffer.empty();
}

const unsigned char* ByteBuffer::getDataPointer() const
{
    return &buffer[0];
}

unsigned char ByteBuffer::operator[](const int index)
{
    return buffer[index];
}
