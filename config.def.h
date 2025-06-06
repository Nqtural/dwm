/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx      = 2;          /* border pixel of windows */
static const int startwithgaps	        = 1;          /* 1 means gaps are used by default */
static const unsigned int gappx         = 10;          /* default gap between windows in pixels */
static const unsigned int snap          = 16;         /* snap pixel */
static const int showbar                = 1;          /* 0 means no bar */
static const int topbar                 = 1;          /* 0 means bottom bar */
static const int user_bh                = 12;          /* 2 is the default spacing around the bar's font */
static const char *fonts[]              = {
    "SourceCodePro-Regular:size=10",
    "JetBrainsMonoNerdFontMono-Regular:size=12"
};
static const char dmenufont[]           = "monospace:size=10";
static const char col_pri_bg[]          = "#171219";
static const char col_sec_bg[]          = "#2b272e";
static const char col_pri_fg[]          = "#d5dbc5";
static const char col_sec_fg[]          = "#f1f8e1";
static const char col_accent[]          = "#2874b6";
static const unsigned int baralpha      = OPAQUE;
static const unsigned int borderalpha   = OPAQUE;
static const char *colors[][3]          = {
	/*               fg             bg          border   */
	[SchemeNorm] = { col_pri_fg,    col_pri_bg,  col_sec_bg },
	[SchemeSel]  = { col_accent,    col_pri_bg,  col_accent  },
};
static const unsigned int alphas[][3]   = {
    /*               fg         bg          border*/
    [SchemeNorm] = { OPAQUE,    baralpha,   borderalpha },
    [SchemeSel]  = { OPAQUE,    baralpha,   borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const char ptagf[] = "[%s: %s]";	    /* format of a tag label */
static const char etagf[] = "[%s]";	    /* format of an empty tag */
static const int lcaselbl = 0;		    /* 1 means make tag label lowercase */	

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                    instance    title   tags mask   isfloating  monitor */
	{ "PLACEHOLDER44444444",    NULL,       NULL,   1 << 8,     0,          -1 },
};

/* layout(s) */
static const float mfact        = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

	/* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, */
static const Layout layouts[] = {
	/* symbol   arrange function */
	{ "[]=",    tile },    /* first entry is default */
	{ "><>",    NULL },    /* no layout function means floating behavior */
	{ "[M]",    monocle },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_pri_bg, "-nf", col_pri_fg, "-sb", col_accent, "-sf", col_sec_fg, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key         function        argument */
	/* { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, */
	/* { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } }, */
	{ MODKEY|ShiftMask,             XK_b,       togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,       rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,       rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,       focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_i,       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,     view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,       killclient,     {0} },
	{ MODKEY,                       XK_t,       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },
	{ MODKEY,                       XK_f,       togglefullscr,  {0} },
	{ MODKEY,                       XK_0,       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,   setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_plus,    setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,   setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_plus,    setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask|ShiftMask, XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	/* { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } }, */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

