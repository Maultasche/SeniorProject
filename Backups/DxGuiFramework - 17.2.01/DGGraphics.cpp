/*------------------------------------------------------------------------
File Name: DGGraphics.h
Description: This file contains the DGGraphics class implementation, 
   which manages the DirectDraw surfaces and controls and what is drawn 
   to the screen.
Version:
   1.0.0    10.02.2000  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

DGGraphics::DGGraphics()
{
   OutputDebugString("DGGraphics constructor\n");

   hWnd = DGGetApp()->GetWindowsHandle();

   //Initialize DirectDraw object
   HRESULT result = DirectDrawCreateEx(NULL, (void**)&lpDD, 
      IID_IDirectDraw7, NULL);
   
   if(result != DD_OK)
      HandleDDrawError(EC_DDINIT, result, __FILE__, __LINE__);

   //Set the cooperative level.
   result = lpDD->SetCooperativeLevel(hWnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE |
      DDSCL_FULLSCREEN);

   if(result != DD_OK)
      HandleDDrawError(EC_DDINIT, result, __FILE__, __LINE__);

   //Get the hardware capabilities
   ddCaps.dwSize = sizeof(DDCAPS);

   result = lpDD->GetCaps(&ddCaps, NULL);

   SetGraphicsMode(DGPoint(640, 480), WS_WINDOWED, CD_16BIT, BT_SINGLE);

}

DGGraphics::~DGGraphics()
{
   OutputDebugString("DGGraphics destructor\n");

   lpDD->Release();
   lpDD = NULL;
}

void DGGraphics::Initialize()
{

}

void DGGraphics::SetGraphicsMode(DGPoint res, UINT winState, UINT clrDepth,
      UINT bufferMode)
{

   screenRes.x = res.x;
   screenRes.y = res.y;

   windowedState = winState;

   HWND desktopWindow;
   int desktopClrDepth;

   //If we are switching to windowed mode, we need to question the desktop
   //about its color depth
   if(windowedState == WS_WINDOWED)
   {
      desktopWindow = GetDesktopWindow();
      HDC desktopDC = GetDC(desktopWindow);
      desktopClrDepth = GetDeviceCaps(desktopDC, BITSPIXEL);
      ReleaseDC(desktopWindow, desktopDC);
   }


   if(clrDepth == CD_16BIT)
   {

   }
   else
      colorDepth = clrDepth;

   UINT appColorDepth = clrDepth;
   //UINT bufferingMode;
}


void DGGraphics::HandleDDrawError(UINT errorCode, HRESULT error, 
   char* fileName, UINT lineNumber)
{
   if(error == DD_OK)
      return;

   char errorText[512];

   switch(error)
   {
      case DDERR_ALREADYINITIALIZED:
         strcpy(errorText, "DirectDraw object has already been initialized.");
         break;
      case DDERR_BLTFASTCANTCLIP:
         strcpy(errorText, "BltFast() cannot be used with a surface "\
            "that has a DirectDrawClipper object attached.");
         break;
      case DDERR_CANNOTATTACHSURFACE: 
         strcpy(errorText, "The surface cannot be attached.");
         break;
      case DDERR_CANNOTDETACHSURFACE: 
         strcpy(errorText, "The surface cannot be detached.");
         break;
      case DDERR_CANTCREATEDC: 
         strcpy(errorText, "The Windows device context could not be "\
            "created.");
         break;
      case DDERR_CANTDUPLICATE:
         strcpy(errorText, "This surface cannot be duplicated.");
         break;
      case DDERR_CANTLOCKSURFACE:
         strcpy(errorText, "The surface cannot be locked.");
         break;
      case DDERR_CANTPAGELOCK: 
         strcpy(errorText, "Page lock failed.");
         break;
      case DDERR_CANTPAGEUNLOCK:
         strcpy(errorText, "Page unlock failed.");
         break;
      case DDERR_CLIPPERISUSINGHWND:
         strcpy(errorText, "The clip list could not be added, as the "\
            "DirectDrawClipper object is already monitoring a window "\
            "handle.");
         break;
      case DDERR_COLORKEYNOTSET: 
         strcpy(errorText, "No source color key has been set");
         break;
      case DDERR_CURRENTLYNOTAVAIL: 
         strcpy(errorText, "No support is currently available for this "\
            "operation");
         break;
      case DDERR_DDSCAPSCOMPLEXREQUIRED: 
         strcpy(errorText, "This surface needs to be a complex surface");
         break;
      case DDERR_DCALREADYCREATED:
         strcpy(errorText, "A device context has already been created for "\
            "this surface");
         break;
      case DDERR_DEVICEDOESNTOWNSURFACE:
         strcpy(errorText, "This surface is owned by another DirectDraw device "\
            "and cannot be used");
         break;
      case DDERR_DIRECTDRAWALREADYCREATED:
         strcpy(errorText, "A DirectDraw object representing this driver has "\
            "already been created.");
         break;
      case DDERR_EXCEPTION:
         strcpy(errorText, "An exception was encountered while performing "\
            "the requested operation.");
         break;
     case DDERR_EXCLUSIVEMODEALREADYSET:
         strcpy(errorText, "Exclusive mode has already been set.");
         break;
      case DDERR_EXPIRED:
         strcpy(errorText, "The data has expired and is invalid.");
         break;
      case DDERR_GENERIC: 
         strcpy(errorText, "An undefined error condition has occurred.");
         break;
      case DDERR_HEIGHTALIGN: 
         strcpy(errorText, "The height of the provided rectangle is not a "\
            "multiple of the required alignment.");
         break;
      case DDERR_HWNDALREADYSET:
         strcpy(errorText, "The cooperative-level window handle has already been "\
            "set.");
         break;
      case DDERR_HWNDSUBCLASSED:
         strcpy(errorText, "DirectDraw cannot restore because the DirectDraw "\
            "cooperative-level window handle has been subclassed.");
         break;
      case DDERR_IMPLICITLYCREATED:
         strcpy(errorText, "Surface cannot be restored because it was implicitly "\
            "created");
         break;
      case DDERR_INCOMPATIBLEPRIMARY:
         strcpy(errorText, "The primary surface creation request does not match "\
            "the existing primary surface.");
         break;
      case DDERR_INVALIDCAPS: 
         strcpy(errorText, "One or more of the capability bits passed to the "\
            "callback function are incorrect.");
         break;
      case DDERR_INVALIDCLIPLIST:
         strcpy(errorText, "DirectDraw does not support the provided clip list.");
         break;
      case DDERR_INVALIDDIRECTDRAWGUID: 
         strcpy(errorText, "The provided GUID is an invalid DirectDraw GUID");
         break;
      case DDERR_INVALIDMODE:
         strcpy(errorText, "DirectDraw does not support the requested mode.");
         break;
      case DDERR_INVALIDOBJECT:
         strcpy(errorText, "DirectDraw received a pointer to an invalid object.");
         break;
      case DDERR_INVALIDPARAMS: 
         strcpy(errorText, "One or more parameters passed to this method are "\
            "incorrect.");
         break;
      case DDERR_INVALIDPIXELFORMAT: 
         strcpy(errorText, "The specified pixel format was invalid.");
         break;
      case DDERR_INVALIDPOSITION: 
         strcpy(errorText, "The position of the overlay on the destination is "\
            "no longer legal.");
         break;
      case DDERR_INVALIDRECT: 
         strcpy(errorText, "The provided rectangle was invalid.");
         break;
      case DDERR_INVALIDSTREAM: 
         strcpy(errorText, "The specified stream contains invalid data.");
         break;
      case DDERR_INVALIDSURFACETYPE:
         strcpy(errorText, "The surface was of the wrong type.");
         break;
      case DDERR_LOCKEDSURFACES:
         strcpy(errorText, "This operation failed due to a locked surface.");
         break;
      case DDERR_MOREDATA:
         strcpy(errorText, "There is more data available than the specified buffer "\
            "can hold.");
         break;
      case DDERR_NO3D:
         strcpy(errorText, "No 3-D hardware or emulation is present.");
         break;
      case DDERR_NOALPHAHW: 
         strcpy(errorText, "No alpha-acceleration hardware is present or available.");
         break;
      case DDERR_NOBLTHW: 
         strcpy(errorText, "No blitter hardware is present.");
         break;
      case DDERR_NOCLIPLIST: 
         strcpy(errorText, "No clip list is available.");
         break;
      case DDERR_NOCLIPPERATTACHED: 
         strcpy(errorText, "No DirectDrawClipper is attached to the surface.");
         break;
      case DDERR_NOCOLORCONVHW: 
         strcpy(errorText, "No color-conversion hardware is present or available.");
         break;
      case DDERR_NOCOLORKEY: 
         strcpy(errorText, "The surface does not currently have a color key.");
         break;
      case DDERR_NOCOLORKEYHW: 
         strcpy(errorText, "There is no hardware support for the destination color "\
            "key.");
         break;
      case DDERR_NOCOOPERATIVELEVELSET: 
         strcpy(errorText, "No cooperative level had been set.");
         break;
      case DDERR_NODC: 
         strcpy(errorText, "No device context exists for this surface.");
         break;
      case DDERR_NODDROPSHW: 
         strcpy(errorText, "No DirectDraw raster-operation (ROP) hardware is"\
            "available.");
         break;
      case DDERR_NODIRECTDRAWHW: 
         strcpy(errorText, "Hardware-only DirectDraw creation not possible.");
         break;
      case DDERR_NODIRECTDRAWSUPPORT: 
         strcpy(errorText, "DirectDraw support is not possible with the current"\
            "display driver.");
         break;
      case DDERR_NODRIVERSUPPORT: 
         strcpy(errorText, "Testing cannot proceed due to no display driver support.");
         break;
      case DDERR_NOEMULATION: 
         strcpy(errorText, "Software emulation not available.");
         break;
      case DDERR_NOEXCLUSIVEMODE: 
         strcpy(errorText, "This operation requires the application to have "\
            "exclusive mode.");
         break;
      case DDERR_NOFLIPHW: 
         strcpy(errorText, "Flipping visible surfaces not supported.");
         break;
      case DDERR_NOFOCUSWINDOW:
         strcpy(errorText, "Cannot create or set a device window without having "\
            "first set the focus window.");
         break;         
      case DDERR_NOGDI: 
         strcpy(errorText, "No GDI is present.");
         break;
      case DDERR_NOHWND:
         strcpy(errorText, "No cooperative-level window handle.");
         break;
      case DDERR_NOMIPMAPHW: 
         strcpy(errorText, "No mipmap-capable texture mapping hardware is present "\
            "or available.");
         break;
      case DDERR_NOMIRRORHW: 
         strcpy(errorText, "No mirroring hardware is present of available.");
         break;
      case DDERR_NOMONITORINFORMATION: 
         strcpy(errorText, "No monitor information exists.");
         break;
      case DDERR_NONONLOCALVIDMEM:
         strcpy(errorText, "No nonlocal video memory is available.");
         break;
      case DDERR_NOOPTIMIZEHW: 
         strcpy(errorText, "Optimized surfaces not supported.");
         break;
      case DDERR_NOOVERLAYDEST: 
         strcpy(errorText, "Overlay is not a destination.");
         break;
      case DDERR_NOOVERLAYHW: 
         strcpy(errorText, "No overlay hardware present or available.");
         break;
      case DDERR_NOPALETTEATTACHED: 
         strcpy(errorText, "No palette object is attached to the surface.");
         break;
      case DDERR_NOPALETTEHW: 
         strcpy(errorText, "No hardware support for 16- or 256-color palettes.");
         break;
      case DDERR_NORASTEROPHW: 
         strcpy(errorText, "No appropriate raster-operation hardware is present "\
            " or available.");
         break;
      case DDERR_NOROTATIONHW: 
         strcpy(errorText, "No rotation hardware is present or available.");
         break;
      case DDERR_NOSTEREOHARDWARE: 
         strcpy(errorText, "No stereo hardware is present or available.");
         break;
      case DDERR_NOSTRETCHHW: 
         strcpy(errorText, "No hardware support for stretching.");
         break;
      case DDERR_NOSURFACELEFT: 
         strcpy(errorText, "No hardware that supports stereo surfaces.");
         break;
      case DDERR_NOT4BITCOLOR:
         strcpy(errorText, "This operation requires a 4-bit color palette.");
         break;
      case DDERR_NOT4BITCOLORINDEX: 
         strcpy(errorText, "This operation requires a 4-bit color *index* palette.");
         break;
      case DDERR_NOT8BITCOLOR: 
         strcpy(errorText, "This operation requires an 8-bit color palette.");
         break;
      case DDERR_NOTAOVERLAYSURFACE: 
         strcpy(errorText, "Not an overlay surface.");
         break;
      case DDERR_NOTEXTUREHW: 
         strcpy(errorText, "No texture-mapping hardware is present or available.");
         break;
      case DDERR_NOTFLIPPABLE: 
         strcpy(errorText, "This surface cannot be flipped.");
         break;
      case DDERR_NOTFOUND: 
         strcpy(errorText, "The requested item was not found.");
         break;
      case DDERR_NOTINITIALIZED:
         strcpy(errorText, "DirectDraw object has not been initialized.");
         break;
      case DDERR_NOTLOADED: 
         strcpy(errorText, "Surface has not been allocated any memory.");
         break;
      case DDERR_NOTLOCKED: 
         strcpy(errorText, "Surface was not locked.");
         break;
      case DDERR_NOTPAGELOCKED: 
         strcpy(errorText, "Surface was not page-locked.");
         break;
      case DDERR_NOTPALETTIZED: 
         strcpy(errorText, "Surface is not palette-based.");
         break;
      case DDERR_NOVSYNCHW: 
         strcpy(errorText, "There is no hardware support for vertical blank or "\
            "synchronized operations.");
         break;
      case DDERR_NOZBUFFERHW: 
         strcpy(errorText, "There is no z-buffer hardware support.");
         break;
      case DDERR_NOZOVERLAYHW:
         strcpy(errorText, "Overlay surfaces cannot be z-layered: no hardware "\
            "support.");
         break;
      case DDERR_OUTOFCAPS: 
         strcpy(errorText, "The hardware needed for this operation has already "\
            "been allocated.");
         break;
      case DDERR_OUTOFMEMORY: 
         strcpy(errorText, "There is not enough memory to perform this operation.");
         break;
      case DDERR_OUTOFVIDEOMEMORY: 
         strcpy(errorText, "There is not enough *display* memory to perform this "\
            "operation.");
         break;
      case DDERR_OVERLAPPINGRECTS: 
         strcpy(errorText, "Source and destination rectangles are on the same "\
            "surface and overlap each other.");
         break;
      case DDERR_OVERLAYCANTCLIP: 
         strcpy(errorText, "The hardware does not support clipped overlays.");
         break;
      case DDERR_OVERLAYCOLORKEYONLYONEACTIVE: 
         strcpy(errorText, "Only one color key can be active on an overlay.");
         break;
      case DDERR_OVERLAYNOTVISIBLE :
         strcpy(errorText, "The specified overlay is hidden.");
         break;
      case DDERR_PALETTEBUSY: 
         strcpy(errorText, "The palette is busy.");
         break;
      case DDERR_PRIMARYSURFACEALREADYEXISTS: 
         strcpy(errorText, "A primary surface already exists.");
         break;
      case DDERR_REGIONTOOSMALL: 
         strcpy(errorText, "The specified clip region is too small.");
         break;
      case DDERR_SURFACEALREADYATTACHED: 
         strcpy(errorText, "The surface was already attached.");
         break;
      case DDERR_SURFACEALREADYDEPENDENT: 
         strcpy(errorText, "The surface was already dependent.");
         break;
      case DDERR_SURFACEBUSY: 
         strcpy(errorText, "The surface is busy.");
         break;
      case DDERR_SURFACEISOBSCURED: 
         strcpy(errorText, "Access to surface denied: surface is obscured.");
         break;
      case DDERR_SURFACELOST: 
         strcpy(errorText, "The surface had been lost: it must be restored.");
         break;
      case DDERR_SURFACENOTATTACHED: 
         strcpy(errorText, "The requested surface is not attached.");
         break;
      case DDERR_TOOBIGHEIGHT: 
         strcpy(errorText, "The requested height is too large.");
         break;
      case DDERR_TOOBIGSIZE:
         strcpy(errorText, "The requested size is too large.");
         break;
      case DDERR_TOOBIGWIDTH: 
         strcpy(errorText, "The requested width is too large.");
         break;
      case DDERR_UNSUPPORTED: 
         strcpy(errorText, "This operation is not supported.");
         break;
      case DDERR_UNSUPPORTEDFORMAT: 
         strcpy(errorText, "The pixel format is not supported by DirectDraw.");
         break;
      case DDERR_UNSUPPORTEDMASK: 
         strcpy(errorText, "The bitmask in the pixel format is not supported by "\
            "DirectDraw.");
         break;
      case DDERR_UNSUPPORTEDMODE: 
         strcpy(errorText, "The display is currently in an unsupported mode.");
         break;
      case DDERR_VERTICALBLANKINPROGRESS: 
         strcpy(errorText, "A vertical blank is in progress.");
         break;
      case DDERR_VIDEONOTACTIVE: 
         strcpy(errorText, "The video port is not active.");
         break;
      case DDERR_WASSTILLDRAWING: 
         strcpy(errorText, "The operation was still drawing.");
         break;
      case DDERR_WRONGMODE: 
         strcpy(errorText, "This surface cannot be restored: it was created in "\
            "a different mode.");
         break;
      case DDERR_XALIGN: 
         strcpy(errorText, "The rectangle was not horizontally aligned on a "\
            "required boundary.");
         break;
      default:
         strcpy(errorText, "Unknown Error");
         break;
   }

   throw(new DGException(errorText, errorCode, ET_DIRECTDRAW, fileName,
      lineNumber));
}
