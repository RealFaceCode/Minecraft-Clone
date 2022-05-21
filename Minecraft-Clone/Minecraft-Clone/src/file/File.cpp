#include "File.h"
#include "BasicFileHandling.h"
#include <string>

File::~File()
{
	clear();
}

File::File(const char* path, int flags)
	: path(path), lenTotal(0), lenData(0), lenRead(0), fileExist(false), data(nullptr), fileName(nullptr), fileEnding(nullptr)
{
	std::string t(path);
	uint64_t slash = t.find_last_of('/');
	uint64_t point = t.find_last_of('.');
	t.clear();

	uint64_t lenName = point - slash - 1, lenEnding = strlen(path) - point - 1;
	fileName = new char[lenName + 1];
	fileEnding = new char[lenEnding + 1];
	memcpy(fileName, path + slash + 1, lenName);
	memcpy(fileEnding, path + point + 1, lenEnding);
	fileName[lenName]		= '\0';
	fileEnding[lenEnding]	= '\0';

	fileExist = checkExistFile(path);

	if (fileExist)
	{
		lenTotal = getFileSize(path);
	}

	if ((flags & FILE_CRT) == FILE_CRT)
	{
		if (createFile(path))
		{
			fileExist = true;
		}
	}

	if ((flags & FILE_CLR) == FILE_CLR)
	{
		clear();
	}

	if ((flags & FILE_READ) == FILE_READ)
	{
		read();
	}
}

const char* File::getPath()
{
	return path;
}

char* File::getName()
{
	return fileName;
}

char* File::getFileEnding()
{
	return fileEnding;
}

uint64_t File::size()
{
	return lenTotal;
}

uint64_t File::getReadLen()
{
	return lenRead;
}

uint64_t File::getDataLen()
{
	return lenData;
}

bool File::exist()
{
	return fileExist;
}

uint8_t* File::getData()
{
	return data;
}

uint8_t* File::getData(size_t len)
{
	if (lenRead + len > lenTotal)
	{
		return nullptr;
	}

	if (len > 0)
	{
		uint8_t* rData = new uint8_t[len];

		if (rData == nullptr)
		{
			return nullptr;
		}

		memcpy(rData, data + lenRead, len);
		lenRead += len;
		return rData;
	}
	return nullptr;
}

int8_t File::getI8()
{
	uint8_t size = sizeof(uint8_t);
	uint8_t* vData = getData(size);
	int8_t rData;
	memcpy(&rData, vData, size);
	delete[] vData;
	return rData;
}



uint8_t File::getUI8()
{
	uint8_t size = sizeof(int8_t);
	uint8_t* vData = getData(size);
	uint8_t rData;
	memcpy(&rData, vData, size);
	delete[] vData;
	return rData;
}

int16_t File::getI16()
{
	uint8_t size = sizeof(int16_t);
	uint8_t* vData = getData(size);
	int16_t rData;
	memcpy(&rData, vData, size);
	delete[] vData;
	return rData;
}

uint16_t File::getUI16()
{
	uint8_t size = sizeof(uint16_t);
	uint8_t* vData = getData(size);
	uint16_t rData;
	memcpy(&rData, vData, size);
	delete[] vData;
	return rData;
}

int32_t File::getI32()
{
	uint8_t size = sizeof(int32_t);
	uint8_t* vData = getData(size);
	int32_t rData;
	memcpy(&rData, vData, size);
	delete[] vData;
	return rData;
}

uint32_t File::getUI32()
{
	uint8_t size = sizeof(uint32_t);
	uint8_t* vData = getData(size);
	uint32_t rData;
	memcpy(&rData, vData, size);
	delete[] vData;
	return rData;
}

int64_t File::getI64()
{
	uint8_t size = sizeof(int64_t);
	uint8_t* vData = getData(size);
	int64_t rData;
	memcpy(&rData, vData, size);
	delete[] vData;
	return rData;
}

uint64_t File::getUI64()
{
	uint8_t size = sizeof(uint64_t);
	uint8_t* vData = getData(size);
	uint64_t rData;
	memcpy(&rData, vData, size);
	delete[] vData;
	return rData;
}

bool File::getBool()
{
	uint8_t size = sizeof(bool);
	uint8_t* vData = getData(size);
	bool rData;
	memcpy(&rData, vData, size);
	delete[] vData;
	return rData;
}

float File::getFloat()
{
	uint8_t size = sizeof(float);
	uint8_t* vData = getData(size);
	float rData;
	memcpy(&rData, vData, size);
	delete[] vData;
	return rData;
}

