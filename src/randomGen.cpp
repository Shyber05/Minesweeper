#include "randomGen.h"
#include <ctime>

std::mt19937 RandomGen::random(time(0));

int RandomGen::intGenerator(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random);
}

float RandomGen::floatGenerator(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(random);
}

