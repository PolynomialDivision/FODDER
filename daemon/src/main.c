#include <libubus.h>
#include <stdio.h>


int main(int argc, char **argv) {
  const char *ubus_socket = NULL;
  int ch;

  while ((ch = getopt(argc, argv, "cs:")) != -1) {
    switch (ch) {
      case 's':
        ubus_socket = optarg;
        break;
      default:
        break;
    }
  }

  argc -= optind;
  argv += optind;

  uloop_init();
  signal(SIGPIPE, SIG_IGN);

  ctx = ubus_connect(ubus_socket);
  if (!ctx) {
    fprintf(stderr, "Failed to connect to ubus\n");
    return -1;
  }

  ubus_add_uloop(ctx);

  uloop_run();

  ubus_free(ctx);
  uloop_done();

  return 0;
}