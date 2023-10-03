#include<X11/Xutil.h>
#include<stdio.h>

int main(){
  Display* dsp = XOpenDisplay(NULL);
  Window window = XCreateSimpleWindow(dsp,
    DefaultRootWindow(dsp),
    100,100,200,200, //x,y,w,h
    0,0, //border
    0); //backgd

  const int eventMask = KeyPressMask;
  XSelectInput(dsp, window, eventMask);

  Atom wmDelete = XInternAtom(dsp, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(dsp, window, &wmDelete, 1);

  XStoreName(dsp, window, "mywin");
  XMapWindow(dsp, window);

  // recieve events
  XEvent evt;
  int isRunning = 1;
  while(isRunning) {
     XNextEvent(dsp, &evt);
     switch (evt.type) {
        case KeyPress:
            printf("key pressed: %d\n", evt.xkey.keycode);
        break;
        case ClientMessage:
            // receive Exit event
            if (evt.xclient.data.l[0] == wmDelete) {
                XDestroyWindow(dsp, window);
                XFlush(dsp);
                isRunning = 0;
            }
        break;
        default:;
     }
  }


  XCloseDisplay(dsp);
  return 0;
}
