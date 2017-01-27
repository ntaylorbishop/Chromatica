#pragma once

//UI
#define IS_WINDOWED false

//MEMORY DEBUGGING
#define MEMORY_TRACKING 0 //0 = none, 1 = basic, 2 = verbose 


//LOGGING
#define LIST_MODE 2 //0 = blacklist mode, 1 = whitelist mode
#define MAX_LOG_FILE_HISTORY 20
#define PRINT_TO_OUTPUT_PANE true
#define PRINT_TO_DEV_CONSOLE false
#define LOG_LEVEL 4 //0 none, 1 severe, 2 recoverable, 3 default, 4 all

//ENTITY SYSTEM
const unsigned int MAX_NUM_ENTITIES = 100000;

//PROFILER
#define IS_PROFILER_ENABLED false

//NETWORKING
#define IS_USING_NETWORKING true
#define RUDP_DEBUG_DISPLAY_DISPLAYING false