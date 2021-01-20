#ifndef MNWOLF_SERIAL
#define MNWOLF_SERIAL

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <errno.h>

bool initSerial();
bool updateSerial();
string parseSerial();

#endif
