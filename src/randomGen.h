#pragma once
#include <random>

class RandomGen
{
public:
    static int intGenerator(int x, int y);
    static float floatGenerator(float x, float y);

private:
    static std::mt19937 random;

};