#ifndef EVENTS_H
# define EVENTS_H

# ifdef __APPLE__

#  define DESTROY_NOTIFY 17
#  define KEY_PRESS 2
#  define KEY_RELEASE 3
#  define KEY_PRESS_MASK 0
# define XK_ESCAPE 53
# define XK_W   13
# define XK_A   0
# define XK_S   1
# define XK_D   2
# define KEY_LEFT   123
# define KEY_RIGHT  124

# else

#  define DESTROY_NOTIFY DestroyNotify
#  define KEY_PRESS KeyPress
#  define KEY_PRESS_MASK KeyPressMask
#  define XK_ESCAPE XK_Escape
# define XK_W   XK_w
# define XK_A   XK_a
# define XK_S   XK_s
# define XK_D   XK_d
# define KEY_LEFT   XK_Left
# define KEY_RIGHT  XK_Right

# endif

#endif
