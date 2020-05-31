#include <iostream>
#include <stdlib.h>
#include "config.h"

#ifdef USE_MYMATH
    #include "mathFunc/mathFunc.h"
#else
    #include <math.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3){
        //print the version info
        printf("%s version %d.%d\n",
              argv[0],
              Demo_VERSION_MAJOR,
              Demo_VERSION_MINOR);
        printf("Usage: %s base exponent \n", argv[0]);
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
#ifdef USE_MYMATH
    cout<<"Now we use our own math lib."<<endl;
    double result = power(base, exponent);
#else
    cout<<"Now we use the std math lib."<<endl;
    double result = pow(base, exponent);
#endif // USE_MYMATH

    printf("%g ^ %d is %g\n", base, exponent, result);
    return 0;
}
