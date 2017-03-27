#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

int MsgHandle(void * /*arg*/, void *msg) {
  char *s = (char*)msg;
  char *p, *q;
	char gfid[10], txt[4096];
	// printf("%s\n", s);
	// chat
  if (strncmp(s, "type@=chatmsg", 13) == 0) {
    p = strstr(s, "nn@=");
    if (p) {
      p += 4;
      q = strchr(p, '/');
      *q++ = 0;
      printf("%s", p);
      p = strstr(q, "txt@=");
      if (p) {
        p += 5;
        q = strchr(p, '/');
        *q++ = 0;
        strncpy(txt, p, 4096);
      }
    	p = strstr(q, "level@=");
			if (p) {
				p += 7;
				q = strchr(p, '/');
				*q = 0;
				printf("#%s#%s\n", p, txt);
			}
    }
  }
  if (strncmp(s, "type@=dgb", 9) == 0) {
		p = strstr(s, "gfid@=");
		if (p) {
			p += 6;
			q = strchr(p, '/');
			*q++ = 0;
			strncpy(gfid, p, 10);
			p = strstr(q, "nn@=");
			if (p) {
				p += 4;
				q = strchr(p, '/');
				*q++ = 0;
				printf("%s", p);
				p = strstr(q, "level@=");
				if (p) {
					p += 7;
					q = strchr(p, '/');
					*q = 0;
					printf("#%s#@%s\n", p, gfid);
				}
			}
		}
  }

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("%s\n", "invalid argv");
    return 0;
  }
  int rid = atoi(argv[1]);
  if (rid <= 10000) {
    printf("invalid room id: %d\n", rid);
    return -1;
  }
  Client client;
  client.Connect("openbarrage.douyutv.com", 8601);
  client.JoinRoom(rid);
  client.Watch(MsgHandle, NULL);
  return 0;
}
