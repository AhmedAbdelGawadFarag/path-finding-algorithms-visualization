#include "Menu.h"
#include <iostream>
Menu::Menu(RenderWindow *window,Maze *maze)
{
	//to populate the file names vector
	fileNames();

	this->window = window;
	this->maze = maze;

	for (int i = 0; i < MainMenuMaxElements; i++)
		mainMenu.push_back(new Text());
	for (int i = 0; i < OptionsMenuMaxElements; i++)
		optionsMenu.push_back(new Text());
	for (int i = 0; i < SolveMenuMaxElements; i++)
		solveMenu.push_back(new Text());

	this->width = window->getSize().x;
	this->height = window->getSize().y;

	this->font.loadFromFile("arial.ttf");
	
	//Main Menu
	mainMenu[0]->setFont(font);
	mainMenu[0]->setFillColor(Color::White);
	mainMenu[0]->setString("Generate maze ");

	mainMenu[1]->setFont(font);
	mainMenu[1]->setFillColor(Color::White);
	mainMenu[1]->setString("     Solve     ");

	mainMenu[2]->setFont(font);
	mainMenu[2]->setFillColor(Color::White);
	mainMenu[2]->setString(" Load From File");

	mainMenu[3]->setFont(font);
	mainMenu[3]->setFillColor(Color::White);
	mainMenu[3]->setString("  Save Maze   ");

	mainMenu[4]->setFont(font);
	mainMenu[4]->setFillColor(Color::White);
	mainMenu[4]->setString("   Options    ");

	mainMenu[5]->setFont(font);
	mainMenu[5]->setFillColor(Color::White);
	mainMenu[5]->setString("     Exit     ");

	//options Menu
	optionsMenu[0]->setFont(font);
	optionsMenu[0]->setFillColor(Color::White);
	optionsMenu[0]->setString("Back");

	optionsMenu[1]->setFont(font);
	optionsMenu[1]->setFillColor(Color::White);
	optionsMenu[1]->setString("Screen Mode : Default");

	optionsMenu[2]->setFont(font);
	optionsMenu[2]->setFillColor(Color::White);
	optionsMenu[2]->setString("Video Mode : 1366 X 768");

	optionsMenu[3]->setFont(font);
	optionsMenu[3]->setFillColor(Color::White);
	optionsMenu[3]->setString("Row Count : 30");


	optionsMenu[4]->setFont(font);
	optionsMenu[4]->setFillColor(Color::White);
	optionsMenu[4]->setString("Column Count : 45");

	optionsMenu[5]->setFont(font);
	optionsMenu[5]->setFillColor(Color::White);
	optionsMenu[5]->setString("Animation : ON");

	//Solve Menu
	solveMenu[0]->setFont(font);
	solveMenu[0]->setFillColor(Color::White);
	solveMenu[0]->setString("Back");

	solveMenu[1]->setFont(font);
	solveMenu[1]->setFillColor(Color::White);
	solveMenu[1]->setString("DFS");

	solveMenu[2]->setFont(font);
	solveMenu[2]->setFillColor(Color::White);
	solveMenu[2]->setString("BFS");

	solveMenu[3]->setFont(font);
	solveMenu[3]->setFillColor(Color::White);
	solveMenu[3]->setString("Best First");

	solveMenu[4]->setFont(font);
	solveMenu[4]->setFillColor(Color::White);
	solveMenu[4]->setString("Dijkstra");

	this->reSize();
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
	case MenuElement::SolveMenu:
		for (int i = 0; i < SolveMenuMaxElements; i++)
			window->draw(*this->solveMenu[i]);
		break;
	}
	
}

