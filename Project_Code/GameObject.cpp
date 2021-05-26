#include "GameObject.h"


GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position
}

CellPosition GameObject::GetPosition() const
{
	return position;
}
void GameObject::SetPosition(const CellPosition & pos)
{
	position=pos;
}

GameObject::~GameObject()
{
}