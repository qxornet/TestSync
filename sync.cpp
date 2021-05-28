#include "sync.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// AutoControl
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void
SyncControl::remove()
{
    std::cout << "Removing bad allocation... ";
    int removeCount = 1 + rand() % (15 - 1);
	for (int i = 0; i < removeCount; i++)
	{
		this->vdata.erase(std::remove(this->vdata.begin(), this->vdata.end(), 1 + rand() % size), this->vdata.end());
		auto item = this->mdata.find(1 + rand() % size); 
		if (item != this->mdata.end())
			this->mdata.erase(item);
	}
    std::cout << "\x1b[36m" << this->size - this->vdata.size() << "\x1b[0m items has removed" << std::endl;
}

void SyncControl::sync()
{
	std::cout << "Syncing... ";
	std::map<int, int> bufferMap;
	std::vector<int> bufferVec;

    int mapItem = 0;
	for (auto& vecItem : this->vdata)
	{
		for (auto& [keyMap, keyItem] : this->mdata)
		{
			if (vecItem != keyItem) continue;
            bufferMap[keyMap] = keyItem;
            mapItem = keyItem;
            this->mdata.erase(this->mdata[keyMap]);
		}

        if (vecItem != mapItem) continue;
        bufferVec.push_back(vecItem);
	}

    int incorCount = this->vdata.size() - bufferVec.size();
	this->vdata = bufferVec;
	this->mdata = bufferMap;

    std::cout << "Finished. \x1b[36m" << incorCount << "\x1b[0m incorrect items found" << std::endl;
}

void
SyncControl::print()
{
    std::cout << "Vector" << " Lenght: \x1b[36m" << this->vdata.size() << "\x1b[0m" << std::endl;

	for (auto item : this->vdata)
	{
        std::cout << "Value: \x1b[36m" << item << "\x1b[0m" << std::endl;
	}

	std::cout << std::endl;

    std::cout << "Map" << " Lenght: \x1b[36m" << this->mdata.size() << "\x1b[0m" << std::endl;

	for (auto [key, item] : this->mdata)
	{
        std::cout << " Key: \x1b[36m" << key << "\x1b[0m" << " Value: \x1b[36m" << item << "\x1b[0m" << std::endl;
	}
	std::cout << std::endl;
}

void
SyncControl::compute()
{
    this->size = 15 + rand() % (25 - 15);
    std::cout << "Generated \x1b[36m" << size << "\x1b[0m values..." << std::endl;

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
    system(screen_clear);
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
    system(screen_clear);
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
