# abj_vcs - Basic Version Control System

## Overview

**abj_vcs** is my basic implementation of a version control system like git. 

## Features

- **Create** new files and initialize their version history.
- **Read** the current content of any file.
- **Insert** new content, creating new versions if the current version is a snapshot.
- **Update** the content of the current version.
- **Snapshot** the current version with a message.
- **Rollback** to previous versions by version ID or stepwise.
- **History**: View the full version history of a file.
- **Recent Files**: List files sorted by last modification time.
- **Biggest Trees**: List files with the most versions.
- **Custom HashMap** (`str_map`, `int_map`) and Heap (`maxHeap`) implementations.

## File Structure

```
.
├── main.cpp                       # Main code
├── custom_classes.hpp             # Class and structs declarations
├── custom_classes_implementation.cpp # Class and structs implementations
├── Makefile                       # Build instructions
```

## Build Instructions

1. **Requirements:**  
   - C++17 or newer
   - GNU Make

2. **Build:**  
   Open a terminal in the project directory and run:
   ```
   sudo apt-get update
   sudo apt-get install build-essential
   make
   chmod +x abj_vcs
   ```
   This will produce an executable named `abj_vcs`.
   <!-- Run it with
   ```
   ./abj_vcs
   ``` -->

## Usage

Run the program:
```
./abj_vcs
```

You can enter the following commands interactively:

- `CREATE <filename>`: Create a new file.
- `READ <filename>`: Display the current content of a file.
- `INSERT <filename> <content>`: Append content to the current version.
- `UPDATE <filename> <content>`: Replace content in the current version.
- `SNAPSHOT <filename> <message>`: Mark the current version as a snapshot.
- `ROLLBACK <filename> [version_id]`: Roll back to a previous version (or to the parent of current active_version).
- `HISTORY <filename>`: Show the version history.
- `RECENT_FILES <n>`: Show the `n` most recently modified files.(not specifying n will cause weird behaviour)
- `BIGGEST_TREES <n>`: Show the `n` files with the most versions.(not specifying n will cause weird behaviour)
- `EXIT`: Clean up and exit.

## Data Structures

- **str_map**: Custom hash map for mapping filenames to `File*`(implemented by using a custom hashing function, big enough vector, and nested vectors for collision handling.).
- **int_map**: Custom hash map for mapping version IDs to `TreeNode*`(implemented using basic vectors since version ids are not that large and serially assigned starting from 0).
- **maxHeap**: Custom max heap for sorting files by time or version count.

## Notes and Assumptions

- The hash maps use fixed-size buckets for simplicity and performance.(int_map limited to 10^6 entries)
- No output is printed on *successful* command execution(like on calling CREATE, INSERT UPDATE)
- it is assumed that inputs might run over separate lines, like
```
CREATE
file_name_1
```
- but not for the case of ROLLBACK when there is an optional parameter. Thus ROLLBACK must be called in a single line
```ROLLBACK A 2``` (rolls back file with name 'A' to version 2 (if exists, else prints an error))
- Error is printed:
    - if an invalid command is entered
    - if you try to modify a non existent file
    - if you try to recreate an existing file
    - if you try to snapshot a file which is already a snapshot(without making any further changes)
    - if you try to rollback to a non existent version_id
    - if you ask for k recent files and k is more than the total number of files created

## Author

Abhijai Chugh
