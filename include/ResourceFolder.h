#ifndef RESSOURCESDIRECTORY_H 
#define RESSOURCESDIRECTORY_H 

#include <string>
#include <vector>

std::string GetRPath(void);
std::string GetApplicationSupportFolderCString(void);

std::vector<std::string> GetSaveFolderContents(void);
std::vector<std::string> GetSaves(void);

void CreateApplicationSupportFolder(void);

void makeOSXDirectory(std::string dir);

std::vector<std::string> getFolderContents(std::string folder);
std::vector<std::string> getFolderContentsByFileExtension(std::string folder, const char * fileExtension);

#endif
