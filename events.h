#ifndef EVENTS_H
# define EVENTS_H

# ifdef __APPLE__

#  define DESTROY_NOTIFY 17
#  define KEY_PRESS 2
#  define KEY_PRESS_MASK 0
# define XK_ESCAPE 53
# define KEY_W   13
# define KEY_A   0
# define KEY_S   1
# define KEY_D   2

# else

#  define DESTROY_NOTIFY DestroyNotify
#  define KEY_PRESS KeyPress
#  define KEY_PRESS_MASK KeyPressMask
#  define XK_ESCAPE XK_Escape
# define KEY_W   119
# define KEY_A   97
# define KEY_S   115
# define KEY_D   100

# endif

#endif
