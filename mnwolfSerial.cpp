#include "mnwolfSerial.h"

using namespace std;

int uart0_filestream = -1;
int uart_tx_string(string tx_string);
string strRx;

bool initSerial() {
    uart0_filestream = open("/dev/ttyGS0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart0_filestream == -1)
        return false;

    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);

    return true;
}

bool updateSerial() {
  uint8_t rxBytes, rxByte;

  rxBytes= read(uart0_filestream, (void*)rxByte, 1);
  if (rxBytes <= 0)
    return false;

  switch (rxByte) {
    case '\n':
      break;

    case '\r':
      return true;
      break;

    default:
      strRx += (unsigned char)rxByte;
  }
  return false;
}

string parseSerial() {
  string strTmp = strRx;
  strRx = "";
  return strTmp;
}

bool txSerial(string strTx) {
    if (uart0_filestream == -1)
        return false;

    write(uart0_filestream, (char*)strTx.c_str(), strTx.length());
    return true;
}

bool closeSerial() {
    if (uart0_filestream == -1)
        return false;

    close(uart0_filestream);
    return true;
}
