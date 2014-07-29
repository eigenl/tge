// RessourcesDirectory.mm 

#include "ResourceFolder.h" 

#import <Foundation/Foundation.h> 

std::string GetRPath(void)
{ 
  @autoreleasepool
  {
    // Get the resources dir path. 
    std::string rpath; 
    
    NSBundle* bundle = [NSBundle mainBundle];
    
    if (bundle == nil)
    { 
      NSLog(@"bundle is nil... thus no resources path can be found."); 
    }
    else
    { 
      NSString* path = [bundle resourcePath]; 
      rpath = [path UTF8String] + std::string("/"); 
    } 
    
    return rpath;
  }
}

std::string GetApplicationSupportFolderCString(void)
{
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
  
  NSArray *paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
  
  NSString *dataPath = [[paths objectAtIndex:0] stringByAppendingPathComponent:@"Playful Mongoose/Pioneers"];
  
  std::string outStr = [dataPath UTF8String];
  
  [pool drain];

  return outStr;
}

void makeOSXDirectory(std::string dir)
{
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
  
  NSFileManager *fileManager= [NSFileManager defaultManager];
  
  NSString * dirPath = [NSString stringWithCString:dir.c_str() encoding:NSUTF8StringEncoding];
  
  if (![fileManager createDirectoryAtPath:dirPath withIntermediateDirectories:YES attributes:nil error:NULL]) {
    NSLog(@"Error: Create folder failed %@", dirPath);
  }
  
  [pool drain];
}

void CreateApplicationSupportFolder(void)
{
  NSArray *paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
  
  NSString *dataPath = [[paths objectAtIndex:0] stringByAppendingPathComponent:@"Playful Mongoose/Pioneers"];
  
  NSFileManager *fileManager= [NSFileManager defaultManager];
  
  BOOL firstRun = NO;
  BOOL isDir = YES;
  
  if (![fileManager fileExistsAtPath:dataPath isDirectory:&isDir])
  {
    firstRun = YES;
    
    if (![fileManager createDirectoryAtPath:dataPath withIntermediateDirectories:YES attributes:nil error:NULL]) {
      NSLog(@"Error: Create folder failed %@", dataPath);
    }
    
    if (![fileManager createDirectoryAtPath:[dataPath stringByAppendingFormat:@"/savegames"] withIntermediateDirectories:YES attributes:nil error:NULL]) {
      NSLog(@"Error: Create folder failed %@/scores", dataPath);
    }
  }
  
  // Wait until done
  while (![fileManager fileExistsAtPath:dataPath isDirectory:&isDir])
  {
    continue;
  }

}

std::vector<std::string> GetSaveFolderContents(void)
{
  std::vector<std::string> output;
  
  NSArray *paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
  NSString *dataPath = [[paths objectAtIndex:0] stringByAppendingPathComponent:@"Playful Mongoose/Pioneers"];
  
  NSArray *dirContents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:[dataPath stringByAppendingPathComponent:@"savegames"] error:NULL];
  
  for (NSString * path in dirContents)
  {
    if ([path isEqualToString:@".DS_Store"])
      continue;
    
    output.push_back([path UTF8String]);
  }
  
  return output;
}

std::vector<std::string> getFolderContents(std::string folder)
{
  std::vector<std::string> output;

  NSArray *dirContents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:[NSString stringWithCString:folder.c_str() encoding:NSUTF8StringEncoding]
                                                                             error:NULL];
  
  for (NSString * path in dirContents)
  {
    if ([path isEqualToString:@".DS_Store"])
      continue;
    
    output.push_back([path UTF8String]);
  }
  
  return output;
}


std::vector<std::string> GetSaves(void)
{
  std::vector<std::string> output;
  
  NSArray *paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
  NSString *dataPath = [[paths objectAtIndex:0] stringByAppendingPathComponent:@"Playful Mongoose/Pioneers"];
  
  NSArray *dirContents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:[dataPath stringByAppendingPathComponent:@"savegames"] error:NULL];
  
  for (NSString * path in dirContents)
  {
    if ([path isEqualToString:@".DS_Store"])
      continue;
    
    if ([path rangeOfString:@".sav"].location != NSNotFound || [path rangeOfString:@".zip"].location != NSNotFound) {
      output.push_back([path UTF8String]);
    }
  }
  
  return output;
}

std::vector<std::string> getFolderContentsByFileExtension(std::string folder, const char * fileExtension)
{
  std::vector<std::string> output;
  std::vector<std::string> contents = getFolderContents(folder);
  
  for (unsigned int i = 0; i < contents.size(); ++i)
  {
    if (contents[i].find((std::string(".") + std::string(fileExtension)).c_str()) != std::string::npos)
      output.push_back( contents[i] );
  }
  
  return output;
}


