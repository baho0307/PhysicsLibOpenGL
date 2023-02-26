#include"universe.hpp"


Universe::Universe()
{

}

unsigned long Universe::addObject(Object* obj)
{
	m_UniverseArr.push_back(obj);
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

	while (j < sqrt(n))
	{
		while (i < sqrt(n))
		{
			new Object(this, glm::vec3(i / sqrt(n), j / sqrt(n), 0.0f), 100000);
			i++;
		}
		i = 0;
		j++;
	}

}
