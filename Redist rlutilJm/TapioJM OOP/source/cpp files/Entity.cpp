#include "Entity.h"

Entity::Entity(int _type, int _x, int _y)
{
	type = _type;
	x = _x; 
	y = _y;
}

Entity::Entity()
{

}

Entity::~Entity()
{
}

void Entity::setSprite(int ** _sprite)
{
	for (int i = 0; i < spriteSizeY; i++)
	{
		for (int j = 0; j < spriteSizeX; j++)
		{
			sprite[i][j] = _sprite[i][j];
		}
	}
}

void Entity::setColors(int col1, int col2, int col3, int col4)
{
	color1 = col1;
	color2 = col2;
	color3 = col3;
	color4 = col4;
}

void Entity::setLetters(char let1, char let2, char let3, char let4)
{
	letter1 = let1;
	letter2 = let2;
	letter3 = let3;
	letter4 = let4;
}

void Entity::setBackgrounds(int _bg1, int _bg2, int _bg3, int _bg4)
{
	bg1 = _bg1;
	bg2 = _bg2;
	bg3 = _bg3;
	bg4 = _bg4;
}

void Entity::InitSprite(int sizeX, int sizeY)
{
	spriteSizeX = sizeX;
	spriteSizeY = sizeY;
	sprite = new int*[spriteSizeY];
	for (int i = 0; i <spriteSizeX; i++)
	{
		sprite[i] = new int[spriteSizeX];
	}
}

void Entity::draw()
{
	//rlUtilJM::AddToDrawThread(std::bind(&Entity::DrawBody,this));
	DrawBody();
}

void Entity::freeSprite()
{
	for (int i = 0; i < spriteSizeY; i++)
	{
		delete[](sprite[i]);
	}
	delete(sprite);
}

void Entity::DrawBody()
{
	if (type == CHARACTER || type == ENEMY)
	{
		int i, j;
		for (i = 0; i < spriteSizeY; i++)
		{
			for (j = 0; j < spriteSizeX; j++)
			{
				if ((sprite[i][j]) & CHARACTER1)
				{
					rlUtilJM::AddToBuffer(color1, bg1, letter1, x + j, y + i, type, nullptr);
				}
				else if ((sprite[i][j]) & CHARACTER2)
				{
					rlUtilJM::AddToBuffer(color2, bg2, letter2, x + j, y + i, type, nullptr);
				}
				else if ((sprite[i][j]) & CHARACTER3)
				{
					rlUtilJM::AddToBuffer(color3, bg3, letter3, x + j, y + i, type, nullptr);
				}
				else if ((sprite[i][j]) & CHARACTER4)
				{
					rlUtilJM::AddToBuffer(color4, bg4, letter4, x + j, y + i, type, nullptr);
				}
				else if ((sprite[i][j]) & WEAPON)
				{
					rlUtilJM::AddToBuffer(weapon, BLACK, charWeapon, x + j, y + i, type, nullptr);
				}
				else if ((sprite[i][j]) & CLEAR)
				{
					rlUtilJM::AddToBuffer(BLACK, BLACK, ' ', x + j, y + i, CLEAR, nullptr);
				}
				else
				{

				}
			}
		}
	}
	else if (type == BACKGROUND)
	{
		int i, j;
		for (i = 0; i < spriteSizeY; i++)
		{
			for (j = 0; j < spriteSizeX; j++)
			{
				if ((sprite[i][j]) & BACKGROUND1)
				{
					rlUtilJM::AddToBuffer(color1, bg1, letter1, x + j, y + i, type, nullptr);
				}
				else if ((sprite[i][j]) & BACKGROUND2)
				{
					rlUtilJM::AddToBuffer(color2, bg2, letter2, x + j, y + i, type, nullptr);
				}
				else if ((sprite[i][j]) & BACKGROUND3)
				{
					rlUtilJM::AddToBuffer(color3, bg3, letter3, x + j, y + i, type, nullptr);
				}
				else if ((sprite[i][j]) & BACKGROUND4)
				{
					rlUtilJM::AddToBuffer(color4, bg4, letter4, x + j, y + i, type, nullptr);
				}
				else if ((sprite[i][j]) & CLEAR)
				{
					rlUtilJM::AddToBuffer(BLACK, BLACK, ' ', x + j, y + i, CLEAR, nullptr);
				}
				else
				{

				}
			}
		}
	}
}
