#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include "physics.hpp"
#include<vector>

class Object;

class Universe 
{
public:
	
	Universe();
	unsigned long addObject(Object* obj);
	std::vector<Object*> getUniArr();
	void start();

private:
	
	unsigned long m_ID = 0;
	std::vector<Object*> m_UniverseArr ;
};

#endif // !UNIVERSE_HPP

