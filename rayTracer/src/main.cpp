#include <utils.h>
#include <hittableList.h>
#include <sphere.h>
#include <camera.h>
#include <material.h>

hittableList randomScene()
{
	hittableList world;

	auto groundMaterial = make_shared<lambertian>(colour(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, groundMaterial));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = randomDouble();
			point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = vec3::random() * vec3::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = vec3::random(0.5, 1);
					auto fuzz = randomDouble(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(colour(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(colour(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}

struct RowGroupData
{
	int startRow, endRow;
	std::vector<unsigned long long> pixelIndex;
	std::vector<colour> pixelColour;
};

void RenderImage(RowGroupData threadRowGroup, std::vector<RowGroupData>& rowGroups, std::mutex& rowGroupsMutex, std::atomic<int>& finishedThreadsCount, std::condition_variable& isRenderingDone, const int& imageHeight, const int& imageWidth, const int& samplesPerPixel, const int& maxDepth, const camera& cam, const hittableList& world)
{
	INFOMSG("Thread starting.");
	for (int j = threadRowGroup.startRow; j < threadRowGroup.endRow; ++j) {
		for (int i = 0; i < imageWidth; ++i) {

			colour pixelColour(0, 0, 0);

			for (int s = 0; s < samplesPerPixel; ++s)
			{
				auto u = (i + randomDouble()) / (imageWidth - 1);
				auto v = (j + randomDouble()) / (imageHeight - 1);
				ray r = cam.getRay(u, v);
				pixelColour += rayColour(r, world, maxDepth);
			}
			unsigned long long index = j * imageWidth + (imageWidth - i);
			threadRowGroup.pixelIndex.push_back(index);
			threadRowGroup.pixelColour.push_back(pixelColour);
		}
	}

	{
		std::scoped_lock<std::mutex> lock(rowGroupsMutex);
		rowGroups.push_back(threadRowGroup);
		finishedThreadsCount += 1;
		INFOMSG("Thread has finished.");
		isRenderingDone.notify_one();
	}
}

int main(int argc, char** argv)
{
	cppLogger::Logger::LogOpen("logs.txt");

	//Image Details
	const auto aspectRatio = 16.0 / 9.0;
	const auto imageWidth = 1280;
	const auto imageHeight = static_cast<int> (imageWidth / aspectRatio);
	const int samplesPerPixel = 30;
	const int maxDepth = 10;
	INFOMSG("Resolution: %d x %d", imageWidth, imageHeight);
	INFOMSG("Samples per pixel: %d", samplesPerPixel);

	//Setting the scene
	auto world = randomScene();
	INFOMSG("Scene set.");

	//Camera Details
	point3 lookFrom(13, 2, 3);
	point3 lookAt(0, 0, 0);
	vec3 viewUp(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;

	camera cam(lookFrom, lookAt, viewUp, 20, aspectRatio, aperture, dist_to_focus);
	INFOMSG("Camera set.");

	//Rendering
	int threadCount = std::thread::hardware_concurrency() / 2;
	INFOMSG("Total threads: %d", threadCount);
	int rowsPerThread = imageHeight / threadCount;
	int rowsLeftOver = imageHeight % threadCount;

	std::vector<std::thread> threads;
	std::vector<RowGroupData> rowGroups;
	std::mutex rowGroupsMutex;
	std::atomic<int> finishedThreadsCount = { 0 };
	std::condition_variable isRenderingDone;

	for (int threadID = 0; threadID < threadCount; ++threadID)
	{
		RowGroupData threadRowGroup;

		threadRowGroup.startRow = threadID * rowsPerThread;
		threadRowGroup.endRow = threadRowGroup.startRow + rowsPerThread;

		if (threadID == threadCount - 1)
		{
			threadRowGroup.endRow = threadRowGroup.startRow + rowsPerThread + rowsLeftOver;
		}

		std::thread t([threadRowGroup, &rowGroups, &rowGroupsMutex, &finishedThreadsCount, &isRenderingDone, &imageHeight, &imageWidth, &samplesPerPixel, &maxDepth, &cam, &world]()
			{
				RenderImage(threadRowGroup, rowGroups, rowGroupsMutex, finishedThreadsCount, isRenderingDone, imageHeight, imageWidth, samplesPerPixel, maxDepth, cam, world);
			}
		);
		threads.push_back(std::move(t));
	}

	{
		std::unique_lock<std::mutex> lock(rowGroupsMutex);
		isRenderingDone.wait(lock, [&finishedThreadsCount, &threadCount]
			{
				return finishedThreadsCount == threadCount;
			}
		);
	}

	for (auto& t : threads)
	{
		t.join();
	}

	INFOMSG("All the threads have joined.");

	int totalPixelCount = imageHeight * imageWidth;
	std::vector<colour> imageData(totalPixelCount);
	
	for (auto& threadRowGroup : rowGroups)
	{
		for (int idx = 0; idx < threadRowGroup.pixelIndex.size(); ++idx)
		{
			imageData[threadRowGroup.pixelIndex[idx]] = threadRowGroup.pixelColour[idx];
		}
	}

	std::ofstream imageFile;
	imageFile.open("image.ppm", std::ios::binary);

	if (!imageFile.is_open())
	{
		ERRORMSG("Failed to load the file, exiting.");
		return 1;
	}

	imageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int idx = imageData.size() - 1; idx >= 0; --idx)
	{
		writeColour(imageFile, imageData[idx], samplesPerPixel);
	}

	INFOMSG("Image created successfully.");

	imageFile.close();
	cppLogger::Logger::LogClose();
	return 0;
}