#include <memory>
#include <ctime>

#include "sync.hpp"

void switchMode()
{
    auto sync = std::make_unique<SyncFactory>();

    int mode;
    std::cout << "\x1b[31m"; std::cin >> mode; std::cout << "\x1b[0m";

    system(screen_clear);
    std::cout << "Process start" << std::endl;
    switch (mode)
    {
    case 1:
        sync->make(new AutoSync())->compute();
        break;

    case 2:
        sync->make(new IOSync())->compute();
        break;

    default:
        std::cout << "Unknow mode!" << std::endl;
    }
    std::cout << "Process end" << std::endl;
}

void clientCode()
{
    std::cout << "You can accept anyone variant of mode work" << std::endl;
    std::cout << "\x1b[31m1)\x1b[0m Auto-mode synchronization two containers" << std::endl;
    std::cout << "\x1b[31m2)\x1b[0m IO-mode synchronization two conatiners " << std::endl;
    std::cout << "Select mode: ";
    switchMode();
}

int main(int agrc, char* argv[]) // param for future time
{
    system("color F0");
    srand(time(NULL));

    clientCode();

    return 0;
}
