#include "ProtoPlasm.h"
#include "App01.h"

int main(int argc, char const** argv)
{
    ijg::ProtoPlasm p(800, 600, "Protobyte App 01", new App01());
    return EXIT_SUCCESS;
}
