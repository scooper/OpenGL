#pragma once
#include <iostream>
#include <glad/glad.h>

#define ASSERT(x) if (!(x)) __debugbreak();

class ErrorHandling
{
public:
    static void GLErrorMessageInit();
};