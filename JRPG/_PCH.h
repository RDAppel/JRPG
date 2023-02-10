#pragma once

#pragma message("Compiling Headers...")

/* Standard */
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <limits>
#include <algorithm>

/* Allegro */
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


/* Input */
#include "KeyState.h"
#include "InputState.h"

/* Math */
#include "Color.h"
#include "Vector2.h"

/* Resources */
#include "Resource.h"
#include "Font.h"
#include "Texture.h"

#include "ResourceManager.h"

/* Graphics */
#include "SpriteBatch.h"


/* Game Management */
#include "Game.h"