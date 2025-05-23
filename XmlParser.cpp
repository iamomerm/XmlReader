﻿#include <iostream>
#include "C:\\TinyXML\\tinyxml2.h"
#include "C:\\TinyXML\\tinyxml2.cpp" 
#include <Windows.h>
#include <string>
#include <vector>

int XMLParser(tinyxml2::XMLElement * Node, std::vector<const char *> & Vector, const char * NodeName, const char * Key)
{
	try
	{
		if (Node != nullptr)
		{
			const char * nNodeName = Node->Name();
			if (!(_strcmpi(nNodeName, NodeName)))
			{
				if ((Node->Attribute("Key")) && (Node->Attribute("Value"))) 
				{ 	
					//Key Comparison
					if (Key != "*")
					{
						const char * nKey = Node->Attribute("Key");
						if (!(_strcmpi(nKey, Key)))
						{
							Vector.push_back(Node->Attribute("Key"));
							Vector.push_back(Node->Attribute("Value"));
						}
					}
					else
					{
						Vector.push_back(Node->Attribute("Key"));
						Vector.push_back(Node->Attribute("Value"));
					}		
				}
			}

			tinyxml2::XMLElement * Child = Node->FirstChildElement();

			if (Child != nullptr)
			{
				for (tinyxml2::XMLElement * Childs = Node->FirstChildElement(); Childs != nullptr; Childs = Childs->NextSiblingElement())
				{
					XMLParser(Childs, Vector, NodeName, Key);
				}
			}
		}
	}
	
	catch (std::exception &Error) { return -1; }

	return 0;
}

int main ()
{
	std::vector<const char *> Vecy;
	tinyxml2::XMLDocument XML;
	XML.LoadFile("C:\\Temp\\Example.xml");
	tinyxml2::XMLElement * Root = XML.FirstChildElement();
	XMLParser(Root, Vecy, "Number", "*");
	for (int I = 0; I < Vecy.size(); I++) { std::cout << Vecy[I] << std::endl; }	
}



