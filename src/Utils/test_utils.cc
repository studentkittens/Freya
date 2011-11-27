#include <stdio.h>
#include "Utils.hh"
#include <time.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  //  int a = gettimeofday(); 
    printf("%s\n",Utils::seconds_to_duration(98888888).c_str());
    printf("%s\n",Utils::seconds_to_timestamp(98888888).c_str());
    return EXIT_SUCCESS;
}
