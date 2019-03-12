# DJmixer
DJ mixer based on ultrasonic sensor_by Xiangrui Xu, Rui Zhang, Guangyao Li


log:


pi@raspberrypi:~/DJmixer $ g++ songswitching.c -o songswitching -lwiringPi


songswitching.c:21:1: error: expected unqualified-id before ‘int’
 int oldflag =-1,
 ^~~
songswitching.c: In function ‘int main()’:
songswitching.c:80:11: error: ‘autofile’ was not declared in this scope
  autofile();
           ^
songswitching.c:90:15: error: ‘soundpath1’ was not declared in this scope
    soundpath =soundpath1;
               ^~~~~~~~~~
songswitching.c:109:6: error: ‘oldflag’ was not declared in this scope
   if(oldflag <=0)
      ^~~~~~~
songswitching.c:119:22: error: too few arguments to function ‘int execve(const char*, char* const*, char* const*)’
      execve(soundpath);
                      ^
In file included from songswitching.c:5:0:
/usr/include/unistd.h:554:12: note: declared here
 extern int execve (const char *__path, char *const __argv[],
            ^~~~~~
songswitching.c:138:23: error: too few arguments to function ‘int execve(const char*, char* const*, char* const*)’
       execve(soundpath);
                       ^
In file included from songswitching.c:5:0:
/usr/include/unistd.h:554:12: note: declared here
 extern int execve (const char *__path, char *const __argv[],
            ^~~~~~
