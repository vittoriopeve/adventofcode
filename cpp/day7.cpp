#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string.h>
#include<cmath>
#include "vutil.h"
#include <filesystem>
#include <map>

using namespace std;
using namespace vutil;

struct node {
	int value;
	string name;
	node* parent;
	vector<node*> childs;

	node(int v, string n, node* p) { value = v; name = n; parent = p; }

	node* getChildWithName(string n)
	{
		for (int i = 0; i < childs.size(); i++)
			if (childs[i]->name == n)
				return childs[i];
		return 0;
	}
};

int getSizeNode(node* n, int &sum)
{
	int valueTot = n->value;
	if (n->childs.size() > 0)
		for (int i = 0; i < n->childs.size(); i++)
			valueTot += getSizeNode(n->childs[i], sum);

	if (valueTot <= 100000)
		sum += valueTot;

	return valueTot;
}

int updateSizeNode(node* n, int &sum)
{
	int valueTot = n->value;
	if (n->childs.size() > 0)
		for (int i = 0; i < n->childs.size(); i++)
			valueTot += updateSizeNode(n->childs[i], sum);

	n->value = valueTot;

	sum += valueTot;

	return valueTot;
}

void getSizeNodeToDelete(node* n, const int limit, node** nearer)
{
	if(n->value > limit && (n->value < (*nearer)->value || (*nearer)->value == 0))
		(*nearer) = n;
	if (n->childs.size() > 0)
		for (int i = 0; i < n->childs.size(); i++)
			getSizeNodeToDelete(n->childs[i], limit, nearer);
}

int main() {
	vector<string> ss;
	vutil::file_2_vector("D:\\tmp\\test.txt", ss);
	
	int sum = 0;
	node dad(0, "", 0);
	node* current_node = &dad;

	for (string s : ss)
	{
		if (starts_with(s, "$")) 
		{
			//command
			if (starts_with(s.substr(2), "cd"))
			{
				//move
				if (starts_with(s.substr(5), ".."))
					current_node = current_node->parent; //move back
				else
				{
					//move folder
					string current_folder = s.substr(5);
					if (current_node)
					{
						if (current_node->getChildWithName(current_folder) == 0)
							current_node->childs.push_back(new node(0, current_folder, current_node)); //create
						current_node = current_node->getChildWithName(current_folder); //move
					}
				}
			}
			else
			{
				//stamp
				//ignore
			}
		}
		else
		{
			//file
			current_node->value += to_int(s.substr(0, s.find(" ")));
		}
	}

	node* nearer = &dad;
	cout << getSizeNode(&dad, sum) << endl;
	int tot = updateSizeNode(&dad, sum);
	int limit = 30000000 - (70000000 - tot);
	getSizeNodeToDelete(&dad, limit, &nearer);

	cout << nearer->value << endl;

	system("PAUSE");
	return 0;
}