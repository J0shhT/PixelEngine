#include <PixelEngine.h>

int main()
{

	Pixel::App* app = new Pixel::App();
	app->CreateWindow("Pixel Engine Test", 800, 600);
	app->SetWindowVisible(true);
	app->SetDebugGuiEnabled(true);

	/* HttpService test */
	Pixel::HttpResponse response1 = Pixel::HttpService::Singleton()->Get("http://httpbin.org/get");
	PixelPrint(response1.body.c_str());
	PixelPrintln();

	std::string data = "test=123";
	Pixel::HttpResponse response2 = Pixel::HttpService::Singleton()->Post("http://httpbin.org/post", data);
	PixelPrint(response2.body.c_str());
	/* //////////////// */

	/* Game objects test */
	auto scene = Pixel::SceneManager::Singleton();

	auto testObject = scene->CreateObject<Pixel::Object::Object>();
	std::string testObjectId = testObject->GetId();

	scene->GetObjectById(testObjectId)->SetName("TestObject");

	PixelPrintf("%s: %s (%s)", testObject->GetName().c_str(), testObject->GetId().c_str(), testObject->GetType());
	PixelPrintf("%f", testObject->GetAge());

	PixelDeleteObject(testObject);
	/* ///////////////// */

	app->StartGameLoop();

	delete app;
	
	PixelPrint("Press enter to exit...");
	getchar();
    return 0;
}
