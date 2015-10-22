#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <linux/input.h>
#include <QDebug>

int keyscan(void)
{
   int fd;
   int key_value,i=0,count;
   struct input_event ev_key;
   fd = open("/dev/input/event0", 666);

   if (fd < 0)
  {
    printf("can't open device!\n");

    //exit(1);
    close(fd);
    return 0;
  }
  else
  {

    printf("  open keyboard device!\n");
  }

  for (;;)
  {
    count = read(fd,&ev_key,sizeof(struct input_event));

    printf("count  %d\n",count);
    for(i=0; i<(int)count/sizeof(struct input_event); i++)
        if(EV_KEY==ev_key.type)
          printf("type:%d,code:%d,value:%d\n", ev_key.type,ev_key.code,ev_key.value);
        if(EV_SYN==ev_key.type)
          printf("syn event\n");
  }
   close(fd);
   return 0;
}
