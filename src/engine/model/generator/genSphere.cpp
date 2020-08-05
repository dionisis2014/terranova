#include <engine/model/generator/genShpere.hpp>
#include <glm/glm.hpp>

meshGenSphere::meshGenSphere() {
	meshGenSphereResolution = 4;
}

meshGenSphere::~meshGenSphere() {

}

void meshGenSphere::setResolution(unsigned int resolution) {
	if (resolution > 1)
		meshGenSphereResolution = resolution;
}

unsigned int shpereGetIndex(unsigned int height, unsigned int point, unsigned int resolution) {
	return height * resolution * 2 + point % (resolution * 2);
}

bool meshGenSphere::generate() {
	meshGeneratorObjectData.clear();
	meshGeneratorObjectElem.clear();

	if (meshGeneratorObjectIndexed) {
		float angleStepVert = glm::radians(180.0f / (meshGenSphereResolution + 1));
		float angleStepHor = glm::radians(180.0f / meshGenSphereResolution);
		glm::vec3 pos, norm;
		for (unsigned int i = 0; i < meshGenSphereResolution; i++) {
			float angleVert = angleStepVert * (i + 1);
			for (unsigned int j = 0; j < meshGenSphereResolution * 2; j++) {
				float angleHor = angleStepHor * j;
				pos.x = sin(angleHor) * sin(angleVert);
				pos.y = cos(angleVert);
				pos.z = cos(angleHor) * sin(angleVert);
				norm = glm::normalize(pos);
				meshGeneratorObjectData.push_back( {
						{ pos.x, pos.y, pos.z },
						{ 1.0f, 1.0f },
						{ norm.x, norm.y, norm.z }
				});
			}
		}
		pos = glm::vec3(0.0f, 1.0f, 0.0f);
		norm = glm::normalize(pos);
		meshGeneratorObjectData.push_back( {
				{ pos.x, pos.y, pos.z },
				{ 1.0f, 1.0f },
				{ norm.x, norm.y, norm.z }
		});
		pos = glm::vec3(0.0f, -1.0f, 0.0f);
		norm = glm::normalize(pos);
		meshGeneratorObjectData.push_back( {
				{ pos.x, pos.y, pos.z },
				{ 1.0f, 1.0f},
				{ norm.x, norm.y, norm.z }
		});

		for (unsigned int i = 0; i < meshGenSphereResolution - 1; i++) {
			for (unsigned int j = 0; j < meshGenSphereResolution * 2; j++) {
				meshGeneratorObjectElem.push_back(shpereGetIndex(i, j, meshGenSphereResolution));
				meshGeneratorObjectElem.push_back(shpereGetIndex(i + 1, j, meshGenSphereResolution));
				meshGeneratorObjectElem.push_back(shpereGetIndex(i + 1, j + 1, meshGenSphereResolution));

				meshGeneratorObjectElem.push_back(shpereGetIndex(i, j + 1, meshGenSphereResolution));
				meshGeneratorObjectElem.push_back(shpereGetIndex(i + 1, j + 1, meshGenSphereResolution));
				meshGeneratorObjectElem.push_back(shpereGetIndex(i, j, meshGenSphereResolution));
			}
		}
		for (unsigned int i = 0; i < meshGenSphereResolution * 2; i++) {
			meshGeneratorObjectElem.push_back(meshGeneratorObjectData.size() - 2);
			meshGeneratorObjectElem.push_back(shpereGetIndex(0, i, meshGenSphereResolution));
			meshGeneratorObjectElem.push_back(shpereGetIndex(0, i + 1, meshGenSphereResolution));
		}
		for (unsigned int i = 0; i < meshGenSphereResolution * 2; i++) {
			meshGeneratorObjectElem.push_back(meshGeneratorObjectData.size() - 1);
			meshGeneratorObjectElem.push_back(shpereGetIndex(meshGenSphereResolution - 1, i, meshGenSphereResolution));
			meshGeneratorObjectElem.push_back(shpereGetIndex(meshGenSphereResolution - 1, i + 1, meshGenSphereResolution));
		}
	} else {

	}

	return true;
}

unsigned int meshGenSphere::getResolution() {
	return meshGenSphereResolution;
}
