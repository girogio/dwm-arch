#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "polybar-example_eDP";    /* Polybar tray instance name *1/ */
static const char *altbarcmd        = "bar.sh"; /* Alternate bar launch command */
static const unsigned int gappx		= 5;		/* g a p s */
static const char *fonts[]          = { "Cascadia Code:size=11" };
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char purple[]          = "#bd93f9";
static const char background[]	    = "#282a36";
static const int swallowfloating    = 0; 
static const char terminal[] = "st";

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { terminal, "-t", scratchpadname, NULL };

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, background, col_gray2 },
	[SchemeSel]  = { background, purple,  purple  },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
		/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",           NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox",			  NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "Alacritty",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "st",             NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,             NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

static const char *volupcmd[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "+10%", NULL };
static const char *voldowncmd[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "-10%", NULL };
static const char *volmutecmd[] = {"pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *allscreenshotcmd[] = {"maim", "-x", ":0", "~/Screenshots/$(date).png", NULL };
static const char *termcmd[] = {terminal, NULL};

static Key keys[] = {

	/* modifier                     key        								 function         argument */

	// audio keys
  { 0     ,                       XF86XK_AudioLowerVolume,   spawn,    		    {.v = voldowncmd}},
  { 0     ,                       XF86XK_AudioMute,          spawn,           {.v = volmutecmd}},
  { 0     ,                       XF86XK_AudioRaiseVolume,   spawn,    	  	  {.v = volupcmd}},
  { MODKEY,                       XK_Return,							   spawn,    	  	  {.v = termcmd}},
  { 0,                            XK_Print,                  spawn,           {.v = allscreenshotcmd}},
	{ MODKEY,                       XK_grave,  								 togglescratch,  {.v = scratchpadcmd } },
  { MODKEY|ShiftMask,             XK_c,                      quit,            {0} },
  { MODKEY,                       XK_b,                      togglebar,       {0} },
	{ Mod1Mask,                     XK_Tab,                    focusstack,      {.i = -1 } },
	{ Mod1Mask|ShiftMask,           XK_Tab,                    focusstack,      {.i = +1 } },
	{ MODKEY,                       XK_i,                      incnmaster,      {.i = +1 } },
	{ MODKEY,                       XK_d,                      incnmaster,      {.i = -1 } },
	{ MODKEY,                       XK_h,                      setmfact,        {.f = -0.05} },
	{ MODKEY,                       XK_l,                      setmfact,        {.f = +0.05} },
	// gaps
  { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = gappx  } },
	// cfacts
	{ MODKEY,           					  XK_j,      setcfact,       {.f = +0.05} },
	{ MODKEY,           					  XK_k,      setcfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
  // layout stuff
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ Mod1Mask,                     XK_Return,                 zoom,            {0} },
	{ MODKEY,                       XK_Tab,                    view,            {0} },
	{ MODKEY|ShiftMask,             XK_q,                      killclient,      {0} },
	{ MODKEY,                       XK_t,                      setlayout,       {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                      setlayout,       {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_space,                  togglefloating,  {0} },
	{ MODKEY,                       XK_0,                      view,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,             {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};
