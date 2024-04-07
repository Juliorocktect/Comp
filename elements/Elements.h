#pragma once
#include <cstdlib>
int getOne();

namespace Elements
{
    class Basis
    {
    private:
        Basis *parent;

    public:
        int width,
            height,
            xCoord,
            yCoord,
            zPosition,
            backgroundColor,
            color,
            marginTop,
            marginLeft,
            marginBottom,
            marginRight,
            paddingTop,
            paddingBottom,
            paddingLeft,
            paddingRight;

        const char *id;
        Basis();
        ~Basis();
        void before(Basis *element);
        void after(Basis *element);
    };
    class Text : public Basis
    {
    public:
        const char *text;

    private:
    };
    class Button : public Basis
    {
    public:
        Button(const char *text);
        ~Button();
        const char *text;
        void (*action)(const char *text);
        void executeFunction();
    };
};