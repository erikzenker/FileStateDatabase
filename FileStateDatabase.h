#ifndef FileStateDatabase_H
#define FileStateDatabase_H

#include <string>
#include <sqlite3.h>
#include <map>
#include <utility> /* pair */
#include <vector>
#include <boost/filesystem.hpp>

struct FileState {
std::string path;
unsigned modtime;
unsigned inode;
bool is_dir;

};

enum ModState {FS_DELETE, FS_MODIFY, FS_CREATE};

class FileStateDatabase {
public:
FileStateDatabase(std::string dataBaseName);
~FileStateDatabase();
bool propagateUpdate(std::pair<FileState, ModState> update);
bool insertFileState(FileState fileState);
bool updateFileState(FileState fileState);
bool deleteFileState(FileState fileState);
std::vector<std::pair<FileState, ModState> > getUpdates(std::string rootDirectory);
static std::string modStateToString(ModState modState);
bool resetdb();
private:
bool executeQuery(std::string query, int (*callback)(void*,int,char**,char**) ,void* userData);
FileState createFileState(boost::filesystem::path path);
std::map<int, FileState> createFileStateCache();

// sqlite3_exec callbacks
static int printQueryResult(void *NotUsed, int argc, char **argv, char **azColName);
static int getFileStates(void *fileStates, int argc, char **argv, char **azColName);
  
sqlite3 *mDataBase;

};

#endif /* FileStateDatabase_H */
