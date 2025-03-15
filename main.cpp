#include <cmath>
#include <cstdio>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm> 


int main() {
    constexpr int width = 160;
    constexpr int height = 44;
    const int bufferSize = width * height;

    // Create buffers for depth and ASCII characters
    std::vector<float> zBuffer(bufferSize, 0.0f);
    std::vector<char> buffer(bufferSize, '.');

    float A = 0.0f, B = 0.0f, C = 0.0f;    // Rotation angles
    float cubeWidth = 20.0f;
    const int distanceFromCam = 100;
    float horizontalOffset = 0.0f;
    const float K1 = 40.0f;                // controls size
    const float incrementSpeed = 0.6f;

    // Clear screen 
    std::printf("\x1b[2J");

    while (true) {
        std::fill(buffer.begin(), buffer.end(), '.');
        std::fill(zBuffer.begin(), zBuffer.end(), 0.0f);

        auto calculateX = [&](float i, float j, float k) -> float {
            return j * std::sin(A) * std::sin(B) * std::cos(C) -
                k * std::cos(A) * std::sin(B) * std::cos(C) +
                j * std::cos(A) * std::sin(C) +
                k * std::sin(A) * std::sin(C) +
                i * std::cos(B) * std::cos(C);
            };

        auto calculateY = [&](float i, float j, float k) -> float {
            return j * std::cos(A) * std::cos(C) +
                k * std::sin(A) * std::cos(C) -
                j * std::sin(A) * std::sin(B) * std::sin(C) +
                k * std::cos(A) * std::sin(B) * std::sin(C) -
                i * std::cos(B) * std::sin(C);
            };

        auto calculateZ = [&](float i, float j, float k) -> float {
            return k * std::cos(A) * std::cos(B) -
                j * std::sin(A) * std::cos(B) +
                i * std::sin(B);
            };


        auto calculateForSurface = [&](float cubeX, float cubeY, float cubeZ, char ch) {
 
            float x = calculateX(cubeX, cubeY, cubeZ);
            float y = calculateY(cubeX, cubeY, cubeZ);
            float z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;
            float ooz = 1.0f / z;  // depth scaling

            int xp = static_cast<int>(width / 2 + horizontalOffset + K1 * ooz * x * 2);
            int yp = static_cast<int>(height / 2 + K1 * ooz * y);
            int idx = xp + yp * width;

            if (idx >= 0 && idx < bufferSize && ooz > zBuffer[idx]) {
                zBuffer[idx] = ooz;
                buffer[idx] = ch;
            }
            };

        // First cube 
        cubeWidth = 20.0f;
        horizontalOffset = -2 * cubeWidth;
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
                calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
                calculateForSurface(cubeWidth, cubeY, cubeX, '$');
                calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
                calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
                calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
                calculateForSurface(cubeX, cubeWidth, cubeY, '+');
            }
        }

        // Second cube 
        cubeWidth = 10.0f;
        horizontalOffset = cubeWidth;
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
                calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
                calculateForSurface(cubeWidth, cubeY, cubeX, '$');
                calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
                calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
                calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
                calculateForSurface(cubeX, cubeWidth, cubeY, '+');
            }
        }

        // Third cube 
        cubeWidth = 5.0f;
        horizontalOffset = 8 * cubeWidth;
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
                calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
                calculateForSurface(cubeWidth, cubeY, cubeX, '$');
                calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
                calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
                calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
                calculateForSurface(cubeX, cubeWidth, cubeY, '+');
            }
        }

        // Move cursor to top-left
        std::printf("\x1b[H");
        for (size_t i = 0; i < buffer.size(); ++i) {
            std::putchar((i % width == 0) ? '\n' : buffer[i]);
        }

        A += 0.05f;
        B += 0.05f;
        C += 0.01f;

        // ~16ms per frame
        std::this_thread::sleep_for(std::chrono::microseconds(16000));
    }

    return 0;
}
