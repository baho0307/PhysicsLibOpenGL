#include"physics.hpp"
#include<glm/vec3.hpp>

Object::Object(Universe* universe, glm::vec3 pos, float mass, glm::vec3 v)
{
	m_Universe = universe;
	m_Pos = pos;
	m_Mass = mass;
	m_ID = universe->addObject(this);
	m_V = v;
}

void Object::move(glm::vec3 v)
{
	m_Pos += v;
}

glm::vec3 Object::calcGravity()
{
	int i;
	i = 0;
	glm::vec3 rN (0.0f,0.0f,0.0f);
	while(i < m_Universe->getUniArr().size())
	{
		if(this->getID() != m_Universe->getUniArr()[i]->getID())
			rN.x +=0.00001;
		i++;
	}
	return rN;
}

glm::vec3 Object::getPosition()
{
	return m_Pos;
}

void Object::setPosition(glm::vec3 nPos)
{
	m_Pos = nPos;
}

unsigned long Object::getID()
{
	return m_ID;
}

void Object::start()
{
	m_N = calcGravity();
	m_V += (m_N / m_Mass);
	this->move(m_V);
}