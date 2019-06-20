/*
 * FilePath.h
 */

#ifndef FILE_PATH_INCLUDED
#define FILE_PATH_INCLUDED

#include <string>
#ifdef ANDROID
typedef AAsset File;
#else
typedef FILE File;
#include "Interfaces.h"
#endif

#include "Context.h"

using namespace std;


/** Get the full path of a file in the filesystem.
 * @param filename the name of the file
 * @return the path to the given file
 */
string getPath(const char *filename);
string getPath(const string& filename);

/** Reads every byte from the file specified by a given path.
 * @param filepath the path obtained from getPath, check getPath
 * @return the files content, u should delete the path from outside
 */
string getContentFromPath(const char *filepath);
string getContentFromPath(const string& filepath);

/**
 * load a png/jpg/tga image
 * @param filename the image file name, this function calls getPath implicitly ..
 * @param width height the image width and height
 * @return the data pointer to the image. dont forget to free memory by calling free.
 */
unsigned char* LoadImage(const char* filename, string extension, int *width, int *height);
unsigned char* LoadImage(const string& filename, string extension, int *width, int *height);

size_t ReadFile(File *pFile, int bytesToRead, void *buffer);

unsigned char* LoadTGA(void *ioContext, const char *fileName, int *width, int *height,GLenum& format);

unsigned char* LoadPvr(const char* name, int* width, int* height, GLenum* format, GLint* level, int* bitsPerPixel);

void UnloadPvr();

#endif
