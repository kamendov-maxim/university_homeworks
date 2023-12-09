#pragma once

typedef enum Command
{
    exitCommand,
    addEntryCommand,
    printEntriesCommand,
    findNumberByNameCommand,
    findNameByNumberCommand,
    saveToFileCommand
} Command;

Command userInterface(void);
