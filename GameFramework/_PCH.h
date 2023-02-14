#pragma once

#pragma message("Compiling Headers...")

/* Standard */
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <functional>

/* Allegro */
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


/* Math */
#include "Math.h"
#include "Color.h"
#include "Vector2.h"

/* Input */
#include "KeyState.h"
#include "InputState.h"

/* Resources */
#include "Resource.h"
#include "Font.h"
#include "Texture.h"

#include "ResourceManager.h"

/* Graphics */
#include "SpriteBatch.h"

/* Time */
#include "GameTime.h"

/* Screen Management */
#include "Screen.h"
#include "ScreenManager.h"

/* Game Management */
#include "Game.h"