double File::getDouble()
{
	uint8_t size = sizeof(double);
	uint8_t* vData = getData(size);
	double rData;
	memcpy(&rData, vData, size);
	delete[] vData;
	return rData;
}

char* File::getCString()
{
	size_t sLen = getUI64();
	uint8_t* vData = getData(sLen);
	char* rData = new char[sLen + 1];
	memcpy(rData, vData, sLen);
	rData[sLen] = '\0';
	delete[] vData;
	return rData;
}

void File::addData(void* dat, uint64_t len)
{
	if (data == nullptr)
	{
		reserve(len);
		memcpy(data + lenData, dat, len);
		lenData += len;
		return;
	}

	if (lenData + len > lenTotal)
	{
		reserve(len);
		memcpy(data + lenData, dat, len);
		lenData += len;
		return;
	}


	memcpy(data + lenData, dat, len);
	lenData += len;
	return;

}

void File::addI8(int8_t dat)
{
	addData(&dat, sizeof(int8_t));
}

void File::addUI8(uint8_t dat)
{
	addData(&dat, sizeof(uint8_t));
}

void File::addI16(int16_t dat)
{
	addData(&dat, sizeof(int16_t));
}

void File::addUI16(uint16_t dat)
{
	addData(&dat, sizeof(uint16_t));
}

void File::addI32(int32_t dat)
{
	addData(&dat, sizeof(int32_t));
}

void File::addUI32(uint32_t dat)
{
	addData(&dat, sizeof(uint32_t));
}

void File::addI64(int64_t dat)
{
	addData(&dat, sizeof(int64_t));
}

void File::addUI64(uint64_t dat)
{
	addData(&dat, sizeof(uint64_t));
}

void File::addBool(bool dat)
{
	addData(&dat, sizeof(bool));
}

void File::addFloat(float dat)
{
	addData(&dat, sizeof(float));
}

void File::addDouble(double dat)
{
	addData(&dat, sizeof(double));
}

//Adds a string without the string length
void File::addString(const char* dat)
{
	size_t sLen = strlen(dat);
	addData((void*)dat, sLen);
}

//Adds a string with the string length
void File::addCString(const char* dat)
{
	size_t sLen = strlen(dat);
	addI64(sLen);
	addData((void*)dat, sLen);
}

bool File::read()
{
	if (path == nullptr)
	{
		return false;
	}

	if (!fileExist)
	{
		if (fileExist = checkExistFile(path) != true)
		{
			return false;
		}
	}

	if (lenData <= 0)
	{
		lenData = lenTotal = getFileSize(path);
	}

	FILE* file = _fsopen(path, "rb", _SH_DENYNO);

	if (file == nullptr)
	{
		return false;
	}

	data = new uint8_t[lenData];

	if (data == nullptr)
	{
		return false;
	}

	size_t result = fread_s(data, lenData, lenData, 1, file);
	fclose(file);

	if(result == 0)
	{
		delete[] data;
		data = nullptr;
		return false;
	}

	return true;
}

bool File::write()
{
	if (path == nullptr)
	{
		return false;
	}

	if (!fileExist)
	{
		if (fileExist = checkExistFile(path) != true)
		{
			createFile(path);
			fileExist = true;
		}
	}

	if (lenData <= 0)
	{
		return false;
	}

	FILE* file = _fsopen(path, "wb", _SH_DENYNO);

	if (file == nullptr)
	{
		return false;
	}

	size_t result = fwrite(data, lenData, 1, file);
	fclose(file);

	if (result != 1)
	{
		return false;
	}

	return true;
}

void File::clear()
{
	if (fileName != nullptr)
	{
		delete fileName;
		fileName = nullptr;
	}
		
	if (fileEnding != nullptr)
	{
		delete fileEnding;
		fileEnding = nullptr;
	}
		
	if (data != nullptr)
	{
		delete data;
		data = nullptr;
	}

	lenData		= 0;
	lenTotal	= 0;
	lenRead		= 0;

	fileExist	= false;
	path		= nullptr;
}

void File::reserve(size_t bytes)
{
	if (bytes <= 0)
	{
		return;
	}

	if (lenTotal == 0)
	{
		if (data != nullptr)
		{
			delete[] data;
			data = nullptr;
		}

		data = new uint8_t[bytes];
		lenTotal += bytes;
		return;
	}

	uint8_t* tmpData = new uint8_t[lenData];

	if (tmpData == nullptr)
	{
		return;
	}

	memcpy(tmpData, data, lenData);

	delete[] data;
	data = nullptr;

	data = new uint8_t[lenTotal + bytes];

	if (data == nullptr)
	{
		return;
	}

	memcpy(data, tmpData, lenData);
	lenTotal += bytes;
	
	delete[] tmpData;
}