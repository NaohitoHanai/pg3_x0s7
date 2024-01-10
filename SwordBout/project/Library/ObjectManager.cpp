#include "ObjectManager.h"
#include "GameObject.h"
#include <algorithm>

std::list<ObjectManager::ObjectUpdate> updateObjects;
std::list<ObjectManager::ObjectDraw> drawObjects;
bool needSortUpdate;
bool needSortDraw;

void ObjectManager::Start()
{
	updateObjects.clear();
	drawObjects.clear();
	needSortUpdate = false;
	needSortDraw = false;
}

void deleteDrawObject(GameObject* obj)
{
	for (auto it = drawObjects.begin(); it != drawObjects.end(); ) {
		if ((*it).object == obj) {
			it = drawObjects.erase(it);
		}
		else {
			it++;
		}
	}
}

void ObjectManager::Update()
{
	if (needSortUpdate) {
		updateObjects.sort([](ObjectUpdate& a, ObjectUpdate& b) {return a.priority < b.priority; });
		needSortUpdate = false;
	}
	for (auto it = updateObjects.begin(); it != updateObjects.end(); ) {
		ObjectUpdate& node = *it;
		GameObject* obj = node.object;
		if (!node.initialized) {
			obj->Start();
			node.initialized = true;
		}
		obj->Update();
		if (node.destroyMe) {
			deleteDrawObject(obj);
			delete obj;
			it = updateObjects.erase(it);
		}
		else {
			it++;
		}
	}
}

void ObjectManager::Draw()
{
	if (needSortDraw) {
		drawObjects.sort([](ObjectDraw& a, ObjectDraw& b) {return a.order > b.order; });
		needSortDraw = false;
	}
	for (ObjectDraw node : drawObjects) {
		node.object->Draw();
	}
}

void ObjectManager::Release()
{
	DeleteAllGameObject();
}

void ObjectManager::ChangeScene()
{
	for (auto it = updateObjects.begin(); it != updateObjects.end();) {
		ObjectUpdate& node = *it;
		if (!node.dontDestroy) {
			deleteDrawObject(node.object);
			delete node.object;
			it = updateObjects.erase(it);
		} else
			it++;
	}
}

void ObjectManager::Push(GameObject* obj)
{
	{
		ObjectUpdate node;
		node.object = obj;
		updateObjects.emplace_back(node);
		needSortUpdate = true;
	}
	{
		ObjectDraw node;
		node.object = obj;
		drawObjects.emplace_back(node);
		needSortDraw = true;
	}
}

void ObjectManager::Destroy(GameObject* obj)
{
	for (ObjectUpdate& ou : updateObjects) {
		if (ou.object == obj)
			ou.destroyMe = true;
	}
}

const std::list<ObjectManager::ObjectUpdate>& ObjectManager::GetAllObject()
{
	return updateObjects;
}

void ObjectManager::SetDrawOrder(GameObject* _obj, int _order)
{
	for (ObjectDraw& od : drawObjects) {
		od.order = _order;
	}
	needSortDraw = true;
}

void ObjectManager::SetPriority(GameObject* _obj, int _priority)
{
	for (ObjectUpdate& ou : updateObjects) {
		ou.priority = _priority;
	}
	needSortUpdate = true;
}

void ObjectManager::DeleteGameObject(GameObject* obj)
{
	deleteDrawObject(obj);
	for (auto it = updateObjects.begin(); it != updateObjects.end(); ) {
		ObjectUpdate& node = (*it);
		if (node.object == obj) {
			delete obj;
			it = updateObjects.erase(it);
		}
		else
			it++;
	}
}

void ObjectManager::DeleteAllGameObject()
{
	for (auto it = updateObjects.begin(); it != updateObjects.end(); it++) {
		ObjectUpdate& node = *it;
		delete node.object;
	}
	updateObjects.clear();
	drawObjects.clear();
}

void ObjectManager::DontDestroy(GameObject* obj, bool dont)
{
	for (auto it = updateObjects.begin(); it != updateObjects.end(); it++) {
		ObjectUpdate& node = *it;
		if (node.object == obj) {
			node.dontDestroy = dont;
		}
	}
}
