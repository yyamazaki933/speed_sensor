#include <string>
#include <termios.h>

class CustomSerial
{
private:
    int fd_;
    struct termios oldtio_;

public:
    CustomSerial();
    ~CustomSerial();
    int openPort(std::string port, int baudRate);
    std::string readMsg();
    int writeMsg(const std::string& data);
    void closePort();
};
