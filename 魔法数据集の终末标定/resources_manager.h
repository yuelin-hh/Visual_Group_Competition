#pragma once
#include "manager.h"

class ResourcesManager: public Manager<ResourcesManager>
{
	friend class Manager<ResourcesManager>;
protected:
	ResourcesManager();
	~ResourcesManager();

private:

};

ResourcesManager::ResourcesManager()
{
}

ResourcesManager::~ResourcesManager()
{
}