#include "Core.h"

using namespace tge;

int main(int argc, char* argv[])
{
    Core * C = new Core();

    C->init(argc, argv);
    C->run();

    return C->getExitCode();
}
