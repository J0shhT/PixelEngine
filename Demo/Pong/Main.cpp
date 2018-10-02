#include <PixelEngine.h>

unsigned int score = 0;
Pixel::Sound ballCollideSound = Pixel::Sound("Content/Sounds/BallCollide.wav");

void OnMouseMove(const Pixel::InputEvent& e)
{
	auto paddle = std::dynamic_pointer_cast<Pixel::Object::PhysicalObject>(Pixel::SceneManager::Singleton()->GetObjectByName("Paddle"));
	paddle->SetPosition(PixelWorldPosition((int)e.mouseX - 400 - (paddle->GetSize().GetWidth() / 2), 250.0));
}

void OnBallCollide(const Pixel::Event e)
{
	auto ball = std::dynamic_pointer_cast<Pixel::Object::PhysicalObject>(e.object.lock());
	ball->SetVelocity(PixelVelocity(ball->GetVelocity().GetX(), -ball->GetVelocity().GetY()));
	Pixel::SoundService::Singleton()->PlaySound(ballCollideSound);
	score++;
}

void PongMain()
{
	Pixel::App* app = new Pixel::App();
	app->CreateWindow("Ping Pong", 800, 600);
	Pixel::RenderService::Singleton()->Initialize();

	Pixel::RenderService::Singleton()->SetBackgroundColor(PixelColor(0.0));

	auto scoreGui = PixelCreateGui(BasicTextGui);
	scoreGui->SetName("ScoreGui");
	scoreGui->SetText("Score: 0");
	scoreGui->SetTextColor(PixelColor(1.0, 1.0, 0.0));
	scoreGui->SetPosition(PixelPosition(0.01, 0.04));

	auto gameOverGui = PixelCreateGui(BasicTextGui);
	gameOverGui->SetName("GameOverGui");
	gameOverGui->SetText("GAME OVER!");
	gameOverGui->SetTextColor(PixelColor(1.0, 0.0, 0.0));
	gameOverGui->SetPosition(PixelPosition(0.435, 0.5));
	gameOverGui->SetVisible(false);

	auto paddle = PixelCreateObject(Rectangle);
	paddle->SetName("Paddle");
	paddle->SetColor(PixelColor(1.0));
	paddle->SetSize(PixelSize(100.0, 10.0));
	paddle->SetPosition(PixelWorldPosition(-25.0, 250.0));
	paddle->SetAnchored(true);
	paddle->SetSolid(true);

	auto ball = PixelCreateObject(Rectangle);
	ball->SetName("Ball");
	ball->SetColor(PixelColor(1.0));
	ball->SetSize(PixelSize(7.0, 7.0));
	ball->SetPosition(PixelWorldPosition(0.0, -250.0));
	ball->SetAnchored(false);
	ball->SetSolid(true);
	ball->SetVelocity(PixelVelocity(175.0, -200.0));
	auto OnBallCollideEventId = ball->Bind(Pixel::EventType::CollisionEvent, &OnBallCollide);

	ballCollideSound.volume = 2.0f;

	auto OnMouseMoveEventId = Pixel::UserInputService::Singleton()->Bind(Pixel::InputEventType::MouseMove, &OnMouseMove);

	app->SetWindowVisible(true);
	
	while (!app->CloseRequested())
	{
		scoreGui->SetText("Score: " + std::to_string(score));
		app->StepGame();
		if (ball->GetPosition().GetY() <= -300.0)
		{
			//Hit top of screen
			Pixel::SoundService::Singleton()->PlaySound(ballCollideSound);
			ball->SetVelocity(PixelVelocity(ball->GetVelocity().GetX(), -ball->GetVelocity().GetY()));
		}
		else if (ball->GetPosition().GetY() > paddle->GetPosition().GetY())
		{
			//Game over!
			ball->Unbind(Pixel::EventType::CollisionEvent, OnBallCollideEventId);
			Pixel::UserInputService::Singleton()->Unbind(Pixel::InputEventType::MouseMove, OnMouseMoveEventId);
			ball->SetVelocity(PixelVelocity(0.0));
			ball->SetAnchored(true);
			gameOverGui->SetVisible(true);
		}
		if (ball->GetPosition().GetX() >= 400.0 - (ball->GetSize().GetWidth() / 2))
		{
			//Hit right side of screen
			Pixel::SoundService::Singleton()->PlaySound(ballCollideSound);
			ball->SetVelocity(PixelVelocity(-ball->GetVelocity().GetX(), ball->GetVelocity().GetY()));
		}
		else if (ball->GetPosition().GetX() <= -400.0)
		{
			//Hit left side of screen
			Pixel::SoundService::Singleton()->PlaySound(ballCollideSound);
			ball->SetVelocity(PixelVelocity(abs(ball->GetVelocity().GetX()), ball->GetVelocity().GetY()));
		}
	}

	delete app;
}

PixelMain(PongMain);