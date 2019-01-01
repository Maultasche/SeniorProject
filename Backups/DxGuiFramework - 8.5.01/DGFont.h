/*------------------------------------------------------------------------
File Name: DGFont.h
Description: This file contains the DGFont class, which represents a
   font that is used in drawing text on the screen.
Version:
   1.0.0    10.03.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGFONT_H
#define DGFONT_H

class DGFont
{
public:
   DGFont();
   DGFont(const char* p_fontName, int p_height, int p_weight = FW_NORMAL,
      bool p_italic = false, bool p_underline = false, bool p_strikeout = false);
   virtual ~DGFont();

   DGFont& operator=(DGFont& font);

   char* const GetFontName(void) {return fontName;}
   int GetHeight(void) {return height;}
   int GetWeight(void) {return weight;}
   bool IsItalic(void) {return(italic == TRUE);}
   bool IsUnderline(void) {return(underline == TRUE);}
   bool IsStrikeout(void) {return(strikeout == TRUE);}
   HFONT GetFontHandle(void) {return fontHandle;}
        
   void SetNewDC(HDC hDC);

private:
   HFONT fontHandle;

   //All the user usually cares about is the font name and height
   char fontName[64];
   int height;

   //Factors that could be important to the user
   int weight;
   BOOL italic;
   BOOL underline;
   BOOL strikeout;

   //Factors that the user is almost never concerned with
   int width;
   int escapement;
   int orientation;
   int charSet;
   int outPrecision;
   int clipPrecision;
   int quality;
   int pitchAndFamily;
};

#endif