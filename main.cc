#include <FileStateDatabase.h>
#include <iostream>

int main(){

  std::string dir("/home/erik/Documents/knowledgebase/");
  FileStateDatabase fileStateDatabase("my_filestate_database");

  // Get updates since last getUpdates
  std::vector<std::pair<FileState, ModState> > updates = fileStateDatabase.getUpdates(dir);

  for(auto update = updates.begin(); update != updates.end(); ++update){
    FileState fs = update->first;
    ModState ms  = update->second;
    std::cout << "Update: " << fs.path << " " << fs.modtime << " " << FileStateDatabase::modStateToString(ms) << std::endl;

    // Propagate modstate into database
    fileStateDatabase.propagateUpdate(*update);
  }

  return 0;
}
