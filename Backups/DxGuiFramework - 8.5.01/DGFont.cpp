/*------------------------------------------------------------------------
File Name: DGFont.cpp
Description: This file contains the implementation of the DGFont class,
	which represents a font that is used in drawing text on the screen.
Version:
   1.0.0    10.03.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

//Default Constructor
DGFont::DGFont()
{
   strcpy(fontName, "MS Sans Serif");
   weight = FW_NORMAL;
   italic = FALSE;
   underline = FALSE;
   strikeout = FALSE;
   width = 0;
   height = 0;
   escapement = 0;
   orientation = 0;
   charSet = DEFAULT_CHARSET;
   outPrecision = OUT_CHARACTER_PRECIS;
   clipPrecision = CLIP_CHARACTER_PRECIS;
   quality = DEFAULT_QUALITY;
   pitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

   fontHandle = CreateFont(height, width, escapement, orientation, weight,
      italic, underline, strikeout, charSet, outPrecision, clipPrecision,
      quality, pitchAndFamily, fontName);

   if(fontHandle == NULL)
   {
      char errorMsg[64];
      sprintf(errorMsg, "The font \"%s\" could not be created.");
      throw(new DGException(errorMsg, EC_CREATEFONT, ET_FONT, __FILE__,
         __LINE__));
   }
}

/*------------------------------------------------------------------------
Function Name: Constructor
Parameters:
   const char* p_FontName : the name of the font to create
   int p_pointSize : the point size of the font to create, from 0 to 72
   int p_weight : the thickness of the font to be created, acceptable
      values are FW_DONTCARE, FW_THIN, FW_EXTRALIGHT, FW_LIGHT, 
      FW_NORMAL, FW_MEDIUM, FW_SEMIBOLD, FW_BOLD, FW_EXTRABOLD, FW_HEAVY
   bool p_italic : whether an italicized font should be created
   bool p_underlined : whether an underlined font should be created
   bool p_strikeout : whether an strikeout font should be created
------------------------------------------------------------------------*/

DGFont::DGFont(const char* p_fontName, int p_height, int p_weight,
      bool p_italic, bool p_underline, bool p_strikeout)
{
   strcpy(fontName, p_fontName);
   weight = p_weight;
   italic = p_italic;
   underline = p_underline;
   strikeout = p_strikeout;
   width = 0;
   height = p_height;
   escapement = 0;
   orientation = 0;
   charSet = DEFAULT_CHARSET;
   outPrecision = OUT_CHARACTER_PRECIS;
   clipPrecision = CLIP_CHARACTER_PRECIS;
   quality = DEFAULT_QUALITY;
   pitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

   fontHandle = CreateFont(height, width, escapement, orientation, weight,
      italic, underline, strikeout, charSet, outPrecision, clipPrecision,
      quality, pitchAndFamily, fontName);

   if(fontHandle == NULL)
   {
      char errorMsg[64];
      sprintf(errorMsg, "The font \"%s\" could not be created.");
      throw(new DGException(errorMsg, EC_CREATEFONT, ET_FONT, __FILE__,
         __LINE__));
   }
}


//Overloads the '=' operator
DGFont& DGFont::operator=(DGFont& font)
{
   strcpy(fontName, font.fontName);
   weight = font.weight;
   italic = font.italic;
   underline = font.underline;
   strikeout = font.strikeout;
   width = font.width;
   height = font.height;
   escapement = font.escapement;
   orientation = font.orientation;
   charSet = font.charSet;
   outPrecision = font.outPrecision;
   clipPrecision = font.clipPrecision;
   quality = font.quality;
   pitchAndFamily = font.pitchAndFamily;
   
   DeleteObject(fontHandle);

   fontHandle = CreateFont(height, width, escapement, orientation, weight,
      italic, underline, strikeout, charSet, outPrecision, clipPrecision,
      quality, pitchAndFamily, fontName);

   if(fontHandle == NULL)
   {
      char errorMsg[64];
      sprintf(errorMsg, "The font \"%s\" could not be created.");
      throw(new DGException(errorMsg, EC_CREATEFONT, ET_FONT, __FILE__,
         __LINE__));
   }

   return *this;
}

//Destructor
DGFont::~DGFont()
{
   DeleteObject(fontHandle);
}

/*------------------------------------------------------------------------
Function Name: SetNewDC
Parameters:
   HDC hDC : handle to the new device context
Description:
   This function is to be called by the DGGraphics object when the 
   the font is assigned to it or the drawing surface has to be recreated.
   This is necessary because 
------------------------------------------------------------------------*/
/*
void DGFont::SetNewDC(HDC hDC)
{

}*/