#include <PixelEngine.h>

void TestInputFunction(const Pixel::InputEvent& e)
{
	if (e.key == Pixel::Key::KeySpace)
	{
		PixelPrint("Space was pressed!");
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

void Main()
{
	Pixel::App* app = new Pixel::App(Pixel::WindowSubsystem::SDL);
	app->CreateWindow("Pixel Engine Test", 800, 600);
	app->SetWindowVisible(true);
	app->SetDebugGuiEnabled(true);

	Pixel::RenderService::Singleton()->Initialize();

	auto staticRectangle = PixelCreateObject(Rectangle);
	staticRectangle->SetName("StaticRectangle");
	staticRectangle->SetSize(PixelSize(100, 300));
	staticRectangle->SetPosition(PixelWorldPosition(100, 150));
	staticRectangle->SetColor(PixelColor(0.8, 0.0, 0.5));
	staticRectangle->SetAnchored(true);
	staticRectangle.reset();

	auto movingRectangle = PixelCreateObject(Rectangle);
	movingRectangle->SetName("MovingRectangle");
	movingRectangle->SetSize(PixelSize(300, 100));
	movingRectangle->SetPosition(PixelWorldPosition(400, 300));
	movingRectangle->SetColor(PixelColor(0.5, 0.0, 0.8));
	movingRectangle->SetVelocity(PixelVelocity(-60.0, 40.0));
	movingRectangle.reset();

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