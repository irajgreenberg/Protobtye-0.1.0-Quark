#include "ProtoPlasm.h"
#include "Cephalopod_Dev_01.h"

int main(int argc, char const** argv)
{
    ijg::ProtoPlasm p(800, 600, "Protobyte App 02", new Cephalopod_Dev_01());
    return EXIT_SUCCESS;
}
