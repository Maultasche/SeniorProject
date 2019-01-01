/*------------------------------------------------------------------------
File Name: DGScrollBar.h
Description: This file contains the DGScrollBar class, which is a scroll
   bar control. 
Version:
   1.0.0    30.09.2001  Created the file
------------------------------------------------------------------------*/

#ifndef DGSCROLLBAR_H
#define DGSCROLLBAR_H

//The ID of the child windows, which are only visible inside the
//control
#define IDW_BN_UP             100
#define IDW_BN_DOWN           101
#define IDW_BN_TRACK          102

#define SB_HORIZONTAL         0
#define SB_VERTICAL           1

class DGScrollBar : public DGWindow
{
public:
   DGScrollBar(UINT winID, DGWindow* parentWin, const int xPos, 
      const int yPos,  const int width, const int height,
      const int scrollMin, const int scrollMax, UINT scrollType = SB_VERTICAL);

   DGScrollBar(UINT winID, DGWindow* parentWin, const DGArea& dimensions,
      const int scrollMin, const int scrollMax, UINT scrollType = SB_VERTICAL);

   DGScrollBar(UINT winID, DGWindow* parentWin, const DGPoint& position, 
      const DGPoint& size, const int scrollMin, const int scrollMax, 
      UINT scrollType = SB_VERTICAL);

   void SetMinValue(const int min); 
   int GetMinValue(void) {return minValue;}

   void SetMaxValue(const int max);
   int GetMaxValue(void) {return maxValue;}

   void SetPosition(int scrollPosition);
   int GetPosition(void) {return position;}

   void SetLineValue(int value);
   int GetLineValue(void) {return lineValue;}

protected:
   void FC OnCreate(void);
   void FC OnDrawWindow(DGWindowSurface* surface);
   void FC OnWindowSizing(void);
   void FC OnWindowSized(void);
   void FC OnTimer(UINT timerID);

   void OnButtonPressure(DGMessage* msg);
   void OnButtonClicked(DGMessage* msg);

   virtual void OnLineUp(void);
   virtual void OnLineDown(void);
   virtual void OnTrack(DGMessage* msg);

private:
   DGButton* upButton;
   DGImage* upImage;
   DGButton* downButton;
   DGImage* downImage;
   DGButton* trackingButton;

   UINT scrollType;

   int minValue;
   int maxValue;
   int position;

   int lineValue;
};

#endif