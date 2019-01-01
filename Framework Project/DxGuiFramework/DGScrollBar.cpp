/*------------------------------------------------------------------------
File Name: DGScrollBar.h
Description: This file contains the implementation of the DGScrollBar 
   class, which is a scroll bar control. 
Version:
   1.0.0    30.09.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

#define DEFAULT_LINE_VALUE    1
#define SB_SCROLL_INTERVAL    50

/*Constructors*/
DGScrollBar::DGScrollBar(UINT winID, DGWindow* parentWin, const int xPos, 
                         const int yPos,  const int width, const int height,
                         const int scrollMin, const int scrollMax, 
                         UINT scrType) :
   DGWindow(winID, true, xPos, yPos, width, height),
   minValue(scrollMin),
   maxValue(scrollMax),
   position(scrollMin),
   lineValue(DEFAULT_LINE_VALUE),
   scrollType(scrType),
   upButton(NULL),
   downButton(NULL),
   trackingButton(NULL)
{
   assert(scrollMin <= scrollMax);
}


DGScrollBar::DGScrollBar(UINT winID, DGWindow* parentWin, const DGArea& dimensions,
                         const int scrollMin, const int scrollMax, UINT scrType) :
   DGWindow(winID, true, dimensions),
   minValue(scrollMin),
   maxValue(scrollMax),
   position(scrollMin),
   lineValue(DEFAULT_LINE_VALUE),
   scrollType(scrType),
   upButton(NULL),
   downButton(NULL),
   trackingButton(NULL)
{
   assert(scrollMin <= scrollMax);
}

DGScrollBar::DGScrollBar(UINT winID, DGWindow* parentWin, const DGPoint& position, 
                         const DGPoint& size, const int scrollMin, const int scrollMax, 
                         UINT scrType) :
   DGWindow(winID, true, position, size),
   minValue(scrollMin),
   maxValue(scrollMax),
   position(scrollMin),
   lineValue(DEFAULT_LINE_VALUE),
   scrollType(scrType),
   upButton(NULL),
   downButton(NULL),
   trackingButton(NULL)
{
   assert(scrollMin <= scrollMax);
}

void DGScrollBar::SetMinValue(const int min) 
{
   assert(min <= maxValue);
   minValue = min;

   if(position < minValue)
      position = minValue;
}

void DGScrollBar::SetMaxValue(const int max) 
{
   assert(max >= minValue);
   maxValue = max;

   if(position > maxValue)
      position = maxValue;
}

void DGScrollBar::SetPosition(int scrollPosition) 
{   
   position = scrollPosition;

   if(position < minValue)
      position = minValue;
   else if(position > maxValue)
      position = maxValue;
}

void DGScrollBar::SetLineValue(int value)
{
   assert(abs(lineValue) <= maxValue);

   lineValue = value;
}

