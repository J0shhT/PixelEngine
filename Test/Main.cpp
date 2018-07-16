#include <PixelEngine.h>

int main()
{

	Pixel::App app;
	app.CreateWindow("Pixel Engine Test", 800, 600);
	app.SetWindowVisible(true);
	app.SetDebugGuiEnabled(true);

	Pixel::HttpResponse response1 = Pixel::HttpService::Singleton()->Get("http://httpbin.org/get");
	std::cout << "GET TEST:" << std::endl;
	std::cout << "HTTP Status Code: " << response1.statusCode << std::endl;
	std::cout << "Body:" << std::endl << response1.body << std::endl;

	std::cout << std::endl;

	std::string data = "test=123";
	Pixel::HttpResponse response2 = Pixel::HttpService::Singleton()->Post("http://httpbin.org/post", data);
	std::cout << "POST TEST:" << std::endl;
	std::cout << "HTTP Status Code: " << response2.statusCode << std::endl;
	std::cout << "Body:" << std::endl << response2.body << std::endl;

	app.StartGameLoop();

	app.Close();
	
	printf("Press enter to exit...");
	getchar();
    return 0;
}
