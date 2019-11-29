#include "Menu.h"
#include <iostream>
Menu::Menu(RenderWindow *window,Maze *maze)
{
	this->window = window;
	this->maze = maze;

	for (int i = 0; i < MainMenuMaxElements; i++)
		mainMenu.push_back(new Text());
	for (int i = 0; i < OptionsMenuMaxElements; i++)
		optionsMenu.push_back(new Text());
	for (int i = 0; i < fileMenuSize; i++)
		filesMenu.push_back(new Text());

	float width = window->getSize().x;
	float height = window->getSize().y;

	this->font.loadFromFile("arial.ttf");
	
	//Main Menu
	mainMenu[0]->setFont(font);
	mainMenu[0]->setFillColor(Color::White);
	mainMenu[0]->setString("Generate maze");
	mainMenu[0]->setPosition(Vector2f(width * 0.45, height / (MainMenuMaxElements ) ));


	mainMenu[1]->setFont(font);
	mainMenu[1]->setFillColor(Color::White);
	mainMenu[1]->setString("Maze From File");
	mainMenu[1]->setPosition(Vector2f(width * 0.45, (height / MainMenuMaxElements) + 85));

	mainMenu[2]->setFont(font);
	mainMenu[2]->setFillColor(Color::White);
	mainMenu[2]->setString("Save Maze");
	mainMenu[2]->setPosition(Vector2f(width * 0.465, (height / MainMenuMaxElements) + 170));

	mainMenu[3]->setFont(font);
	mainMenu[3]->setFillColor(Color::White);
	mainMenu[3]->setString("Options");
	mainMenu[3]->setPosition(Vector2f(width * 0.48, (height / MainMenuMaxElements) + 255));


	mainMenu[4]->setFont(font);
	mainMenu[4]->setFillColor(Color::White);
	mainMenu[4]->setString("Exit");
	mainMenu[4]->setPosition(Vector2f(width * 0.495, (height / MainMenuMaxElements) + 340));

	//options Menu
	optionsMenu[0]->setFont(font);
	optionsMenu[0]->setFillColor(Color::White);
	optionsMenu[0]->setString("Back");
	optionsMenu[0]->setPosition(Vector2f(width * 0.45, (height / MainMenuMaxElements) ));

	optionsMenu[1]->setFont(font);
	optionsMenu[1]->setFillColor(Color::White);
	optionsMenu[1]->setString("Screen Mode : Default");
	optionsMenu[1]->setPosition(Vector2f(width * 0.42, (height / MainMenuMaxElements) + 85));

	optionsMenu[2]->setFont(font);
	optionsMenu[2]->setFillColor(Color::White);
	optionsMenu[2]->setString("Video Mode : 1366 X 768");
	optionsMenu[2]->setPosition(Vector2f(width * 0.42, (height / MainMenuMaxElements) + 170));

	optionsMenu[3]->setFont(font);
	optionsMenu[3]->setFillColor(Color::White);
	optionsMenu[3]->setString("Row Count : 30");
	optionsMenu[3]->setPosition(Vector2f(width * 0.43, (height / MainMenuMaxElements) + 255));


	optionsMenu[4]->setFont(font);
	optionsMenu[4]->setFillColor(Color::White);
	optionsMenu[4]->setString("Column Count : 45");
	optionsMenu[4]->setPosition(Vector2f(width * 0.43, (height / MainMenuMaxElements) + 340 ));

	optionsMenu[5]->setFont(font);
	optionsMenu[5]->setFillColor(Color::White);
	optionsMenu[5]->setString("Animation : ON");
	optionsMenu[5]->setPosition(Vector2f(width * 0.43, (height / MainMenuMaxElements) + 425 ));

	//File Menu Back 
	filesMenu[0]->setFont(font);
	filesMenu[0]->setFillColor(Color::White);
	filesMenu[0]->setString("Back");
	filesMenu[0]->setPosition(Vector2f(width * 0.45, (height / MainMenuMaxElements)));


}

Menu::~Menu()
{
	for (int i = 0; i < MainMenuMaxElements; i++)
		delete 	mainMenu[i];
}

