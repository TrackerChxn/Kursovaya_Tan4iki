#include "Scene.h"
#include "SceneDefines.h"
Scene::Scene() {
	cameraYaw = cameraPitch = 0;
	camDist = 200.0f;
	campos = { -camDist,camDist,0.0f };
	camdir = { 0.0f,0.0f,0.0f };
	lights.numPLights = 0;
	lights.numSLights = 0;
	lights.dirLight.ambient = { 1.0f,1.0f,1.0f };
	lights.dirLight.diffuse= { 1.0f,1.0f,1.0f };
	lights.dirLight.specular = { 1.0f,1.0f,1.0f };
	lights.dirLight.direction = { 0.0f,0.0f,1.0f };
	rotateCam(0.0f, 1.0f);
	vs = LoadShader("shaders/VertexShader.glsl", GL_VERTEX_SHADER);
	if (vs == -1) {
		//TODO: обработать
	}
	fs = LoadShader("shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	if (vs == -1) {
		//TODO: обработать
	}
	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, vs);
	glAttachShader(shader_programme, fs); 
	glBindAttribLocation(shader_programme, 0, "vertex_position");
	glBindAttribLocation(shader_programme, 1, "vertex_colour");
	glLinkProgram(shader_programme);
}

void Scene::addObject(BaseObject *obj) {
	Objects.push_back(obj);
}

void Scene::render(int WW, int WH) {
	glm::mat4 prsp = glm::perspective(glm::radians(FOV), (float)WW / WH, FCLIP,SKYBOXSIZE*2+10.0f);
	glm::mat4 cam = glm::lookAt(campos, camdir, glm::vec3(0.0f, 1.0f, 0.0f));
	for (int i = 0; i < Objects.size(); i++)
		Objects[i]->draw(prsp, cam, campos, lights, shader_programme);
}

void Scene::tick(float tickl){
	for (int i = 0; i < Objects.size(); i++)
		Objects.at(i)->tick(tickl);
}

void Scene::setCampos(glm::vec3 newpos){

}

glm::vec3 Scene::getCampos()
{
	return campos;
}


void Scene::moveCam(glm::vec3 mv){
	campos +=mv;
	camdir += mv;
}

void Scene::rotateCam(float yaw, float pitch){
	cameraYaw = cameraYaw+ yaw;
	cameraPitch += pitch;
	campos.x = camdir.x - camDist * cos(cameraPitch) * cos(cameraYaw);
	campos.y = camdir.y + camDist * sin(cameraPitch);
	campos.z = camdir.z - camDist * cos(cameraPitch) * sin(cameraYaw);

}
void Scene::setDirLight(DirLight l){
	lights.dirLight = l;
}

PointLight* Scene::addPointLight(PointLight p)
{
	if (lights.numPLights < MAX_NUM_LIGHTS) {
		lights.pointLights[lights.numPLights] = p;
		lights.numPLights++;
		return lights.pointLights + lights.numPLights - 1;
	}else return nullptr;
}

SpotLight* Scene::addSpotLight(SpotLight s)
{
	if (lights.numSLights < MAX_NUM_LIGHTS) {
		lights.spotLights[lights.numSLights] = s;
		lights.numSLights++;
		return lights.spotLights + lights.numSLights - 1;
	}
	else return nullptr;
}

Scene::~Scene(){
	for (int i = 0; i < Objects.size(); i++)
		delete Objects[i];
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(shader_programme);
}
