#include <iostream>
#include <cmath>

float A, B, C;

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

int main() {

    std::cout << "Hello World" << std::endl;

    return 0;
}