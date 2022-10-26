
#include <cppLogger.h>
#include <vec3.h>
#include <colour.h>
#include <ray.h>


#define ERRORMSG(...) cppLogger::Logger::ERRORMSG(__VA_ARGS__)
#define INFOMSG(...)  cppLogger::Logger::INFOMSG(__VA_ARGS__)
#define DEBUGMSG(...) cppLogger::Logger::DEBUGMSG(__VA_ARGS__)

int main(int argc, char** argv)
{
	cppLogger::Logger::setPriority(cppLogger::LoggerPriority::Debug);
	cppLogger::Logger::LogOpen("logs.txt");
	INFOMSG("Hello World!");

	const auto aspectRatio = 16.0 / 9.0;
	const auto imageWidth = 1920;
	const auto imageHeight = static_cast<int> (imageWidth / aspectRatio);


	auto origin = point3(0, 0, 0);
	auto viewPortHeight = 2.0;
	auto viewPortWidth = viewPortHeight * aspectRatio;
	auto focalLen = 1.0;
	auto vertical = vec3(0, viewPortHeight, 0);
	auto horizontal = vec3(viewPortWidth, 0, 0);
	auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLen);

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	for (int j = imageHeight - 1; j >= 0; --j) {
		for (int i = 0; i < imageWidth; ++i) {
			auto u = double(i) / (imageWidth - 1);
			auto v = double(j) / (imageHeight - 1);
			ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
			colour pixelColour = rayColour(r);
			DEBUGMSG("%lf %lf %lf", pixelColour.x(), pixelColour.y(), pixelColour.z());
			writeColour(std::cout, pixelColour);
		}
	}
	cppLogger::Logger::LogClose();
	return 0;
}