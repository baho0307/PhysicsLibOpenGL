#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include "physics.hpp"
#include<vector>
#include<glm/gtx/matrix_transform_2d.hpp>

class Object;

class Universe
{
public:

	Universe();
	void createObjects(unsigned long n);
	unsigned long addObject(Object* obj);
	std::vector<Object*> getUniArr();
	void start();

private:

	unsigned long m_ID = 0;
	std::vector<Object*> m_UniverseArr;
	glm::mat3 m_UniversePosMtx = glm::mat3(1);

};

#endif // !UNIVERSE_HPP