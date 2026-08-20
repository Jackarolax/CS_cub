#ifndef EVENTS_H
# define EVENTS_H

# ifdef __APPLE__

#  define DESTROY_NOTIFY 17
#  define KEY_PRESS 2
#  define KEY_PRESS_MASK 0
# define XK_ESCAPE 53

# else

#  define DESTROY_NOTIFY DestroyNotify
#  define KEY_PRESS KeyPress
#  define KEY_PRESS_MASK KeyPressMask
#  define XK_ESCAPE XK_Escape

# endif

#endif
