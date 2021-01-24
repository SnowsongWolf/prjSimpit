#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <errno.h>

using namespace std;

bool initSerial();
bool updateSerial();
std::string parseSerial();
bool txSerial(string strTx);
bool closeSerial();
