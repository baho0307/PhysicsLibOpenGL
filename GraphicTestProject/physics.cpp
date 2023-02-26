#include"physics.hpp"
#include<glm/vec3.hpp>

Object::Object()
{

}

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
		if (getID() != m_Universe->getUniArr()[i]->getID() && sqrt(pow(m_Universe->getUniArr()[i]->getPosition().x - getPosition().x, 2) + pow(m_Universe->getUniArr()[i]->getPosition().y - getPosition().y, 2))>.01)
		{
			rN.x += (m_Universe->getUniArr()[i]->getPosition().x - getPosition().x) * .0000000000667 * ((m_Mass * m_Universe->getUniArr()[i]->m_Mass) / sqrt(pow(m_Universe->getUniArr()[i]->getPosition().x - getPosition().x, 2) + pow(m_Universe->getUniArr()[i]->getPosition().y - getPosition().y, 2)));
			rN.y += (m_Universe->getUniArr()[i]->getPosition().y - getPosition().y) * .0000000000667 * ((m_Mass * m_Universe->getUniArr()[i]->m_Mass) / sqrt(pow(m_Universe->getUniArr()[i]->getPosition().x - getPosition().x, 2) + pow(m_Universe->getUniArr()[i]->getPosition().y - getPosition().y, 2)));
		}
		
			
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

void Object::calcVelocity()
{
	m_N = calcGravity();
	m_V += (m_N / m_Mass);
}

void Object::start()
{
	this->move(m_V);
}

