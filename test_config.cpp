//
// Created by Vitaliy Vorobyov on 2019-04-23.
//

#include "config_reader.h"
#include <iostream>

int main() {

    config config;

    std::cout << config.get_string("infile") << std::endl;
    std::cout << config.get_string("out_by_a") << std::endl;
    std::cout << config.get_string("out_by_n") << std::endl;
    std::cout << config.get_int("threads") << std::endl;

}