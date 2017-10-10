#include "..\easy2d.h"

Node::Node() :
	m_nZOrder(0),
	m_bDisplay(true),
	m_pParent(nullptr)
{
}

Node::Node(CPoint p) :
	m_nZOrder(0),
	m_bDisplay(true),
	m_pParent(nullptr),
	m_Pos(p)
{
}

Node::Node(int x, int y) :
	m_nZOrder(0),
	m_bDisplay(true),
	m_pParent(nullptr)
{
}

Node::~Node()
{
}

bool Node::_exec(bool active)
{
	return false;
}

void Node::_onDraw()
{
}

int Node::getX() const
{
	return m_Pos.x;
}

int Node::getY() const
{
	return m_Pos.y;
}

CPoint Node::getPos() const
{
	return m_Pos;
}

void Node::setX(int x)
{
	m_Pos.x = m_pParent ? m_pParent->getX() + x : x;
}

void Node::setY(int y)
{
	m_Pos.y = m_pParent ? m_pParent->getY() + y : y;
}

void Node::setPos(int x, int y)
{
	if (m_pParent)
	{
		m_Pos.SetPoint(m_pParent->getX() + x, m_pParent->getY() + y);
	}
	else
	{
		m_Pos.SetPoint(x, y);
	}
}

void Node::setPos(CPoint p)
{
	if (m_pParent)
	{
		m_Pos = m_pParent->getPos() + p;
	}
	else
	{
		m_Pos = p;
	}
}

void Node::move(int x, int y)
{
	m_Pos.Offset(x, y);
}

void Node::move(CVector v)
{
	m_Pos.Offset(v);
}

int Node::getZOrder() const
{
	return m_nZOrder;
}

void Node::setZOrder(int z)
{
	m_nZOrder = z;
}

Node * Node::getParent()
{
	return m_pParent;
}

void Node::setParent(Node * parent)
{
	if (parent)
	{
		m_pParent = parent;
	}
}

Scene * Node::getParentScene()
{
	return m_pScene;
}

void Node::setParentScene(Scene * scene)
{
	m_pScene = scene;
}

void Node::setDisplay(bool value)
{
	m_bDisplay = value;
}

bool Node::display() const
{
	return m_bDisplay;
}