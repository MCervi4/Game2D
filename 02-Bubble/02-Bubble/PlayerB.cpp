#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PlayerB.h"
#include "Game.h"





enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT
};


void PlayerB::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	damuntMeta = false;
	death = false;
	lavaWalk = false;
	saltAlt = false;
	levelFinished = false;
	jumpH = JUMP_HEIGHT;

	spritesheet.loadFromFile("images/messi.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(40, 40), glm::vec2(1. / 9., 1. / 9.), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(1. / 9., 2. / 9.));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(5. / 9., 2. / 9.));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0. / 9., 3. / 9.));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(4. / 9., 3. / 9.));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(8. / 9., 1. / 9.));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(3. / 9., 2. / 9.));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(7. / 9., 2. / 9.));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(2. / 9., 3. / 9.));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(6. / 9., 5. / 9.));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(1. / 9., 6. / 9.));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(5. / 9., 6. / 9.));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0. / 9., 7. / 9.));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(4. / 9., 7. / 9.));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(8. / 9., 7. / 9.));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4. / 9., 5. / 9.));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(8. / 9., 5. / 9.));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3. / 9., 6. / 9.));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(7. / 9., 6. / 9.));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2. / 9., 7. / 9.));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(6. / 9., 7. / 9.));

	sprite->setAnimationSpeed(JUMP_LEFT, 8);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(6. / 9., 3. / 9.));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(1. / 9., 4. / 9.));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(5. / 9., 4. / 9.));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(8. / 9., 4. / 9.));

	sprite->setAnimationSpeed(JUMP_RIGHT, 8);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(5. / 9., 3. / 9.));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0. / 9., 4. / 9.));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(4. / 9., 4. / 9.));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(2. / 9., 5. / 9.));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void PlayerB::update(int deltaTime)
{
	sprite->update(deltaTime);

	death = map2->deathcollisionB(posPlayer, glm::ivec2(11, 30), godMode, lavaWalk);
	map3->gemcollision(posPlayer, glm::ivec2(11, 32), jumpH, lavaWalk);


	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != MOVE_LEFT && sprite->animation() != JUMP_LEFT && sprite->animation() != JUMP_RIGHT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if (map1->collisionMoveLeft(posPlayer, glm::ivec2(11, 30)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT && sprite->animation() != JUMP_RIGHT && sprite->animation() != JUMP_LEFT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if (map1->collisionMoveRight(posPlayer, glm::ivec2(11, 30)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;

		if (map1->collisionMoveUpB(posPlayer, glm::ivec2(11, 30)))
		{
			bJumping = false;
		}

		
		else
		{
			if (jumpAngle < 120) posPlayer.y = int(startY + jumpH * sin(3.14159f * jumpAngle / 180.f));
			else posPlayer.y -= FALL_STEP;
			if (jumpAngle > 90) {
				bool downCondition;
				if (!lavaWalk) downCondition = map1->collisionMoveDownB(posPlayer, glm::ivec2(11, 32), &posPlayer.y, damuntMeta);
				else downCondition = map1->collisionMoveDownB(posPlayer, glm::ivec2(11, 32), &posPlayer.y, damuntMeta) || map2->lavaWalkB(posPlayer, glm::ivec2(11, 32), &posPlayer.y);

				bJumping = !downCondition;
			}
		}
	}
	else
	{
		if (sprite->animation() == JUMP_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == JUMP_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);

		posPlayer.y -= FALL_STEP;

		bool downCondition;
		if (!lavaWalk) downCondition = map1->collisionMoveDownB(posPlayer, glm::ivec2(11, 32), &posPlayer.y, damuntMeta);
		else downCondition = map1->collisionMoveDownB(posPlayer, glm::ivec2(11, 32), &posPlayer.y, damuntMeta) || map2->lavaWalkB(posPlayer, glm::ivec2(11, 32), &posPlayer.y);

		if (downCondition)
		{
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;

				if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
					sprite->changeAnimation(JUMP_LEFT);
				else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
					sprite->changeAnimation(JUMP_RIGHT);
			}
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}



