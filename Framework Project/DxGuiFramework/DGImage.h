/*------------------------------------------------------------------------
File Name: DGImage.h
Description: This file contains the DGImage class, which is a control that
   displays a bitmap.
Version:
   1.0.0    09.09.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGIMAGE_H
#define DGIMAGE_H

class DGImage : public DGWindow
{
public:
   DGImage(UINT winID, DGWindow* parentWin, const int xPos, 
      const int yPos,  const int width, const int height,
      UINT bitmapID, bool transparent = false, 
      DGColor transparentColor = DGColor(255, 0, 255), 
      bool _parentNotify = true);

   DGImage(UINT winID, DGWindow* parentWin, const DGArea& dimensions,
      UINT bitmapID, bool transparent = false, 
      DGColor transparentColor = DGColor(255, 0, 255), 
      bool _parentNotify = true);

   DGImage(UINT winID, DGWindow* parentWin, const DGPoint& position, 
      const DGPoint& size, UINT bitmapID, bool transparent = false, 
      DGColor transparentColor = DGColor(255, 0, 255), 
      bool _parentNotify = true);

   void LoadBitmapFile(const char* bitmapName, int priority = 1);
   char* const GetBitmapFileName(void) {return bitmapFileName;}

   void SetTransparency(bool transparent);
   bool GetTransparency(void) {return transparentBitmap;}

   void SetParentNotify(bool notify) {parentNotify = notify;}
   bool GetParentNotify(void) {return parentNotify;}

   void SetTransparentColor(DGColor color);
   DGColor GetTransparentColor(void) {return transparentColor;}

   void SetBitmapID(UINT id) {bitmapID = id;}
   UINT GetBitmapID(void) {return bitmapID;}

   void SetBitmapOrigin(DGPoint coords);
   DGPoint GetBitmapOrigin(void) {return bitmapOrigin;}

   DGPoint GetBitmapSize(void);

protected:
   void FC OnDrawWindow(DGWindowSurface* surface);
   void FC OnLButtonDown(int x, int y, BYTE* keyboardState);
   void FC OnLButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnLButtonDblClk(int x, int y, BYTE* keyboardState);
   void FC OnMButtonDown(int x, int y, BYTE* keyboardState);
   void FC OnMButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnMButtonDblClk(int x, int y, BYTE* keyboardState);
   void FC OnRButtonDown(int x, int y, BYTE* keyboardState);
   void FC OnRButtonUp(int x, int y, BYTE* keyboardState);
   void FC OnRButtonDblClk(int x, int y, BYTE* keyboardState);
   void FC OnMouseMove(int x, int y, BYTE* keyboardState);
   void FC OnWindowSized(void);

private:
   bool transparentBitmap;
   bool parentNotify;

   DGColor transparentColor;
   UINT bitmapID;
   char bitmapFileName[256];

   DGPoint bitmapOrigin;
};

#endif