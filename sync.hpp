#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>

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

	AutoSync() {};
	~AutoSync() {};

	void makeVector() override;
	void makeMap() override;
};

class IOSync : public SyncControl
{
public:

	IOSync() {};
	~IOSync() {};

	void makeVector() override;
	void makeMap() override;
};

class Factory
{
public:

	Factory() {};
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