# ⏱ Timer and Timeline Utils for `C`
[![C/C++ CI](https://github.com/recp/tm/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/recp/tm/actions/workflows/c-cpp.yml)
[![MSBuild](https://github.com/recp/tm/actions/workflows/msbuild.yml/badge.svg)](https://github.com/recp/tm/actions/workflows/msbuild.yml)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/ba230efea5f94149822a48e12584942f)](https://www.codacy.com/app/recp/tm?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=recp/tm&amp;utm_campaign=Badge_Grade)

This library provides an easy way to set timers and timeouts. 
As initial version all timers run in single runloop at seperate thread. 
Currently only one thread is used for all timers, because there is only one runloop. In the future multiple runloop may be allowed. 

#### Documentation

Currently all docs can be found in headers but in the future complete docs will be published. 

#### Javascript and Swift/Objective-C like API

`setTimeout` in javascript is very useful and it is now in `C`:

```C
tm_settimeout(callback, arg, delay);
```

## TODOs:

- [ ] Improve loopkup, make timers ordered. This may reduce some lookup operations runloop 
- [ ] Tests
- [ ] More time and timeline utils
- [ ] More platform support

## Build

### Unix (Autotools)

```bash
$ sh autogen.sh
$ ./configure
$ make
$ [sudo] make install
```

you can grap library in .libs folder after build finished

### Windows (MSBuild)
Windows related build files, project files are located in `win` folder,
make sure you are inside `tm/win` folder.
Code Analysis are enabled, it may take awhile to build

```Powershell
$ cd win
$ .\build.bat
```

#### Example usage

```C
#include <tm/tm.h>

/* callback */
void
mytimer(tm_timer *timer) {
  printf("my timer\n");
}

void
delayed_func(void *arg) {
  printf("settimeout: %s\n", (const char *)arg);
}

int 
main(int argc, const char * argv[]) {
  tm_timer   *timer1, *timer2, *timer3;
  tm_interval start, end, elapsed;
 
  /* option 1: alloc timer and start */
  timer1 = tm_alloc(mytimer, 1.5); /* 1.5 seconds */
  tm_start(timer1);
  
  /* option 2: alloc timer and start with delay */
  timer2 = tm_alloc(mytimer, 1.5); /* 1.5 seconds */
  tm_start_at(timer2, 0.05);       /* start after 0.05 secons */
  
  /* option 3: alloc timer and start with delay */
  timer3 = tm_schedule(mytimer, 1.5, 0.05); /* same as tm_alloc + tm_start_at */
  
  /* option 4: javascript-like setTimeout */
  tm_settimeout(delayed_func, "Hello World!", 0.00001);
  
  /*
  
  if we call free here timers will be stopped 
  
  tm_free(timer1);
  tm_free(timer2);
  tm_free(timer3);

  */
  
  /* measure elapsed time */
  start = tm_time();
  
  /* do stuff */
  
  end = tm_time();
  
  elapsed = end - start;
  
  /* wait timers to finish; otherwise main thread will cause timer thread to be exited */
  tm_wait();

  return 0;
}

```

## License
MIT. check the LICENSE file
