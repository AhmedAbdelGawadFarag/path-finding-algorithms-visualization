#include "TextBox.h"

void TextBox::draw(RenderWindow& window)
{
	window.draw(textbox);
}

Text TextBox::getText()
{
	return textbox;
}

void TextBox::setPos(Vector2f pos)
{
	textbox.setPosition(pos);
}

TextBox::TextBox(Vector2f pos)
{
	textbox.setFillColor(Color::White);
	textbox.setCharacterSize(4);

	textbox.setPosition(pos);

}

void TextBox::deleteLastChar()
{
	std::string s = text.str();
	std::string newS = "";
	for (int i = 0; i < s.length() - 1; i++) 
		newS += s[i];

	text.str("");
	text << newS;
	textbox.setString(text.str());
}

void TextBox::type(int charTyped)
{
	if (charTyped != DELETE )
	{
		text << static_cast<char>(charTyped);
	}
	
	else if (charTyped == DELETE ) 
	{
		if (text.str().length() > 0) 
		{
			deleteLastChar();
		}
	}
	
	textbox.setString(text.str());
}

void TextBox::input(Event evnt)
{
	int charTyped = evnt.text.unicode;
	if (charTyped >= 48 && charTyped <= 57)
	{
		if (text.str().length() <= LIMIT) 
		{
			type(charTyped);
		}
		else if (charTyped == DELETE)
		{
			deleteLastChar();
		}
	}
}
