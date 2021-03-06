/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Object/Rectangle.cpp
*/

#include "Include/Object/Rectangle.h"

#include "Include/PixelOutput.h"

#include "Include/Graphics/RenderService.h"

#include "Include/Core/SceneManager.h"

PIXEL_DECLARE_OBJECT(Rectangle);

Pixel::Object::Rectangle::Rectangle()
{
	PIXEL_OBJECT_CONSTRUCTOR(Rectangle);
}

Pixel::Object::Rectangle::~Rectangle()
{
	PIXEL_OBJECT_DECONSTRUCTOR(Rectangle);
}

void Pixel::Object::Rectangle::StepPhysics(double frameDelta)
{
	if (IsAnchored())
		return;
	Pixel::Type::Position position = GetPosition();
	Pixel::Type::Velocity velocity = GetVelocity();
	if (velocity.GetMagnitude() != 0.0)
	{
		//Collision check
		///todo: move all collision detection into PhysicsService?
		_checkCollisions();

		position = GetPosition();
		velocity = GetVelocity();
		double xPosition = position.GetX();
		double yPosition = position.GetY();
		double xVelocity = velocity.GetX();
		double yVelocity = velocity.GetY();

		if (_hasCollisionTop && yVelocity < 0.0)
		{
			yVelocity = 0.0;
		}
		if (_hasCollisionBottom && yVelocity > 0.0)
		{
			yVelocity = 0.0;
		}
		if (_hasCollisionLeft && xVelocity < 0.0)
		{
			xVelocity = 0.0;
		}
		if (_hasCollisionRight && xVelocity > 0.0)
		{
			xVelocity = 0.0;
		}

		//Update object position
		//position = position + velocity * frameDelta
		SetPosition(Pixel::Type::WorldPosition(xPosition + xVelocity * frameDelta, yPosition - yVelocity * frameDelta));
	}
}

