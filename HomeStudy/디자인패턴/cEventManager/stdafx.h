// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <list>
#include <string>
#include <iostream>
#include <map>
#include <vector>

#include "EventManager.h"
#include "Observer.h"
#include "Publisher.h"

#define SafeDelete(p)		{ if(p) delete p; p = NULL; }

// TODO: reference additional headers your program requires here
