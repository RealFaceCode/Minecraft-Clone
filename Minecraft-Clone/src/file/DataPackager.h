#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "File.h"

struct Node
{
	Node()	= default;
	~Node() = default;

	std::string nodeName;
	std::unordered_map<std::string, Node> nodes;
	std::vector<std::string> data;

private:
	void printNode(Node* rootNode, int tab);
	void packNotes(Node* rootNode, File* file, int tab);

public:

	void printNodes();
	void write(const char* path);

	int getAsInt(size_t at);
	float getAsFloat(size_t at);
	std::string getAsString(size_t at);

	Node& operator[] (std::string key);
	void operator= (int value);
	void operator= (float value);
	void operator= (const char* value);

	static Node loadNode(const char* path);
};
