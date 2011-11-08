#ifndef FREYA_INCLUDES_GUARD
#define FREYA_INCLUDES_GUARD

/* Libmpdclient */
#include <mpd/client.h>
#include <mpd/status.h>
#include <mpd/entity.h>
#include <mpd/search.h>
#include <mpd/parser.h>
#include <mpd/async.h>
#include <mpd/tag.h>

/* GLibmm */
#include <glibmm.h>

/* STL */
#include <vector>
#include <iostream>

using namespace std;

/* Typdefs for the lazy */
typedef struct mpd_connection mpd_connection;
typedef struct mpd_status mpd_status;
typedef struct mpd_entity mpd_entity;

#endif
