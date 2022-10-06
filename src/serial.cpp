#include "serial.hpp"
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

CustomSerial::CustomSerial() {}

CustomSerial::~CustomSerial() { this->closePort(); }

int CustomSerial::openPort(std::string port, int baudRate)
{
	fd_ = open(port.c_str(), O_RDWR | O_NOCTTY);
	if (fd_ < 0)
    {
		return -1;
	}

    tcgetattr(fd_, &oldtio_);

    struct termios newtio;
    memset(&newtio, 0, sizeof(newtio));

    newtio.c_cflag = CS8 | CLOCAL | CREAD;  
    newtio.c_cc[VTIME] = 0;
    newtio.c_lflag = ICANON;
    newtio.c_iflag = IGNPAR | ICRNL;  
  
    cfsetispeed(&newtio, baudRate);  
    cfsetospeed(&newtio, baudRate);
    
    tcsetattr(fd_, TCSANOW, &newtio);  

    return 0;
}

std::string CustomSerial::readMsg()
{
	unsigned char* buffer = new unsigned char[1024];
    
    int size = read(fd_, buffer, 1024);
	if (size <= 0)
    {
        delete[] buffer;
		return "";
	}

    std::string data((char*)buffer, sizeof(buffer));
    delete[] buffer;
    return data;
}

int CustomSerial::writeMsg(const std::string& data)
{
	int size = (int)data.size() + 1;
	unsigned char* buffer = new unsigned char[size];
	
    buffer = (unsigned char*)data.data();
	size = write(fd_, buffer, size);
    
    delete[] buffer;
    return size;
}

void CustomSerial::closePort()
{
	tcsetattr(fd_, TCSANOW, &oldtio_);
	close(fd_);
}