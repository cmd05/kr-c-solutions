#include <stdio.h>

int main() {
    float fahr = 10.312122, celsius = 20.673191;   
    // printf("%3d %6d\n", fahr, celsius); // specify width using %<width>d, (right justified)
    printf("%3.0f %6.4f\n", fahr, celsius); // specify width using %<width>d, (right justified)
}