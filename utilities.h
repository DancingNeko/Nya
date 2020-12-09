#ifndef UTILITY_H
#define UTILITY_H

#ifdef SPDLOG
#pragma warning(disable : 4101)
#include "includes/spdlog/spdlog.h"
#include "includes\spdlog\sinks\basic_file_sink.h"

#define LOGNAME ("spdlog")
#endif

void utilitiesInitialize(char const * fp);
void utilitiesUninitializePrint();

void printPuzzle(int * puzzle, int dim);

#if defined(SPDLOG)
#define LOGINFO spdlog::get(LOGNAME)->info
#else
#define LOGINFO(x, ...)
#endif

#endif // UTILITY_H
