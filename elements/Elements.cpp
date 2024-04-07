#include "Elements.h"

int getOne()
{
    return 1;
}
Elements::Basis::Basis() {}

Elements::Button::Button(const char *pText) : Basis()
{
    text = pText;
}
void Elements::Button::executeFunction()
{
    action("Executed");
}
Elements::Button::~Button()
{
    action = nullptr;
}
Elements::Basis::~Basis()
{
}