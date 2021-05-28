#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <algorithm>

#ifdef WIN32
#define screen_clear "clr"
#else
#define screen_clear "clear"
#endif

class SyncControl
{
public:

	SyncControl() = default;
	virtual ~SyncControl() = default;

	virtual void remove();
	virtual void sync();
	virtual void print();

	virtual void compute();

	virtual void makeVector() = 0;
	virtual void makeMap() = 0;

	virtual std::vector<int> getVector() const;
	virtual std::map<int, int> getMap() const;

protected:

	std::vector<int> vdata;
	std::map<int, int> mdata;

	int size = 0;
};

class AutoSync : public SyncControl
{
public:

    AutoSync() = default;
    ~AutoSync() = default;

	void makeVector() override;
	void makeMap() override;
};

class IOSync : public SyncControl
{
public:

    IOSync() = default;
    ~IOSync() = default;

	void makeVector() override;
	void makeMap() override;
};

class Factory
{
public:

    Factory() = default;
	virtual ~Factory() = default;

	virtual SyncControl* make(SyncControl* mode) = 0;
};

class SyncFactory : public Factory
{
public:

	SyncFactory() = default;
	~SyncFactory() = default;

	SyncControl* make(SyncControl* mode) override;
};
