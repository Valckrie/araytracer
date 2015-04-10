#include "include/colour.h"

Colour::Colour()
{
    red   = 0.0;
    green = 0.0;
    blue  = 0.0;
    alpha = 0.0;
}

void Colour::clear(void)
{
    red   = 0.0;
    green = 0.0;
    blue  = 0.0;
    alpha = 0.0;
}

void Colour::set(float pred, float pgreen, float pblue, float palpha)
{
    red   = pred;
    green = pgreen;
    blue  = pblue;
    alpha = palpha;
}

float Colour::getRed(void)
{
    return red;
}

float Colour::getGreen(void)
{
    return green;
}

float Colour::getBlue(void)
{
    return blue;
}

float Colour::getAlpha(void)
{
    return alpha;
}

void Colour::add(Colour c) {
    red += c.red;
    green += c.green;
    blue += c.blue;
}

void Colour::multiply(Colour c) {
    red *= c.red;
    green *= c.green;
    blue *= c.blue;
}

void Colour::multiply(float scalar) {
    red *= scalar;
    green *= scalar;
    blue *= scalar;
}

Colour Colour::divide(float scalar) {
    red = red / scalar;
    green = green / scalar;
    blue = blue / scalar;
}

void Colour::scaleLuminance(float scalar) {
    red = red * scalar;
    green = green * scalar;
    blue = blue * scalar;
}