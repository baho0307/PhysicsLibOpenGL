#include"universe.hpp"


Universe::Universe()
{

}

unsigned long Universe::addObject(Object* obj)
{
	
	m_UniverseArr.push_back(obj);
	//m_UniversePosMtx[m_ID] = obj->getPosition();
	m_ID++;
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
		m_UniverseArr[i]->calcVelocity();

		i++;
	}
	while (i > 0)
	{
		m_UniverseArr[i - 1]->start();

		i--;
	}

}

void Universe::createObjects(unsigned long n)
{
	int i, j;
	i = 0;
	j = 0;

	while (j < (float)sqrt(n))
	{
		

		new Object(this, glm::vec3((i / sqrt(n)) - .5, j*0.1-.5, 0.0f), 10);


		i = 0;
		j++;
	}

}