void Menu::draw()
{
	switch (currentMenu)
	{
	case MenuElement::MainMenu:
		for (int i = 0; i < MainMenuMaxElements; i++)
			window->draw(*this->mainMenu[i]);
		break;
	case MenuElement::OptionsMenu:
		for (int i = 0; i < OptionsMenuMaxElements; i++)
			window->draw(*this->optionsMenu[i]);
		break;
	case MenuElement::FilesMenu:
		for (int i = 0; i < fileMenuSize ; i++)
			window->draw(*this->filesMenu[i]);
		break;
	
	}
	
}

void Menu::moveUp()
{
	
	if (videoModeSelected)
	{
		videoModeIndex--;
		if (videoModeIndex < 0)
			videoModeIndex = videoModes.size() - 1;
		updateText();
		return;
	}
	else if (rowSelected)
	{
		++cellCount.y;
		updateText();
	}
	else if (columnSelected)
	{
		++cellCount.x;
		updateText();
	}
	else
	switch (currentMenu)
	{
	case MenuElement::MainMenu:

		mainMenuCurrentIndex--;
	if (mainMenuCurrentIndex < 0) 
		 mainMenuCurrentIndex = MainMenuMaxElements - 1;
		update();
		break;

	case MenuElement::OptionsMenu:
		optionsMenuCurrentIndex--;
		if (optionsMenuCurrentIndex < 0) 
			optionsMenuCurrentIndex = OptionsMenuMaxElements - 1;	
		update();
		break;

	case MenuElement::FilesMenu:
		filesMenuCurrentIndex--;
		if (filesMenuCurrentIndex < 0)
			filesMenuCurrentIndex = fileMenuSize - 1;
		update();
		break;
	
	}
	
	
}

void Menu::moveDown()
{
	if (videoModeSelected)
	{
		videoModeIndex++;
		if (videoModeIndex > videoModes.size() - 1)
			videoModeIndex = 0;
		updateText();
		return;
	}
	else if (rowSelected)
	{
		--cellCount.y;
		updateText();
	}
	else if (columnSelected)
	{
		--cellCount.x;
		updateText();
	}
	else 
	switch (currentMenu)
	{
	case MenuElement::MainMenu:

		mainMenuCurrentIndex++;
		if (mainMenuCurrentIndex >= MainMenuMaxElements)
			mainMenuCurrentIndex = 0;
		update();
		break;

	case MenuElement::OptionsMenu:
		optionsMenuCurrentIndex++;
		if (optionsMenuCurrentIndex >= OptionsMenuMaxElements)
			optionsMenuCurrentIndex = 0;
		update();
		break;

	case MenuElement::FilesMenu:
		filesMenuCurrentIndex++;
		if (filesMenuCurrentIndex >= fileMenuSize)
			filesMenuCurrentIndex = 0;
		update();
		break;

	}
	
}

bool Menu::isOpen()
{
	return mainState;
}

void Menu::open()
{
	mainState = true;
}

void Menu::close()
{
	mainState = false;
}

void Menu::update()
{
	switch (currentMenu)
	{
	case MenuElement::MainMenu:
		for (int i = 0; i < MainMenuMaxElements; i++)
			mainMenu[i]->setFillColor(Color::White);

		mainMenu[mainMenuCurrentIndex]->setFillColor(Color::Red);
		break;

	case MenuElement::OptionsMenu:
		for (int i = 0; i < OptionsMenuMaxElements; i++)
			optionsMenu[i]->setFillColor(Color::White);

		optionsMenu[optionsMenuCurrentIndex]->setFillColor(Color::Red);
		break;

	case MenuElement::FilesMenu:
		for (int i = 0; i < fileMenuSize; i++)
			filesMenu[i]->setFillColor(Color::White);

		filesMenu[filesMenuCurrentIndex]->setFillColor(Color::Red);
		break;
	}
	
}

