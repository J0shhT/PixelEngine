#include <PixelEngine.h>

void Main()
{
	Pixel::App* app = new Pixel::App();
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

	app->StartGameLoop();

	delete app;
	
	PixelPrint("Press enter to exit...");
	getchar();
}

PixelMain(Main)