void Menu::moveUp()
{
	
	if (videoModeSelected)
	{
		--videoModeIndex;
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
	else if (filesSelected)
	{
		--filesIndex;
		if (filesIndex < 0)
			filesIndex = files.size() - 1;
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
	case MenuElement::SolveMenu:
		solveMenuCurrentIndex--;
		if (solveMenuCurrentIndex < 0)
			solveMenuCurrentIndex = SolveMenuMaxElements - 1;
		update();
		break;
	}
	
	
}

void Menu::moveDown()
{
	if (videoModeSelected)
	{
		++videoModeIndex;
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
	else if (filesSelected)
	{
		++filesIndex;
		if (filesIndex > files.size() - 1)
			filesIndex = 0;
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
	case MenuElement::SolveMenu:
		solveMenuCurrentIndex++;
		if (solveMenuCurrentIndex >= SolveMenuMaxElements)
			solveMenuCurrentIndex = 0;
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
	case MenuElement::SolveMenu:
		for (int i = 0; i < SolveMenuMaxElements; i++)
			solveMenu[i]->setFillColor(Color::White);

		solveMenu[solveMenuCurrentIndex]->setFillColor(Color::Red);
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
	if (filesSelected)
		mainMenu[2]->setString("File : " + files[filesIndex]);
}

void Menu::eventHandler(Event& event)
{
	if ( event.type != Event::KeyPressed )
		return;
	switch (event.key.code)
	{
	 case Keyboard::Key::Escape:
		 if (!mainState)
			 mainState = true;
		 if (currentMenu == MenuElement::SolveMenu)
			 break;
		 if(!rowSelected && !columnSelected && !videoModeSelected )
			 currentMenu = MenuElement::MainMenu;
		 break;
	 case Keyboard::Key::Up:
		 if (mainState)
			 moveUp();
		 break;
	 case Keyboard::Key::Down:
		 if (mainState)
			 moveDown();
		 break;
	 case Keyboard::Key::Enter:
		 if(mainState)
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
			maze->generate(cellCount);
			mainState = false;
			break;
		case MainMenuElementName::Solve:
			currentMenu = MenuElement::SolveMenu;
			solveMenuCurrentIndex = 0;
			break;
		case MainMenuElementName::Files:
			if (filesSelected)
			{
				maze->readFile(files[filesIndex]);
				mainState = false;
				filesSelected = false;
			}
			else
			{
				filesSelected = true;
			}
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
			this->reSize();
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
			this->reSize();
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

	case MenuElement::SolveMenu:
		
		switch (static_cast<SolveMenuElementName>(solveMenuCurrentIndex))
		{
		case SolveMenuElementName::Back:
			currentMenu = MenuElement::MainMenu;
			solveMenuCurrentIndex = -1;
			break;
		case SolveMenuElementName::DFS:
			mainState = false;
			maze->DFS();
			break;
		case SolveMenuElementName::BFS:
			mainState = false;
			maze->BFS();
			break;
		case SolveMenuElementName::BestFirst:
			maze->BestFirst();
			mainState = false;
			break;
		case SolveMenuElementName::Dijkstra:
			//call Dijkstra Function here
			maze->dijkstra();
			mainState = false;
			break;
		}
		break;
	}
	
}

void Menu::fileNames()
{
	for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
		if (entry.path().filename().extension() == ".txt")
			files.push_back(entry.path().filename().generic_string());	
}

void Menu::reSize()
{
	this->width = this->window->getSize().x;
	this->height = this->window->getSize().y;

	mainMenu[0]->setPosition(Vector2f(width * 0.45, (height / MainMenuMaxElements)       ));
	mainMenu[1]->setPosition(Vector2f(width * 0.45, (height / MainMenuMaxElements) + 85  ));
	mainMenu[2]->setPosition(Vector2f(width * 0.45, (height / MainMenuMaxElements) + 170 ));
	mainMenu[3]->setPosition(Vector2f(width * 0.45, (height / MainMenuMaxElements) + 255 ));
	mainMenu[4]->setPosition(Vector2f(width * 0.45, (height / MainMenuMaxElements) + 340 ));
	mainMenu[5]->setPosition(Vector2f(width * 0.45, (height / MainMenuMaxElements) + 425 ));

	optionsMenu[0]->setPosition(Vector2f(width * 0.45, (height / MainMenuMaxElements)      ));
	optionsMenu[1]->setPosition(Vector2f(width * 0.42, (height / MainMenuMaxElements) + 85 ));
	optionsMenu[2]->setPosition(Vector2f(width * 0.42, (height / MainMenuMaxElements) + 170 ));
	optionsMenu[3]->setPosition(Vector2f(width * 0.43, (height / MainMenuMaxElements) + 255 ));
	optionsMenu[4]->setPosition(Vector2f(width * 0.43, (height / MainMenuMaxElements) + 340 ));
	optionsMenu[5]->setPosition(Vector2f(width * 0.43, (height / MainMenuMaxElements) + 425 ));

	solveMenu[0]->setPosition(Vector2f(width * 0.45, height / SolveMenuMaxElements + 85 ));
	solveMenu[1]->setPosition(Vector2f(width * 0.45, height / SolveMenuMaxElements + 170 ));
	solveMenu[2]->setPosition(Vector2f(width * 0.45, height / SolveMenuMaxElements + 255 ));
	solveMenu[3]->setPosition(Vector2f(width * 0.45, height / SolveMenuMaxElements + 340 ));
	solveMenu[4]->setPosition(Vector2f(width * 0.45, height / SolveMenuMaxElements + 425 ));

}
