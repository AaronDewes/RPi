#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cinttypes>
#include <TFT/tft.h>
#include <TFT/conv.h>
#include "Graphic/shapes.h"
#include <ctime>
#include <pthread.h>
//#define CAPTURE
#define PICS	"/mnt/NFS/files/capture/"

class block: public object
{
public:
	block(class object *parent);
};

#define BLOCK_SIZE	24
block::block(class object *parent): object(parent)
{
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 2; y++) {
			for (int z = 0; z < 8; z++) {
				new cubeFrame(this, point(x * BLOCK_SIZE, -y * BLOCK_SIZE, z * BLOCK_SIZE), point(BLOCK_SIZE, -BLOCK_SIZE, BLOCK_SIZE), 0xFF0000);
				new cubeFrame(this, point(x * BLOCK_SIZE, -y * BLOCK_SIZE, -z * BLOCK_SIZE), point(BLOCK_SIZE, -BLOCK_SIZE, -BLOCK_SIZE), 0xFFFF00);
				new cubeFrame(this, point(-x * BLOCK_SIZE, -y * BLOCK_SIZE, z * BLOCK_SIZE), point(-BLOCK_SIZE, -BLOCK_SIZE, BLOCK_SIZE), 0x00FF00);
				new cubeFrame(this, point(-x * BLOCK_SIZE, -y * BLOCK_SIZE, -z * BLOCK_SIZE), point(-BLOCK_SIZE, -BLOCK_SIZE, -BLOCK_SIZE), 0x0000FF);
			}
}
}
}

void init()
{
	gpio_init();
	tft.init();
	tft /= tft.FlipLandscape;
	tft.setBackground(0x0000);
	tft.setForeground(0xFFFF);
	tft.clean();
	tft++;
}

auto main() -> int
{
	init();

	new block(gAxis);

/*	class object *cube = new object(gRoot, point(0, 40, -200));
	new cubeFrame(cube, point(-50, 50), point(100, -100, -100), 0xFF);

	class object *subAxis = new object(0, point(0, 0, -150), angle());
	(new cubeFrame(subAxis, point(5, 5, 5), point(20, 20, 20), 0x7F7F7F));//->showAxis(100);
	(new cubeFrame(subAxis, point(5, -5, 5), point(20, -20, 20), 0xFF0000));//->showAxis(100);
	(new cubeFrame(subAxis, point(-5, 5, 5), point(-20, 20, 20), 0x00FF00));//->showAxis(100);
	(new cubeFrame(subAxis, point(5, 5, -5), point(20, 20, -20), 0x0000FF));//->showAxis(100);
	(new cubeFrame(subAxis, point(-5, -5, 5), point(-20, -20, 20), 0xFF00FF));//->showAxis(100);
	(new cubeFrame(subAxis, point(5, -5, -5), point(20, -20, -20), 0x00FFFF));//->showAxis(100);
	(new cubeFrame(subAxis, point(-5, 5, -5), point(-20, 20, -20), 0xFFFF00));//->showAxis(100);
	(new cubeFrame(subAxis, point(-5, -5, -5), point(-20, -20, -20), 0xFFFFFF));//->showAxis(100);
	(new cubeFrame(subAxis, point(30, 30, 30), point(-60, -60, -60), 0x3F3F3F));//->showAxis(100);
	//(new gString(subAxis, point(0, 30, 0), angle(0, 0, 1.57079), 0x66CCFF, "Hello, world!"));//->showAxis(100);

*/	auto *str = new gString(nullptr, point(-107, 100), angle(), 0x66CCFF, "HelloWD!", 4.5);
	/*class sphereFrame *sph = *//*new sphereFrame(str, point(-30, 50, 0), 30, 0x66CCFF);
	new sphere(new sphereFrame(str, point(240, 50, 0), 30, 0x00FF00), point(), 20, 0xFF0000);
	new circle(str, point(-30, -15, 0), angle(), 30, true, 0xFF0000);
	new circle(str, point(240, -15, 0), angle(0, PI / 2), 30, false, 0x0000FF);*/
	//cube->setA(0.5);
	gAxis->setA(angle(0.5));
	gAxis->showAxis(100);
#ifdef CAPTURE
	int i = 0;
#endif
	pthread_t pid = 0;
	pthread_create(&pid, nullptr, tftUpdateThread, nullptr);
	while (true) {
		gRoot->show();
#ifdef CAPTURE
		char path[std::char_traits<char>::length(PICS ".bmp") + 7];
		sprintf(path, PICS "%06d.bmp", i++);
		scr::scrCapture(path);
#endif
		time_t timep = 0;
		time(&timep);
		std::string tstr(ctime(&timep) + 11);
		tstr.resize(8);
		str->setString(tstr);
		gAxis->setA(angle(0.5, gAxis->a().y() + 0.05, 0));
		if (gAxis->a().y() > 2 * PI) {
			gAxis->setA(0.5);
}
/*		subAxis->setA(angle(subAxis->a().x() + 0.1, subAxis->a().y() + 0.1, subAxis->a().z() + 0.1));
		if (subAxis->a().x() > 2 * PI)
			subAxis->setA();
*/		str->setA(angle(str->a().x() + 0.05, 0, 0));
		if (str->a().x() > 2 * PI) {
			str->setA();
}
/*		cube->setA(angle(0, 0, cube->a().z() + 0.05));
		if (cube->a().z() > 2 * PI)
			cube->setA(0);
*/		str->setColour(rand() % 0x1000000);
		//sph->setColour(rand() % 0x1000000);
		//gRoot->setColour(rand() % 0x1000000);
		usleep(1000);
	}
	pthread_detach(pid);
	gpio_close();
	return 0;
}
