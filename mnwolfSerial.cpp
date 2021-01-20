#include "mnwolfSerial.h"

using namespace std;

int uart0_filestream = -1;
int uart_tx_string(string tx_string);
string strRx;

bool initSerial() {
    uart0_filestream = open("/dev/ttyGS0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart0_filestream == -1)
        return FALSE;
    
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
    
    return TRUE;
}

bool updateSerial() {
  uint8_t rxBytes, rxByte;
  
  rxBytes= read(uart0_filestream, (void*)rxByte, 1);
  if (rxBytes <= 0)
    return FALSE;
  
  switch (rxByte) {
    case '\n':
      break;
      
    case '\r':
      return TRUE;
      break;
      
    default:
      strRx += (unsigned char)rxByte;
  }
  return FALSE;
}

string parseSerial() {
  string strTmp = strRx;
  strRx = "";
  return strTmp;
}
