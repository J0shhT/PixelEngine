#include <PixelEngine.h>

int main()
{

	Pixel::App* app = new Pixel::App();
	app->CreateWindow("Pixel Engine Test", 800, 600);
	app->SetWindowVisible(true);
	app->SetDebugGuiEnabled(true);

	Pixel::RenderService::Singleton()->Initialize();

	auto vertexShader = Pixel::Graphics::CreateShader(Pixel::Graphics::ShaderType::VertexShader);
	vertexShader->Load("J:/PixelEngine/Dev/Build_Release/Shaders/Vertex.glsl");
	Pixel::RenderService::Singleton()->AddShader(vertexShader);

	auto fragmentShader = Pixel::Graphics::CreateShader(Pixel::Graphics::ShaderType::FragmentShader);
	fragmentShader->Load("J:/PixelEngine/Dev/Build_Release/Shaders/Fragment.glsl");
	Pixel::RenderService::Singleton()->AddShader(fragmentShader);

	Pixel::RenderService::Singleton()->LinkShaders();



	auto scene = Pixel::SceneManager::Singleton();

	auto testObject = scene->CreateObject<Pixel::Object::Object>();
	std::string testObjectId = testObject->GetId();

	scene->GetObjectById(testObjectId)->SetName("TestObject");

	PixelPrintf("%s: %s (%s)", testObject->GetName().c_str(), testObject->GetId().c_str(), testObject->GetType());
	PixelPrintf("%f", testObject->GetAge());

	PixelDeleteObject(testObject);



	app->StartGameLoop();

	delete app;
	
	PixelPrint("Press enter to exit...");
	getchar();
    return 0;
}
