#include <iostream>
#include <string.h>

#include <fmt/core.h>
#include <fmt/color.h>

struct Arg
{
    const char *data;
    size_t len;
};

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fmt::print(stderr, "Usage: {} <src> <comp 0> [comp 1] [comp 2] [comp N]\n", argv[0]);
        return 1;
    }

    const int argsLenght = argc - 1;
    Arg *args = new Arg[argsLenght];

    const Arg *minArg = args;

    for (int i = 0; i < argsLenght; i++)
    {
        args[i].data = argv[i + 1];
        args[i].len = strlen(argv[i + 1]);

        if (minArg->len > args[i].len)
            minArg = args + i;
    }

    for (size_t i = 0; i < minArg->len; i++)
    {
        fmt::print("{0} ({0:#04x})", args[0].data[i]);
        for (const Arg *arg = args + 1; arg - args < argsLenght; arg++)
        {
            if (arg->data[i] == args[0].data[i])
                fmt::print("\t{0} ({0:#04x})", arg->data[i]);
            else
                fmt::print(fmt::fg(fmt::color::red), "\t{0} ({0:#04x})", arg->data[i]);
        }
        fmt::print("\n");
    }

    delete[] args;
    return 0;
}
