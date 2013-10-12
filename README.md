FileStateDatabase
=================

A C++ class, that helps you to save the state of files in a sql database.

## Description ##


## Build ##
   + include FileStateDatabase.h
   + compile with -lsqlite3 -lboost_system -lboost_filesystem -std=c++11 
   + example: g++ main.cc FileStateDatabase.cc -I . -lsqlite3 -lboost_system -lboost_filesystem -std=c++11

## Example ##
Small example explains how to use FileStateDatabase.
```c++

#include <FileStateDatabase.h>
#include <iostream>

int main(int argc, char **argv){

  if(argc <= 1){
    std::cout << "Usage: ./a.out /dir/to/generate/filestates" << std::endl;
    return 1;
  }

  boost::filesystem::path dir(argv[1]);
  FileStateDatabase fileStateDatabase("my_filestate_database", dir);

  // Get updates since last getUpdates
  std::vector<std::pair<FileState, ModState> > updates = fileStateDatabase.getUpdates();

  for(auto update = updates.begin(); update != updates.end(); ++update){
    FileState fs = update->first;
    ModState ms  = update->second;
    std::cout << "Update: " << fs.path << " " << fs.modtime << " " << FileStateDatabase::modStateToString(ms) << std::endl;

    // Propagate modstate into database
    fileStateDatabase.propagateUpdate(*update);
  }

  return 0;
}

```


## Dependencies ##
 + boost
 + c++11
 + sqlite3

## Copyrigth
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.  
This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the extent permitted by law.

## Author ##
Written by Erik Zenker (erikzenker@hotmail.com)
