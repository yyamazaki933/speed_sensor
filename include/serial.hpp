#include <string>

class CustomSerial
{
private:
    int fd_;
    termios oldtio_;

    CustomSerial();
    ~CustomSerial();

public:
    int openPort(std::string port, int baudRate);
    std::string readMsg();
    int writeMsg(const std::string& data);
    void closePort();
};
