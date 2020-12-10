
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>
#include "utilities.h"

#ifdef SPDLOG
#include "spdlog/sinks/stdout_color_sinks.h"
#endif

using namespace std;

#ifndef SPDLOG
static streambuf* s_recordedBuf = nullptr;
static ofstream s_out;
#endif

static bool s_initialized = false;

void utilitiesInitialize(char const * fp) {
    if (fp == nullptr)
        s_initialized = false;
    else
        s_initialized = true;
#ifndef SPDLOG
    if (!s_initialized)
        return;
    // save cout buffer
    s_out.open(fp);
    if (s_recordedBuf == nullptr) {
        s_recordedBuf = cout.rdbuf();
    }
    cout.rdbuf(s_out.rdbuf());
#else
    if (!s_initialized) {
        auto console = spdlog::stdout_color_mt(LOGNAME);
    }
    else {
        spdlog::basic_logger_mt(LOGNAME, fp);
        spdlog::get(LOGNAME)->info("Initialized ... ");
        spdlog::get(LOGNAME)->flush();
    }
#endif
}

void utilitiesUninitializePrint() {
    if (!s_initialized)
        return;
    s_initialized = false;
#ifndef SPDLOG
    s_out.close();
    if (s_recordedBuf != nullptr) {
        cout.rdbuf(s_recordedBuf);
    }
#else
    spdlog::get(LOGNAME)->info("Uninitialized ... ");
    spdlog::get(LOGNAME)->flush();
#endif
}

void printPuzzle(int* tempPuzzle, int dim) {
    if (!s_initialized)
        return;
#ifndef SPDLOG
    cout << "\npuzzle: " << endl;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << tempPuzzle[i * dim + j]<<", ";
        }
        cout << endl;
    }
#else
    spdlog::get(LOGNAME)->info("puzzle: ");
    stringstream ss;
    auto old = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    cout << endl;
    for (int i = 0; i < dim; i++) {
        std::string temp;
        for (int j = 0; j < dim; j++) {
            cout << tempPuzzle[i * dim + j]<<", ";
        }
        cout << endl;
    }
    cout.rdbuf(old);
    auto buf = ss.str();
    spdlog::get(LOGNAME)->info(buf);
    spdlog::get(LOGNAME)->flush();
#endif
}

