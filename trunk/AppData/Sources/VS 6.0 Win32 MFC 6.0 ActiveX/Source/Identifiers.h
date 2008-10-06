// Ax$CONTROL$ ActiveX control.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// Identifiers.h - UUIDs declaration

// initially generated by $GENERATOR$ on $DATE$ at $TIME$
// visit http://zarezky.spb.ru/projects/afx_scratch.html for more info

#if !defined(__Identifiers_h)
#define __Identifiers_h

//////////////////////////////////////////////////////////////////////////////////////////////
// UUID strings

#define S_UUID_I$CONTROL$Disp "$DISPIID$"
#define S_UUID_I$CONTROL$Events "$EVTIID$"
#define S_UUID_C$CONTROL$Ctrl "$CLSID$"
#define S_UUID_Ax$CONTROL$ "$LIBID$"

#if !defined(__MKTYPLIB__) && !defined(__midl)

//////////////////////////////////////////////////////////////////////////////////////////////
// interfaces

struct __declspec(uuid(S_UUID_I$CONTROL$Disp)) I$CONTROL$Disp;
#define IID_I$CONTROL$Disp __uuidof(I$CONTROL$Disp)
struct __declspec(uuid(S_UUID_I$CONTROL$Events)) I$CONTROL$Events;
#define IID_I$CONTROL$Events __uuidof(I$CONTROL$Events)

//////////////////////////////////////////////////////////////////////////////////////////////
// coclass

class __declspec(uuid(S_UUID_C$CONTROL$Ctrl)) C$CONTROL$Ctrl;
#define CLSID_C$CONTROL$Ctrl __uuidof(C$CONTROL$Ctrl)

//////////////////////////////////////////////////////////////////////////////////////////////
// type library

struct __declspec(uuid(S_UUID_Ax$CONTROL$)) Ax$CONTROL$;
#define LIBID_Ax$CONTROL$ __uuidof(Ax$CONTROL$)

#endif   // !defined(__MKTYPLIB__) && !defined(__midl)

#endif   // __Identifiers_h

// end of file
