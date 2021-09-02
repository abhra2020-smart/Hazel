#include "AppWindow.h"



AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	b_isRunning = true;
	GraphicsEngine::get()->init();
}

void AppWindow::onUpdate()
{
}

void AppWindow::onDestroy()
{
	b_isRunning = false;
	GraphicsEngine::get()->release();
	exit(0);
}