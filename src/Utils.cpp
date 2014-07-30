#include <iostream>
#include <fstream>

#include "Utils.h"

#include <dirent.h>

#include <SFML/System.hpp>

#ifdef SFML_SYSTEM_WINDOWS
  #ifdef VISUAL_STUDIO_BUILD
    #include "direct.h"
  #endif
#elif defined(SFML_SYSTEM_MACOS)
    #include "ResourceFolder.h"
#endif

#include <sys/stat.h>
#include <math.h>
#include <sstream>

int Utils::hash(const char *str)
{
    int h = 0;
    while (*str) h = h << 1 ^ *str++;
    return h;
}


std::string Utils::getPlatformSpecificResourcePath()
{

#ifdef SFML_SYSTEM_MACOS

  return GetRPath();

#elif defined SFML_SYSTEM_LINUX

  // TODO: If "data" folder is accessible from current working directory, then simply return "" as on Windows

  return "/usr/share/tge/";

#elif defined SFML_SYSTEM_WINDOWS

  return "";

#endif

    return "";
}


bool Utils::fileExists(const std::string& filename)
{
  struct stat buf;

  if (stat(filename.c_str(), &buf) != -1) {
      return true;
  }

  return false;
}

bool Utils::makeDirectory(std::string folderPath)
{
#if defined SFML_SYSTEM_WINDOWS

  return _mkdir(folderPath.c_str()) == 0;

#elif defined SFML_SYSTEM_MACOS

  makeOSXDirectory(folderPath);

  // I guess we assume this works?
  return true;

#elif defined SFML_SYSTEM_LINUX

  //create the specified folder
  // TODO FREDRIK
  // This is unimplemented as of now.

  std::string cmd =  "mkdir -p \""+ folderPath +"\"";
  int i = system(cmd.c_str());
  if(i != 0){
    std::cerr << "Warning: Command might have not had effect: \"" << cmd << "\"." << std::endl;
  }


  return false;

#endif

    return false;
}

std::vector<std::string> Utils::listAllFilesInFolder(std::string folderPath, const char * fileExtension)
{
  std::vector<std::string> out;

  // printf("# List all files in %s\n", folderPath.c_str());

#if defined SFML_SYSTEM_WINDOWS

  DIR *dir = 0;
  struct dirent *ent = 0;

  dir = opendir ( folderPath.c_str() );
  std::string ext = ".";
  ext += fileExtension;

  if (dir != NULL)
  {
    while ((ent = readdir (dir)) != NULL)
    {
      std::string element = ent->d_name;

      if (element == "." || element == ".." || element == ".DS_Store") continue;

      // Not the extension we want
      if (element.find(ext.c_str()) == std::string::npos) continue;

      out.push_back( element );
    }

    closedir (dir);
  }

#elif defined SFML_SYSTEM_MACOS

  out = getFolderContentsByFileExtension(Utils::getPlatformSpecificResourcePath() + folderPath, fileExtension);

#elif defined SFML_SYSTEM_LINUX

  //to implement
  // TODO FREDRIK


  DIR           *d;
  struct dirent *dir;
  d = opendir(folderPath.c_str());

  std::string extwanted = "." + std::string(fileExtension);
  int s = extwanted.length();
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      std::string fname = dir->d_name;
      int ns = fname.length();
      int offset = ns - s;
      if(offset >= 0){
        if(strcmp(fname.substr(offset, s).c_str(), extwanted.c_str()) == 0){
          out.push_back(fname);
        }
      }
    }

    closedir(d);
  }


#endif

  return out;
}

int Utils::normalizeDirection(int dir)
{
	if (dir < 0) { dir += 4; }
	else if (dir >= 4) { dir -= 4; }

	return dir;
}