void Pixel::Object::Rectangle::Render()
{
	static Pixel::RenderService* renderService = Pixel::RenderService::Singleton();

	Pixel::Type::WorldPosition position = GetPosition();
	Pixel::Type::Size size = GetSize();
	Pixel::Type::Color color = GetColor();

	//Projection
	glm::mat4 worldSpaceMatrix = glm::translate(glm::mat4(), glm::vec3((float)position.GetX(), (float)position.GetY(), 0.0f));
	glm::mat4 cameraSpaceMatrix = renderService->GetCameraMatrix();
	glm::mat4 projectionMatrix = renderService->GetProjectionMatrix();
	glm::mat4 worldViewMatrix = projectionMatrix * cameraSpaceMatrix * worldSpaceMatrix;
	static GLuint matrixId = glGetUniformLocation(renderService->GetProgram(), "worldViewMatrix");
	glUniformMatrix4fv(matrixId, 1, GL_FALSE, &worldViewMatrix[0][0]);

	//Vertices for rectangle (at origin)
	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, (float)size.GetHeight(), 0,
		(float)size.GetWidth(), (float)size.GetHeight(), 0,

		0.0f, 0.0f, 0.0f,
		(float)size.GetWidth(), (float)size.GetHeight(), 0,
		(float)size.GetWidth(), 0, 0
	};

	//Colors
	GLfloat colors[] = {
		(float)color.GetRed(), (float)color.GetGreen(), (float)color.GetBlue(),
		(float)color.GetRed(), (float)color.GetGreen(), (float)color.GetBlue(),
		(float)color.GetRed(), (float)color.GetGreen(), (float)color.GetBlue(),

		(float)color.GetRed(), (float)color.GetGreen(), (float)color.GetBlue(),
		(float)color.GetRed(), (float)color.GetGreen(), (float)color.GetBlue(),
		(float)color.GetRed(), (float)color.GetGreen(), (float)color.GetBlue()
	};

	//Texture
	GLfloat texCoords[12];
	if (GetTextureMode() == Pixel::TextureMode::Stretch)
	{
		/*
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		*/
		texCoords[0] = 0.0f;
		texCoords[1] = 0.0f;
		texCoords[2] = 0.0f;
		texCoords[3] = 1.0f;
		texCoords[4] = 1.0f;
		texCoords[5] = 1.0f;
		texCoords[6] = 0.0f;
		texCoords[7] = 0.0f;
		texCoords[8] = 1.0f;
		texCoords[9] = 1.0f;
		texCoords[10] = 1.0f;
		texCoords[11] = 0.0f;
	}
	else if (GetTextureMode() == Pixel::TextureMode::Repeat)
	{
		texCoords[0] = 0.0f;
		texCoords[1] = 0.0f;
		texCoords[2] = 0.0f;
		texCoords[3] = _textureRepeatY;
		texCoords[4] = _textureRepeatX;
		texCoords[5] = _textureRepeatY;
		texCoords[6] = 0.0f;
		texCoords[7] = 0.0f;
		texCoords[8] = _textureRepeatX;
		texCoords[9] = _textureRepeatY;
		texCoords[10] = _textureRepeatX;
		texCoords[11] = 0.0f;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//GLfloat borderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Send vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//Send color
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _colorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//Send texture
	glEnableVertexAttribArray(2);
	static GLuint hasTextureId = glGetUniformLocation(renderService->GetProgram(), "hasTexture");
	int hasTexture = 0;
	if (_texture != "")
	{
		auto textureContent = Pixel::ContentProvider::Singleton()->Get(_texture);
		if (textureContent->type == ContentType::Texture)
		{
			if (!renderService->IsWireframeEnabled())
			{
				glBindTexture(GL_TEXTURE_2D, textureContent->glTextureId);
				hasTexture = 1;
			}
		}
	}
	if (hasTextureId != -1)
	{
		glUniform1i(hasTextureId, hasTexture);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _textureBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//Draw
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Pixel::Object::Rectangle::_checkCollisions()
{
	bool hasCollisionTop = false;
	bool hasCollisionBottom = false;
	bool hasCollisionRight = false;
	bool hasCollisionLeft = false;

	auto gameObjects = Pixel::SceneManager::Singleton()->GetObjects();
	for (auto iter = gameObjects.cbegin(); iter != gameObjects.cend(); iter++)
	{
		if (iter->second->IsA<Pixel::Object::PhysicalObject>())
		{
			std::shared_ptr<Pixel::Object::PhysicalObject> physicsObject = std::dynamic_pointer_cast<Pixel::Object::PhysicalObject>(iter->second);
			if (GetId() != physicsObject->GetId())
			{

				//Construct bounding box
				struct AABB {
					double x1;
					double x2;
					double y1;
					double y2;
				} a, b;
				a.x1 = GetPosition().GetX();
				a.x2 = GetPosition().GetX() + GetSize().GetWidth();
				a.y1 = GetPosition().GetY();
				a.y2 = GetPosition().GetY() + GetSize().GetHeight();
				b.x1 = physicsObject->GetPosition().GetX();
				b.x2 = physicsObject->GetPosition().GetX() + physicsObject->GetSize().GetWidth();
				b.y1 = physicsObject->GetPosition().GetY();
				b.y2 = physicsObject->GetPosition().GetY() + physicsObject->GetSize().GetHeight();

				//Overlap test
				bool isTouching = false;
				if (a.x2 >= b.x1 && a.x1 <= b.x2)
				{
					if (a.y2 >= b.y1 && a.y1 <= b.y2)
					{
						isTouching = true;
					}
				}

				if (IsSolid() && physicsObject->IsSolid())
				{
					//Determine touched side
					if (isTouching)
					{
						//Side clamp
						double clampToRightJump = abs(a.x1 - b.x2);
						double clampToLeftJump = abs(a.x2 - b.x1);
						double clampToTopJump = abs(a.y2 - b.y1);
						double clampToBottomJump = abs(a.y1 - b.y2);
						auto clampJumps = { clampToRightJump, clampToLeftJump, clampToTopJump, clampToBottomJump };
						if ((std::min)(clampJumps) == clampToRightJump)
						{
							_position.SetX(b.x2);
							hasCollisionLeft = true;
						}
						else if ((std::min)(clampJumps) == clampToLeftJump)
						{
							_position.SetX(b.x1 - this->GetSize().GetWidth());
							hasCollisionRight = true;
						}
						else if ((std::min)(clampJumps) == clampToTopJump)
						{
							_position.SetY(b.y1 - this->GetSize().GetHeight());
							hasCollisionTop = true;
						}
						else if ((std::min)(clampJumps) == clampToBottomJump)
						{
							_position.SetY(b.y2);
							hasCollisionBottom = true;
						}
					}
					if (isTouching)
					{
						//Object is colliding, invoke CollisionEvent
						Pixel::Event e = Pixel::Event();
						e.type = Pixel::EventType::CollisionEvent;
						e.object = weak_from_this();
						e.collidedObject = physicsObject;
						_invokeEvent(e);
					}
				}
				else
				{
					if (isTouching)
					{
						//Object isn't collidable, but is overlapping, invoke IntersectionEvent
						Pixel::Event e = Pixel::Event();
						e.type = Pixel::EventType::IntersectionEvent;
						e.object = weak_from_this();
						e.collidedObject = physicsObject;
						_invokeEvent(e);
					}
				}
			}
		}
	}

	_hasCollisionTop = hasCollisionTop;
	_hasCollisionBottom = hasCollisionBottom;
	_hasCollisionLeft = hasCollisionLeft;
	_hasCollisionRight = hasCollisionRight;
}