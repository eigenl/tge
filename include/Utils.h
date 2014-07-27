#ifndef Pioneers_Utils_h
#define Pioneers_Utils_h

#include "ResourceFolder.h"

// For convinience
#define DEG_TO_RAD (3.14159265 / 180.0)
#define RAD_TO_DEG (180.0 / 3.14159265)
#define HASH(n) Utils::hash(n)

class Utils
{
public:

  static std::string                getPlatformSpecificResourcePath();
  static int                        hash(const char *str);
  static bool                       fileExists(const std::string& filename);
  static bool                       makeDirectory(std::string folderPath);
  static std::vector<std::string>   listAllFilesInFolder(std::string folderPath, const char * fileExtension = "sav");
  static int                        normalizeDirection(int dir);
};

#endif
