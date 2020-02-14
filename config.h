/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_gray5[]       = "#1d1d1d";
static const char col_red1[]        = "#c40233";
static const char col_red2[]        = "#424242";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_red2, col_gray2 },
	[SchemeSel]  = { col_gray4, col_red1,  col_red1  },
	[SchemeStatus]  = { col_red1, col_gray5,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray5, col_red1,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_red1, col_gray5,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_red1, col_gray5,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray5, col_gray5,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating canfocus   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,         1,         -1 },
	{ "mpv",     NULL,       NULL,       0,            1,           1,           -1 },
	{ "com-sittinglittleduck-DirBuster-Start",     NULL,       NULL,       0,            1,           1,           -1 },
	{ "Microsoft Teams - Preview",     NULL,       "Microsoft Teams Notification",       1<<8,            1,           0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.70; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "\uE011",   grid },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* key definitions */
#define XF86MonBrightnessDown           0x1008ff03
#define XF86MonBrightnessUp             0x1008ff02
#define XF86AudioLowerVolume            0x1008ff11
#define XF86AudioMute                   0x1008ff12
#define XF86AudioRaiseVolume            0x1008ff13
#define XF86KbdBrightnessDown           0x1008ff06
#define XF86KbdBrightnessUp             0x1008ff05

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_red1, "-sb", col_red1, "-sf", col_gray5, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *screenlock[]  = { "dm-tool", "lock", NULL };
static const char *surf[]  = { "surf", NULL };
static const char *flameshot[]  = { "flameshot", "gui", NULL };
static const char *mpvyt[]  = { "mpvyt", "gui", NULL };
static const char *dwmkill[]  = { "dwm_kill", NULL };

static const char *cmdbrightnessup[]  = { "dwm_stat", "sudo", "brightness", "up", NULL };
static const char *cmdbrightnessdown[]  = { "dwm_stat", "sudo", "brightness", "down", NULL };
static const char *cmdkbbrightup[]  = { "dwm_stat", "sudo", "kb_brightness", "up", NULL };
static const char *cmdkbbrightdown[]  = { "dwm_stat", "sudo", "kb_brightness", "down", NULL };

static const char *mutecmd[] = { "dwm_stat", "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *volupcmd[] = { "dwm_stat", "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *voldowncmd[] = { "dwm_stat", "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = screenlock } },
	{ MODKEY,                       XK_s,      spawn,          {.v = surf } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = flameshot } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = mpvyt } },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = dwmkill } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_l,  	   focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      focusmon,       {.i = +1 } },
	{ MODKEY|ControlMask,           XK_l,      tagmon,         {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,      tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    { 0,                       XF86MonBrightnessDown, spawn,   {.v = cmdbrightnessdown } },
    { 0,                       XF86MonBrightnessUp,   spawn,   {.v = cmdbrightnessup }   },
    { 0,                       XF86KbdBrightnessDown, spawn,   {.v = cmdkbbrightdown }   },
    { 0,                       XF86KbdBrightnessUp,   spawn,   {.v = cmdkbbrightup }     },
    { 0,                       XF86AudioLowerVolume,  spawn,   {.v = voldowncmd } },
    { 0,                       XF86AudioRaiseVolume,  spawn,   {.v = volupcmd }   },
    { 0,                       XF86AudioMute,         spawn,   {.v = mutecmd }    },
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

