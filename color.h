/*
 * Filename: color.h
 * Created on Fri Apr 30 2021 @ 18:48:50
 * Author: Brendan Sadlier
 * Description: Header file containing text color macros for UI Design within
 * the terminal
 * Copyright (c) - 2021 Brendan Sadlier
 * All Rights Reserved
 */
#ifndef COLOR
#define COLOR

// RED
#define COLOR_RED           "\033[31m"
#define COLOR_RED_BOLD      "\033[1;31m"

// GREEN
#define COLOR_GREEN         "\033[32m"
#define COLOR_GREEN_BOLD    "\033[1;32m"

// YELLOW
#define COLOR_YELLOW        "\033[33m"
#define COLOR_YELLOW_BOLD   "\033[1;33m"

// BLUE
#define COLOR_BLUE          "\033[34m"
#define COLOR_BLUE_BOLD     "\033[1;34m"

// MAGENTA
#define COLOR_MAGENTA       "\033[35m"
#define COLOR_MAGENTA_BOLD  "\033[1;35m"

// CYAN
#define COLOR_CYAN          "\033[36m"
#define COLOR_CYAN_BOLD     "\033[1;36m"

// RESET TO DEFAULT
#define COLOR_RESET         "\033[0m"

#endif //COLOR