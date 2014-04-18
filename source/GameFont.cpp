#include "stdafx.h"
#include "GameFont.h"
#include "Location.h"
#include "Colour.h"

HDC GameFont::m_device_context = NULL;

GameFont::GameFont() : m_list_base_index(0), m_font(NULL)
{
}

GameFont::~GameFont()
{
	if (m_list_base_index)
		glDeleteLists(m_list_base_index, 255);
	DeleteObject(m_font);
}

void GameFont::set_device_context(HDC device_context)  
{ 
	m_device_context = device_context; 
}

void GameFont::create_font(const std::string& font_name, int height, int weight)
{
	if (!m_device_context)
	{
		std::string strerror = "Impossible to create the font: ";
		strerror += font_name;
		strerror += ".\nReason: no device context.";
		throw Exception(strerror);
		return;
	}

	m_list_base_index = glGenLists(255);
	if (m_list_base_index == 0)
	{
		std::string strError = "Impossible to create the font: ";
		strError += font_name;
		strError += ".\nReason: list base is zero.";
		throw Exception(strError);
		return;
	}

	m_font = ::CreateFont(-height,
								  0,
								  0,
								  0,
								  weight,
								  FALSE,
								  FALSE,
								  FALSE,
								  ANSI_CHARSET,
								  OUT_TT_PRECIS,
								  CLIP_DEFAULT_PRECIS,
								  ANTIALIASED_QUALITY,
								  FF_DONTCARE|DEFAULT_PITCH,
								  font_name.c_str());
	if (m_font == NULL)
	{
		m_list_base_index = 0;
		std::string strError = "Impossible to create the font: ";
		strError += font_name;
		strError += ".\nReason: m_font is null.";
		throw Exception(strError);
		return;
	}

	HFONT old_font = (HFONT)SelectObject(m_device_context, m_font);
	wglUseFontBitmaps(m_device_context, 0, 255, m_list_base_index);	
	SelectObject(m_device_context, old_font);	
}

Rectangle_int GameFont::get_text_size(const std::string& font_name)
{
	SIZE text_size;
	HFONT old_font = (HFONT)SelectObject(m_device_context, m_font);
	GetTextExtentPoint32(m_device_context, font_name.c_str(), (int)font_name.size(), &text_size);
	SelectObject(m_device_context, old_font);	

	Rectangle_int new_text_size(0, text_size.cy, 0, text_size.cx);
	return new_text_size;
}

void GameFont::draw_text(const std::string& font_name, Location* location_p, Colour* font_colour)
{
	if (m_list_base_index == 0)
	{
		throw Exception("Impossible to diplay the text.\nReason: list base is zero.");
		return;
	}

	glDisable(GL_TEXTURE_2D);
	glColor3ub(font_colour->red, font_colour->green, font_colour->blue);
	glRasterPos2i(location_p->x_position, location_p->y_position);
	glPushAttrib(GL_LIST_BIT);
		glListBase(m_list_base_index);
		glCallLists((GLsizei)font_name.size(), GL_UNSIGNED_BYTE, (GLubyte *)font_name.c_str());
    glPopAttrib();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
}
