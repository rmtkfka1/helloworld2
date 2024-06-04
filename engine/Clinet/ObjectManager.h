#pragma once



class ObjectManager
{
public:

	static ObjectManager* GetInstance()
	{
		static ObjectManager instance;
		return &instance;
	}

public:


};

