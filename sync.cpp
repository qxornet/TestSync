#include "sync.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// AutoControl
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void
SyncControl::remove()
{
	std::cout << "Remove bad allocation... ";
	int removeCount = 1 + rand() % (size - 1);
	for (int i = 0; i < removeCount; i++)
	{
		this->vdata.erase(std::remove(this->vdata.begin(), this->vdata.end(), 1 + rand() % size), this->vdata.end());
		auto item = this->mdata.find(1 + rand() % size); 
		if (item != this->mdata.end())
			this->mdata.erase(item);
	}
	std::cout << removeCount << " items has removed" << std::endl;
}

void SyncControl::sync()
{
	std::cout << "Syncing... ";
	std::map<int, int> bufferMap;
	std::vector<int> bufferVec;

	int currentPosition = 1;
	for (auto& vecItem : this->vdata)
	{
		for (auto& [keyMap, keyItem] : this->mdata)
		{
			if (vecItem != keyItem) continue;
			bufferMap[keyMap] = keyItem;
			this->mdata.erase(keyMap);
			
			bufferVec.push_back(vecItem);
			this->vdata.erase(std::remove(this->vdata.begin(), this->vdata.end(), currentPosition), this->vdata.end());
		}
		currentPosition++;
	}

	int incorCount = this->vdata.size();
	this->vdata = bufferVec;
	this->mdata = bufferMap;

	std::cout << "Finished. " << incorCount << " incorrect items found" << std::endl;
}

void
SyncControl::print()
{
	std::cout << "Vector" << " Lenght: " << this->vdata.size() << std::endl;

	for (auto item : this->vdata)
	{
		std::cout << "Value: " << item << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Map" << " Lenght: " << this->mdata.size() << std::endl;

	for (auto [key, item] : this->mdata)
	{
		std::cout << " Key: " << key << " Value: " << item << std::endl;
	}
	std::cout << std::endl;
}

void
SyncControl::compute()
{
	this->size = 5 + rand() % (15 - 5);
	std::cout << "Generated " << size << " values..." << std::endl;

	this->makeVector();
	this->makeMap();

	this->remove();
	this->sync();
	this->print();
}

std::vector<int>
SyncControl::getVector() const
{
	return this->vdata;
}

std::map<int, int>
SyncControl::getMap() const
{
	return this->mdata;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// AutoSync
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void
AutoSync::makeVector()
{
	std::cout << "Vector make... " << std::endl;
	for (int i = 0; i < this->size; i++)
	{
		this->vdata.push_back(1 + rand() % 9);
	}
}

void
AutoSync::makeMap()
{
	std::cout << "Map make... " << std::endl;
	for (int i = 0; i < this->size; i++)
		this->mdata[i] = 1 + rand() % 9;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// IOSync
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void
IOSync::makeVector()
{
	system("cls");
	std::cout << "Please enter to buffer " << this->size << " values by vector container" << std::endl;

	for (int i = 0; i < this->size; i++)
	{
		int value;
		std::cout << "Enter value: "; std::cin >> value;
		this->vdata.push_back(value);
	}
}

void
IOSync::makeMap()
{
	system("cls");
	std::cout << "Please enter to buffer " << this->size << " values by map container" << std::endl;

	for (int i = 0; i < this->size; i++)
	{
		int key, value;
		std::cout << "Enter key: "; std::cin >> key;
		std::cout << "Enter value: "; std::cin >> value;
		this->mdata[key] = value;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SyncFactory
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SyncControl* 
SyncFactory::make(SyncControl* mode)
{
	return mode;
}