void FC DGScrollBar::OnCreate()
{
   DGPoint size = GetSize();

   upButton = new DGButton(IDW_BN_UP, this, DGArea(0, 0, 16, 16),
      BT_PUSHBUTTON | BT_IMAGEBUTTON);

   downButton = new DGButton(IDW_BN_DOWN, this, DGArea(size.x - 16, 
      size.y - 16, 16, 16), BT_PUSHBUTTON | BT_IMAGEBUTTON);

   //If the up and down arrow bitmaps have not already been loaded, 
   //load them
   if(scrollType == SB_VERTICAL)
   {
      DGBitmap* bitmap = dgGraphics->GetBitmap(IDB_UP_ARROW);
      if(bitmap == NULL)
         dgGraphics->LoadBitmap(IDB_UP_ARROW, 1, "Bitmaps\\Arrow_Up.bmp");

      bitmap = dgGraphics->GetBitmap(IDB_DOWN_ARROW);
      if(bitmap == NULL)
         dgGraphics->LoadBitmap(IDB_DOWN_ARROW, 1, "Bitmaps\\Arrow_Down.bmp");

      upButton->SetBitmapID(IDB_UP_ARROW);
      downButton->SetBitmapID(IDB_DOWN_ARROW);
   }
   
   //scrollType == SB_HORIZONTAL
   else
   {
      DGBitmap* bitmap = dgGraphics->GetBitmap(IDB_LEFT_ARROW);
      if(bitmap == NULL)
         dgGraphics->LoadBitmap(IDB_LEFT_ARROW, 1, "Bitmaps\\Arrow_Left.bmp");

      bitmap = dgGraphics->GetBitmap(IDB_RIGHT_ARROW);
      if(bitmap == NULL)
         dgGraphics->LoadBitmap(IDB_RIGHT_ARROW, 1, "Bitmaps\\Arrow_Right.bmp");

      upButton->SetBitmapID(IDB_LEFT_ARROW);
      downButton->SetBitmapID(IDB_RIGHT_ARROW);
   }

   AddChildWindow(upButton);
   AddChildWindow(downButton);

   AddMessageHandler(GM_BUTTON_PRESSURE, 
      new MsgHandlerFunction<DGScrollBar>(this, OnButtonPressure));

   AddMessageHandler(GM_BUTTON_CLICKED, 
      new MsgHandlerFunction<DGScrollBar>(this, OnButtonClicked));
}

void FC DGScrollBar::OnDrawWindow(DGWindowSurface* surface)
{
   surface->FillSurface(DGColor(180, 180, 180));
}

void FC DGScrollBar::OnWindowSizing()
{
   OnWindowSized();
}

void FC DGScrollBar::OnWindowSized()
{
   DGPoint size = GetSize();
   downButton->SetPosition(size.x - 16, size.y - 16);
}

void FC DGScrollBar::OnTimer(UINT timerID)
{
   if(timerID == SB_UP_TIMER)
   {
      OnLineUp();
      //OutputDebugString("LineUp Timer\n");
   }
   else if(timerID == SB_DOWN_TIMER)
   {
      OnLineDown();
      //OutputDebugString("LineDown Timer\n");
   }
}

void DGScrollBar::OnButtonPressure(DGMessage* msg)
{
   if(msg->data3 == IDW_BN_UP)
   {
      OnLineUp();

      DGGetGui()->CreateTimer(SB_UP_TIMER, GetWindowID(), SB_SCROLL_INTERVAL);


   }

   else if(msg->data3 == IDW_BN_DOWN)
   {
      OnLineDown();

      DGGetGui()->CreateTimer(SB_DOWN_TIMER, GetWindowID(), SB_SCROLL_INTERVAL);

   }

   //OutputDebugString("Button Down\n");
}

void DGScrollBar::OnButtonClicked(DGMessage* msg)
{
   if(msg->data3 == IDW_BN_UP)
   {
      DGGetGui()->DestroyTimer(SB_UP_TIMER);
   }

   else if(msg->data3 == IDW_BN_DOWN)
   {
      DGGetGui()->DestroyTimer(SB_DOWN_TIMER);
   }

   //OutputDebugString("Button Up\n");
}

void DGScrollBar::OnLineUp()
{
   position -= lineValue;

   if(position < minValue)
      position = minValue;

   //Send a GM_SCROLLBAR_LINEUP message to parent
   DGMessage* msg = new DGMessage(DGMessage(GM_SCROLLBAR_LINEUP,
      GetParent()->GetWindowID(), 0, 0, GetWindowID()));
   GetParent()->SendMessage(msg);
   delete msg;

}

void DGScrollBar::OnLineDown()
{
   position += lineValue;

   if(position > maxValue)
      position = maxValue;

   //Send a GM_SCROLLBAR_LINEDOWN message to parent
   DGMessage* msg = new DGMessage(DGMessage(GM_SCROLLBAR_LINEDOWN,
      GetParent()->GetWindowID(), 0, 0, GetWindowID()));
   GetParent()->SendMessage(msg);
   delete msg;

}

void DGScrollBar::OnTrack(DGMessage* msg)
{

}
