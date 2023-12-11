#pragma once

#include "../phoneBook/phoneBook.h"

typedef enum Command
{
    exitCommand,
    addEntryCommand,
    printEntriesCommand,
    findNumberByNameCommand,
    findNameByNumberCommand,
    saveToFileCommand
} Command;

Command userInterface(PhoneBook *PhoneBook);

