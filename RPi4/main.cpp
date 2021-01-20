#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <errno.h>
#include "raylib.h"

using namespace std;

int uart0_filestream = -1;
int uart_tx_string(string tx_string);

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    Shader sh;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    MaximizeWindow();

    SetTargetFPS(60);
    sh = LoadShader(0, "resources/shaders/glsl120/bloom.fs");

    RenderTexture2D tgt = LoadRenderTexture(screenWidth, screenHeight);

    BeginDrawing();
    ClearBackground(BLACK);
    BeginTextureMode(tgt);
    ClearBackground(BLACK);
    DrawText("Congrats! You created your first window!", 190, 200, 20, SKYBLUE);
    EndTextureMode();

    BeginShaderMode(sh);
    DrawTextureRec(tgt.texture, (Rectangle){0, 0, tgt.texture.width, -tgt.texture.height}, (Vector2){0, 0}, WHITE);
    EndShaderMode();

    //DrawText("Congrats! You created your first window!", 190, 200, 20, SKYBLUE);

    EndDrawing();

    sleep(10);
    UnloadRenderTexture(tgt);
    CloseWindow();

    printf("Hello World!\n");

    uart0_filestream = open("/dev/ttyGS0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart0_filestream == -1)
    {
        printf("Error - Unable to open UART.\n");
        return 0;
    }
    else
        printf("Successfully opened UART!\n");

    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);

    //uart_tx_string("LOOK AROUND YOU!\n\r");

    unsigned char rx_buffer[256];
    int rx_length = 0;
    while (rx_length <= 0)
    {
        rx_length = read(uart0_filestream, (void*)rx_buffer, 255);
    }
    rx_buffer[rx_length] = '\0';
    printf("%i byte(s) read: %s\n\r", rx_length, rx_buffer);

    close(uart0_filestream);

    return 1;
}

int uart_tx_string(string tx_string) {
    if (uart0_filestream == -1)
        return 0;

    write(uart0_filestream, (char*)tx_string.c_str(), tx_string.length());
    return 1;
}
