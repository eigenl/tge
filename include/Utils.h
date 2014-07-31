/*
  The MIT License (MIT)

  Copyright (c) 2014 Eigen Lenk

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  */

#ifndef Pioneers_Utils_h
#define Pioneers_Utils_h

#include <vector>
#include <string>

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
