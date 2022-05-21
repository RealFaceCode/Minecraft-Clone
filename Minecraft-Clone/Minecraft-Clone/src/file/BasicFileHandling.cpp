#define _CRT_SECURE_NO_WARNINGS
#include "BasicFileHandling.h"
#include <stdio.h>
#include <direct.h>
#include <sys/stat.h>
#include <io.h>

// Creates a file, return false if path == nullptr or file already exist
bool createFile(const char* path) {
	if (path == nullptr) {
		return false;
	}
	int result = _creat(path, _S_IREAD | _S_IWRITE);
	if (result == -1 || checkExistFile(path) != true) {
		return false;
	}
	return true;
}

// Removes a file, return false if path == nullptr or no file exist
bool removeFile(const char* path) {
	if (path == nullptr || remove(path) != 0) {
		return false;
	}
	return true;
}

// Checking for a file, return false if no file exist ore path == nullptr
bool checkExistFile(const char* path) {
	if (path == nullptr) return false;
	return _access(path, 00) != -1;
}

// Renames an existing file, return false if path ore newName == nullptr or no file exist or rename failed
bool renameFile(const char* path, const char* newName) {
	if (path == nullptr || newName == nullptr) {
		return false;
	}
	if (!checkExistFile(path)) {
		return false;
	}
	if (rename(path, newName) != 0) {
		return false;
	}
	return true;
}

// Returns the filesize, return 0 if file has len 0 or no file exist or path == nullptr
uint64_t getFileSize(const char* path) {
	struct stat buf {};
	int c = stat(path, &buf);
	return c == 0 ? buf.st_size : 0;
}

// Creates a directory, returns 0 if the directory already exist or path == nullptr
bool createDir(const char* dirPath) {
	if (checkExistDir(dirPath)) return false;
	return (_mkdir(dirPath) == 0);
}

// Removes a directory, return false if no directory exist
bool removeDir(const char* dirPath) {
	if (!checkExistDir(dirPath)) return false;
	return (_rmdir(dirPath) == 0);
}

// Checks if a directory exist, return false if no exist
bool checkExistDir(const char* dirPath) {
	if (dirPath == nullptr) return false;
	struct stat sb;
	return (stat(dirPath, &sb) == 0 && (S_IFDIR & sb.st_mode) != 0);
}