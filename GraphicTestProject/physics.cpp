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

Object::Object()
{

}



void Object::move(glm::vec3 v)
{
	m_Pos += v;
}

glm::vec3 Object::calcGravity()
{
	int i;
	i = 0;
	glm::vec3 rN(0.0f, 0.0f, 0.0f);
	while (i < m_Universe->getUniArr().size())
	{
		if (sqrt(pow(m_Universe->getUniArr()[i]->getPosition().x - getPosition().x, 2) + pow(m_Universe->getUniArr()[i]->getPosition().y - getPosition().y, 2)) > .005)
		{
			rN.x += (m_Universe->getUniArr()[i]->getPosition().x - getPosition().x) * .0000000000667 * ((m_Mass * m_Universe->getUniArr()[i]->m_Mass) / sqrt(pow(m_Universe->getUniArr()[i]->getPosition().x - getPosition().x, 2) + pow(m_Universe->getUniArr()[i]->getPosition().y - getPosition().y, 2)));
			rN.y += (m_Universe->getUniArr()[i]->getPosition().y - getPosition().y) * .0000000000667 * ((m_Mass * m_Universe->getUniArr()[i]->m_Mass) / sqrt(pow(m_Universe->getUniArr()[i]->getPosition().x - getPosition().x, 2) + pow(m_Universe->getUniArr()[i]->getPosition().y - getPosition().y, 2)));
		}
			


		i++;
	}
	std::vector<Object*> collide = isColliding();
	int j;
	j = 0;
	while(j<collide.size())
	{
		rN.x = 0;
		rN.y = 0;

		float cAngle = acos((collide[j]->getPosition().y - getPosition().y) / objDistance(collide[j])) * (180 / 3.1415);
		float mAngle1 = acos(m_V.y / sqrt(m_V.x * m_V.x + m_V.y * m_V.y)) * (180 / 3.1415);
		float mAngle2 = acos(collide[j]->getVelocity().y / sqrt(collide[j]->getVelocity().x * collide[j]->getVelocity().x + collide[j]->getVelocity().y * collide[j]->getVelocity().y)) * (180 / 3.1415);
		///this.physics.nextN.x = (-this.physics.v.x * this.physics.mass + obj.physics.v.x*obj.physics.mass/2);
		rN.x += (sqrt(m_V.x * m_V.x + m_V.y * m_V.y) * cos(mAngle1 - cAngle) * (m_Mass - collide[j]->getMass()) + 2 * collide[j]->getMass() * sqrt(collide[j]->getVelocity().x * collide[j]->getVelocity().x + collide[j]->getVelocity().y * collide[j]->getVelocity().y) * cos(mAngle2 - cAngle)) * cos(cAngle) / (m_Mass + collide[j]->getMass()) + sqrt(m_V.x * m_V.x + m_V.y * m_V.y) * sin(mAngle1 - cAngle) * cos(cAngle + 3.1415 / 2) * m_Mass;
		rN.y += (sqrt(m_V.x * m_V.x + m_V.y * m_V.y) * cos(mAngle1 - cAngle) * (m_Mass - collide[j]->getMass()) + 2 * collide[j]->getMass() * sqrt(collide[j]->getVelocity().x * collide[j]->getVelocity().x + collide[j]->getVelocity().y * collide[j]->getVelocity().y) * cos(mAngle2 - cAngle)) * sin(cAngle) / (m_Mass + collide[j]->getMass()) + sqrt(m_V.x * m_V.x + m_V.y * m_V.y) * sin(mAngle1 - cAngle) * sin(cAngle + 3.1215 / 2) * m_Mass;
		///this.physics.nextN.y = (-this.physics.v.y * this.physics.mass + obj.physics.v.y * obj.physics.mass/2);
		j++;
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
}

void Object::start()
{
	m_V += (m_N / m_Mass);
	this->move(m_V);
}

std::vector<Object*> Object::isColliding()
{
	std::vector<Object*> r;
	int i;
	i = 0;

	while (i < m_Universe->getUniArr().size())
	{
		if (getID() != m_Universe->getUniArr()[i]->getID() && objDistance(m_Universe->getUniArr()[i]) <= .005)
			r.push_back(m_Universe->getUniArr()[i]);
		i++;
	}
	return r;
}
float Object::objDistance(Object* obj)
{
	return sqrt(pow(obj->getPosition().x - getPosition().x, 2) + pow(obj->getPosition().y - getPosition().y, 2));
}

glm::vec3 Object::getVelocity()
{
	return m_V;
}

float Object::getMass()
{
	return m_Mass;
}
