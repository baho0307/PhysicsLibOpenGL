#include"universe.hpp"

Universe::Universe()
{

}

unsigned long Universe::addObject(Object* obj)
{
	m_UniverseArr.push_back(obj);
	m_ID ++;
	return m_ID;
}

std::vector<Object*> Universe::getUniArr()
{
	return m_UniverseArr;
}

void Universe::start()
{
	int i;
	i = 0;

	while (i < m_UniverseArr.size())
	{
		m_UniverseArr[i]->start();
		i++;
	}
}