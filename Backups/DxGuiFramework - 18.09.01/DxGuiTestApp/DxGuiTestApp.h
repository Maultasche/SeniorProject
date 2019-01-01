/*DxGuiTestApp.h*/

#ifndef DXGUITESTAPP_H
#define DXGUITESTAPP_H

#define	IDW_BLUEWINDOW			100
#define  IDW_REDWINDOW			101
#define	IDW_YELLOWWINDOW		102
#define	IDW_GREENWINDOW		103

#define  IDL_TESTLABEL        110
#define  IDB_TESTBUTTON       111

#define  IDI_IMAGE            120
#define  IDE_IMAGENAME        121

#define  IDB_IMAGEBITMAP      1

class DxGuiTestApp : public DGApplication
{
public:
   void InitApp();
};

#endif