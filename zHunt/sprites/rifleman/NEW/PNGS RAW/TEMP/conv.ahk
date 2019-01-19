#include gdip.ahk
pToken := Gdip_StartUp()
Loop, Files, %A_ScriptDir%\*.bmp
{
    pBitmap := Gdip_CreateBitmapFromFile(A_LoopFileFullPath)
    Width := Gdip_GetImageWidth(pBitmap)
    Height := Gdip_GetImageHeight(pBitmap)
     TopRight := Gdip_GetPixel(pBitmap, 0, 0)
 Run, % A_ScriptDir "\convert.exe """ A_LoopFilePath """ -transparent " ARGB_TO_RGB(TopRight) " """ StrReplace(A_LoopFileFullPath, A_LoopFileExt, "png") """"
     Gdip_DisposeImage(pBitmap)
}
Return

ARGB_TO_RGB(ARGB) {
    return Format("#{:x}", 0xFFFFFF & ARGB)
}