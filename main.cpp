#include <iostream>
#include <cmath>
#include <string>
#include <unistd.h>

float A, B, C;

float cubeWidth = 10;
int width = 160, height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int backgroundASCIICode = ' ';
int distanceFromCam = 60;
float K1 = 40;

float increamentSpeed = 0.6;

float x,y,z;
float ooz;
int xp, yp;
int idx;

float calculateX(int i, int j, int k) {
    return j * std::sin(A) * std::sin(B) * std::cos(C) - k * std::cos(A) * std::sin(B) * std::cos(C) +
            j * std::cos(A) * std::sin(C) + k * std::sin(A) * std::sin(C) +
            i * std::cos(B) * std::cos(C);
}

float calculateY(int i, int j, int k) {
    return j * std::cos(A) * std::cos(C) + k * std::sin(A) * std::cos(C) -
            j * std::sin(A) * std::sin(B) * std::sin(C) + k * std::cos(A) * std::sin(B) * std::sin(C) -
            i * std::cos(B) * std::sin(C);
}

float calculateZ(int i, int j, int k) {
    return k * std::cos(A) * std::cos(B) - j * std::sin(A) * std::cos(B) +
            i * std::sin(B);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int character) {
    x = calculateX(cubeX, cubeY, cubeZ);
    y = calculateY(cubeX, cubeY, cubeZ);
    z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;
    ooz = 1/z;
    xp = (int)(width/2 + K1 * ooz * x * 2);
    yp = (int)(height/2 + K1 * ooz * y);

    idx = xp + yp * width;
    if(idx >= 0 && idx <  width * height) {
        if(ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = character;
        }
    }
}

int main() {
    printf("\x1b[2J");
    while(true) {
        memset(buffer, backgroundASCIICode, width * height);
        memset(zBuffer, 0, width * height * 4);
        for(float cubeX = -cubeWidth ; cubeX < cubeWidth ; cubeX += increamentSpeed) {
            for(float cubeY = -cubeWidth ; cubeY < cubeWidth ; cubeY += increamentSpeed) {
                calculateForSurface(cubeX, cubeY, -cubeWidth, '#');
            }
        }
        printf("\x1b[H");
        for(int k = 0 ; k < width * height ; k++) {
            putchar(k % width ? buffer[k] : 10);
        }

        A += 0.005;
        B += 0.005;
    }
    return 0;
}