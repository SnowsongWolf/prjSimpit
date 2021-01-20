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
  int8_t rxBytes;
  char rxByte;

  rxBytes = read(uart0_filestream, &rxByte, sizeof(rxByte));
  //printf("Bytes received: %i ",rxBytes);
  if (rxBytes <= 0)
    return false;

    printf("Bytes received: %i | Data received: %i",rxBytes, (uint8_t)rxByte);

  switch (rxByte) {
    case '\n':
      printf(" | \\n detected.\n\r");
      break;

    case '\r':
      printf(" | \\r detected.\n\r");
      return true;
      break;

    default:
      strRx += rxByte;
      printf(" | Character received: %c",rxByte);
  }
  printf("\n\r");
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
