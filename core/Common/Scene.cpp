#include "..\e2dbase.h"
#include "..\e2dnode.h"
#include "..\e2dmanager.h"

e2d::Scene::Scene()
	: _autoUpdate(true)
	, _root(nullptr)
{
	_root = new (e2d::autorelease) Node();
	GC::retain(_root);
	_root->_setParentScene(this);
}

e2d::Scene::~Scene()
{
	GC::safeRelease(_root);
}

void e2d::Scene::_render()
{
	_root->_render();

	if (Game::getInstance()->getConfig()->isOutlineVisible())
	{
		Renderer::getInstance()->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
		_root->_renderOutline();
	}

	if (Game::getInstance()->getConfig()->isColliderVisible())
	{
		Renderer::getInstance()->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
		_root->_renderCollider();
	}
}

void e2d::Scene::_update()
{
	// ִ�� onUpdate ����
	if (_autoUpdate)
	{
		this->onUpdate();
	}
	// ���¸��ڵ�
	_root->_update();
}

void e2d::Scene::setAutoUpdate(bool bAutoUpdate)
{
	_autoUpdate = bAutoUpdate;
}

void e2d::Scene::add(Node * child, int order /* = 0 */)
{
	_root->addChild(child, order);
}

void e2d::Scene::add(const std::vector<Node*>& nodes, int order)
{
	for (auto node : nodes)
	{
		this->add(node, order);
	}
}

bool e2d::Scene::remove(Node * child)
{
	return _root->removeChild(child);
}

std::vector<e2d::Node*> e2d::Scene::get(const String& name) const
{
	return _root->getChildren(name);
}

e2d::Node * e2d::Scene::getOne(const String& name) const
{
	return _root->getChild(name);
}

const std::vector<e2d::Node*>& e2d::Scene::getAll() const
{
	return _root->getAllChildren();
}

e2d::Node * e2d::Scene::getRoot() const
{
	return _root;
}
