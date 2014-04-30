#include <FileStateDatabase.h>
#include <FileState.h>
#include <iostream>
#include <map>
#include <string>
#include <boost/filesystem.hpp>

int main(int argc, char **argv){

  if(argc <= 1){
    std::cout << "Usage: ./a.out /dir/to/generate/filestates" << std::endl;
    return 1;
  }

  boost::filesystem::path dir(argv[1]);
  FileStateDatabase fileStateDatabase(std::vector<std::string>(), "my_filestate_database", dir);

  //Get updates since last getUpdates
  std::vector<std::pair<FileState, ModState> > updates = fileStateDatabase.updates();

  for(auto update: updates){
    FileState fs = update.first;
    ModState ms  = update.second;
    std::cout << "Update: " << fs.path.string() << " " << fs.modtime << " " << FileStateDatabase::modStateToString(ms) << std::endl;

    // Propagate modstate into database
    fileStateDatabase.propagateUpdate(update);
  }

  return 0;

  
}
