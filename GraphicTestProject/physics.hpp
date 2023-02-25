#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include<glm/vec3.hpp>
#include<vector>
#include"universe.hpp"

class Universe;

class Object
{
	public:

		Object(Universe* universe, glm::vec3 pos, float mass, glm::vec3 v = glm::vec3(0.0f, 0.0f, 0.0f));

		glm::vec3 getPosition();
		void setPosition(glm::vec3 nPos);

		unsigned long getID();

		void start();

		void move(glm::vec3 v);

	private:

		glm::vec3 m_Pos;
		glm::vec3 m_N;
		glm::vec3 m_V;
		float m_Mass;
		unsigned int m_ID;

		Universe* m_Universe;

		glm::vec3 calcGravity();
};

#endif // !PHYSICS_HPP
