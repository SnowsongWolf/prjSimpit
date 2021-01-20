/*
 * simpit.c
 *
 *  Created on: Jan 10, 2021
 *      Author: Snow
 */

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include "simpit.h"

int ADDCALL _hello() {
	HANDLE hComm;
	char txBuffer[256];
	DWORD txBytesWritten;
	BOOLEAN boolRVal;

	DCB dcb;
	BOOL fSuccess;

	hComm = CreateFileA("\\\\.\\COM4", GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);
	if (hComm == INVALID_HANDLE_VALUE)
		return 2;

	//SecureZeroMemory(&dcb, sizeof(DCB));
	dcb.DCBlength = sizeof(DCB);

	fSuccess = GetCommState(hComm, &dcb);
	if (!fSuccess)
	{
		CloseHandle(hComm);
		return 5;
	}

	dcb.BaudRate = CBR_115200;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;

	fSuccess = SetCommState(hComm, &dcb);
	if (!fSuccess)
	{
		CloseHandle(hComm);
		return 3;
	}

	strcpy(txBuffer, "Look around you.  Look around you.  Just look around you.");

	boolRVal = WriteFile(hComm, txBuffer, strlen(txBuffer), &txBytesWritten, NULL);

	CloseHandle(hComm);
	if (boolRVal)
		return 1;
	return 4;
}