void Menu::updateText()
{
	if (animation == Animation::ON)
		optionsMenu[5]->setString("Animation : ON");
	if (animation == Animation::OFF)
		optionsMenu[5]->setString("Animation : OFF");
	if (screenMode == ScreenMode::Default)
		optionsMenu[1]->setString("Screen Mode : Default");
	if (screenMode == ScreenMode::FullScreen)
		optionsMenu[1]->setString("Screen Mode : FullScreen");
	if (videoModeSelected)
		optionsMenu[2]->setString( "Video Mode :" + std::to_string( videoModes[videoModeIndex].width ) + " X " + std::to_string(videoModes[videoModeIndex].height) );
	if (rowSelected)
		optionsMenu[3]->setString("Row Count : " + std::to_string(cellCount.y));
	if (columnSelected)
		optionsMenu[4]->setString("Column Count : " + std::to_string(cellCount.x));
}

int Menu::checked()
{
	return  mainMenuCurrentIndex;
}

void Menu::eventHandler(Event& event)
{
	if ( event.type != Event::KeyReleased )
		return;
	switch (event.key.code)
	{
	 case Keyboard::Key::Escape:
		 if (!mainState)
			 mainState = true;
		 currentMenu = MenuElement::MainMenu;
		 break;
	 case Keyboard::Key::Up:
		 moveUp();
		 break;
	 case Keyboard::Key::Down:
		 moveDown();
		 break;
	 case Keyboard::Key::Enter:
		 onAction();
		 break;
		
	}
}

void Menu::onAction()
{
	switch (currentMenu)
	{
	case MenuElement::MainMenu:

		switch ( static_cast<MainMenuElementName>(mainMenuCurrentIndex) )
		{
		case MainMenuElementName::Generate:
			maze->generate(static_cast<Vector2f>(window->getSize()), cellCount);
			mainState = false;
			break;

		case MainMenuElementName::Files:
			currentMenu = MenuElement::FilesMenu;
			filesMenuCurrentIndex = 0;
			update();
			break;

		case MainMenuElementName::Save:

			break;

		case MainMenuElementName::Options:
			currentMenu = MenuElement::OptionsMenu;
			optionsMenuCurrentIndex = 0;
			update();
			break;

		case MainMenuElementName::Exit:
			window->close();
			break;
		}
		break;

	case MenuElement::OptionsMenu:

		switch ( static_cast<OptionsMenuElementName>(optionsMenuCurrentIndex) )
		{
		case OptionsMenuElementName::Back:
			currentMenu = MenuElement::MainMenu;
			optionsMenuCurrentIndex = -1;
			break;
		case OptionsMenuElementName::ScreenMode:
			if (screenMode == ScreenMode::Default)
			{
				screenMode = ScreenMode::FullScreen;
				window->create(videoModes[videoModeIndex], "Maze Runner!", Style::Fullscreen);
			}
			else
			{
				screenMode = ScreenMode::Default;
				window->create(videoModes[videoModeIndex], "Maze Runner!", Style::Default);
			}
			updateText();
			break;
		case OptionsMenuElementName::ScreenRes:
			if (videoModeSelected)
			{
				if (screenMode == ScreenMode::Default)
				window->create(videoModes[videoModeIndex], "Maze Runner!", Style::Default);
				else
				window->create(videoModes[videoModeIndex], "Maze Runner!", Style::Fullscreen);

				videoModeSelected = false;
			}
			else
				videoModeSelected = true;

			break;
		case OptionsMenuElementName::RowCount:
			rowSelected = !rowSelected;
			break;

		case OptionsMenuElementName::ColumnCount:
			columnSelected = !columnSelected;
			break;

		case OptionsMenuElementName::Animation:
			if (animation == Animation::ON)
			{
				animation = Animation::OFF;
				maze->animation = false;
			}
			else
			{
				animation = Animation::ON;
				maze->animation = true;
			}
			updateText();
			break;
	
		}
		break;

	case MenuElement::FilesMenu:
		switch (filesMenuCurrentIndex)
		{
		case 0:
			currentMenu = MenuElement::MainMenu;
			filesMenuCurrentIndex = -1;
		default:
			mainState = false;
			break;
		}
		break;
	
	}
}
