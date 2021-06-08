#ifndef __NO_SYSTEM_INIT
extern "C" void SystemInit()
{}
#endif

int main()
{
    for(;;) {}

    return 0; // suppress compiler warnings
}