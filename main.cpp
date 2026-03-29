#include <iostream>
#include "logic/Config.h"

int main() {
    Config config("config.csv");
    config.run();
}