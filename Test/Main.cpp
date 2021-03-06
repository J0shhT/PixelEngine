#include <PixelEngine.h>

void TestInputFunction(const Pixel::InputEvent& e)
{
	if (e.key == Pixel::Key::KeySpace)
	{
		static Pixel::Sound testSound = Pixel::Sound("http://www.wavsource.com/snds_2018-06-03_5106726768923853/sfx/boing_x.wav");
		testSound.volume = 1.0f;
		Pixel::SoundService::Singleton()->PlaySound(testSound);
	}
}

void MouseClickEvent(const Pixel::InputEvent& e)
{
	PixelPrintf("Mouse clicked! (button %d) (%d, %d)", e.mouseButton, e.mouseX, e.mouseY);
}

void MouseMoveEvent(const Pixel::InputEvent& e)
{
	PixelPrintf("Mouse moved! (%d, %d)", e.mouseX, e.mouseY);
}

void CollisionEvent(const Pixel::Event e)
{
	auto object1 = e.object.lock();
	auto object2 = e.collidedObject.lock();
	PixelPrintf("Object \"%s\" collided with \"%s\"", object1->GetName().c_str(), object2->GetName().c_str());
	object1->Unbind(e.type, e.invoker);
}

void Main()
{
	Pixel::App* app = new Pixel::App(Pixel::WindowSubsystem::SDL);
	app->CreateWindow("Pixel Engine Test", 800, 600);
	app->SetWindowVisible(true);
	app->SetDebugGuiEnabled(true);

	Pixel::RenderService::Singleton()->Initialize();

	auto player = PixelCreateObject(Rectangle);
	player->SetName("Player");
	player->SetSize(PixelSize(30, 90));
	player->SetPosition(PixelWorldPosition(0, 0));
	player->SetTexture("Content/Textures/character.png");
	Pixel::PlayerController::Singleton()->ControlObject(player);
	Pixel::PlayerController::Singleton()->SetMoveSpeed(100);
	Pixel::RenderService::Singleton()->GetCurrentCamera()->SetTarget(player);
	Pixel::RenderService::Singleton()->GetCurrentCamera()->SetCameraType(Pixel::CameraType::Attach);
	player.reset();

	auto staticRectangle = PixelCreateObject(Rectangle);
	staticRectangle->SetName("StaticRectangle");
	staticRectangle->SetSize(PixelSize(100, 300));
	staticRectangle->SetPosition(PixelWorldPosition(-150, 0));
	staticRectangle->SetColor(PixelColor(0.8, 0.0, 0.5));
	staticRectangle->SetAnchored(true);
	staticRectangle.reset();

	auto movingRectangle = PixelCreateObject(Rectangle);
	movingRectangle->SetName("MovingRectangle");
	movingRectangle->SetSize(PixelSize(500, 500));
	movingRectangle->SetPosition(PixelWorldPosition(300, 150));
	movingRectangle->SetTexture("https://stonzeteam.github.io/assets/img/test_texture.png");
	movingRectangle->SetTextureMode(Pixel::TextureMode::Repeat);
	movingRectangle->SetTextureRepeat(10.0f);
	movingRectangle->SetVelocity(PixelVelocity(-60.0, 40.0));
	movingRectangle->Bind(Pixel::EventType::CollisionEvent, &CollisionEvent);
	movingRectangle.reset();

	auto testGui = PixelCreateGui(BasicTextGui);
	testGui->SetName("TestGui");
	testGui->SetText("Hello World :D!");
	testGui->SetTextColor(PixelColor(1.0f, 0.0f, 0.0f));
	testGui->SetPosition(PixelPosition(0.4f, 0.04f));
	testGui.reset();

	Pixel::UserInputService::Singleton()->Bind(Pixel::InputEventType::KeyDown, &TestInputFunction);
	Pixel::UserInputService::Singleton()->Bind(Pixel::InputEventType::MouseDown, &MouseClickEvent);

	std::string eventId = Pixel::UserInputService::Singleton()->Bind(Pixel::InputEventType::MouseMove, &MouseMoveEvent);
	Pixel::UserInputService::Singleton()->Unbind(Pixel::InputEventType::MouseMove, eventId);

	app->StartGameLoop();

	delete app;
	
	PixelPrint("Press enter to exit...");
	getchar();
}

PixelMain(Main)