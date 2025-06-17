#include <stdio.h>
#include "xafetylib.h"

int main(int argc, char* argv[])
{
    if (argc == 0) {
        printf("No arguments found.\nTry using xafety sniff");
        return 1;
    }
    if (argv[0] == "sniff")
    {
        sniff();
        return 0;
    }
    else if (argv[0] == "")
    {
        return 0;
    }
}

