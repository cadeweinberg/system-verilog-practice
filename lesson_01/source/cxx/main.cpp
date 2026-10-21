
/*
 * @file main.cpp
 *
 * @brief the main cpp file for lesson_01
 *
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <memory>

#include <verilated.h>

#include "Vtop.h"

int main(int argc, char **argv) {
    const std::unique_ptr<VerilatedContext> vctx = std::make_unique<VerilatedContext>();

    vctx->commandArgs(argc, argv);

    const std::unique_ptr<Vtop> top = std::make_unique<Vtop>(vctx.get(), "TOP");

    while (!vctx->gotFinish()) {
        top->eval();
    }

    top->final();

    return 0;
}


