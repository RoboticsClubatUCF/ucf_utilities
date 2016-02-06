#include <byte_buffer.h>

ByteBuffer::ByteBuffer()
{
}

ByteBuffer::ByteBuffer(std::vector<char> data) : buffer(data)
{
}

ByteBuffer::~ByteBuffer()
{

}

void ByteBuffer::appendByte(char data)
{
    buffer.push_back(data);
}

void ByteBuffer::prependByte(char data)
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

char ByteBuffer::peekNextByte() const
{
    char value = buffer[0];
    return value;
}
    
char ByteBuffer::removeNextByte()
{
    char value = buffer[0];
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

const char* ByteBuffer::getDataPointer() const
{
    return &buffer[0];
}

char ByteBuffer::operator[](const int index)
{
    return buffer[index];
}
