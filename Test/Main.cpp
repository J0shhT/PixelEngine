#include <PixelEngine.h>

void Main()
{
	Pixel::App* app = new Pixel::App();
	app->CreateWindow("Pixel Engine Test", 800, 600);
	app->SetWindowVisible(true);
	app->SetDebugGuiEnabled(true);

	Pixel::RenderService::Singleton()->Initialize();

	auto rectangle = PixelCreateObject(Rectangle);
	rectangle->SetName("TestRectangle");
	rectangle->SetSize(PixelSize(300, 100));
	rectangle->SetPosition(PixelWorldPosition(400, 300));
	rectangle->SetColor(PixelColor(0.0, 0.0, 1.0));

	app->StartGameLoop();

	delete app;
	
	PixelPrint("Press enter to exit...");
	getchar();
}

PixelMain(Main)