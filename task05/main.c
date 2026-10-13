#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

volatile sig_atomic_t running = 1;

void signal_handler(int sig) {
  (void)sig;
  running = 0;
}

int send_message(int fd, const char *buffer, size_t len) {
  size_t sent = 0;

  while (sent < len && running) {
    ssize_t n = write(fd, buffer + sent, len - sent);

    if (n < 0) {
      if (errno == EINTR)
        continue;
      return -1;
    }

    if (n == 0)
      return -1;

    sent += (size_t)n;
  }

  return sent == len ? 0 : -1;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <UART device>\n", argv[0]);
    return 1;
  }

  time_t start = time(NULL);
  struct tm start_tm;
  localtime_r(&start, &start_tm);

  // logging
  char log_name[64];
  strftime(log_name, sizeof(log_name), "%Y-%m-%d_%H-%M-%S.log", &start_tm);

  FILE *log = fopen(log_name, "w");
  if (log == NULL) {
    perror("Error opening log");
    return 1;
  }

  // uart fd
  int fd = open(argv[1], O_RDWR | O_NOCTTY);

  if (fd == -1) {
    perror("Error opening UART");
    fprintf(log, "UART open error: %s\n", strerror(errno));
    fclose(log);
    return 1;
  }

  // termios setup
  struct termios tty;
  struct termios old_tty;
  int configured = 0;

  if (tcgetattr(fd, &old_tty) == -1) {
    perror("tcgetattr");
    fprintf(log, "tcgetattr error: %s\n", strerror(errno));
    goto cleanup;
  }

  tty = old_tty;

  cfmakeraw(&tty);

  if (cfsetispeed(&tty, B115200) == -1 || cfsetospeed(&tty, B115200) == -1) {
    perror("UART speed");
    fprintf(log, "UART speed configuration error\n");
    goto cleanup;
  }

  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag |= CREAD | CLOCAL;
  tty.c_cflag &= ~CRTSCTS;

  tty.c_cc[VMIN] = 1;
  tty.c_cc[VTIME] = 0;

  if (tcsetattr(fd, TCSANOW, &tty) == -1) {
    perror("tcsetattr");
    fprintf(log, "tcsetattr error: %s\n", strerror(errno));
    goto cleanup;
  }

  configured = 1;

  // signals
  struct sigaction sa = {0};
  sa.sa_handler = signal_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;

  if (sigaction(SIGINT, &sa, NULL) == -1 ||
      sigaction(SIGTERM, &sa, NULL) == -1) {
    perror("sigaction");
    fprintf(log, "Signal configuration error\n");
    goto cleanup;
  }

  printf("UART started: %s\n", argv[1]);
  printf("Log file: %s\n", log_name);

  char buffer[256];
  size_t pos = 0;
  int result = 0;

  while (running) {
    char c;
    ssize_t n = read(fd, &c, 1);

    if (n == 1) {
      printf("Received byte: 0x%02X\n", (unsigned char)c);
      fflush(stdout);
    }

    if (n < 0) {
      if (errno == EINTR) {
        continue;
      }

      perror("UART read error");
      fprintf(log, "UART read error: %s\n", strerror(errno));
      result = 1;
      break;
    }

    if (n == 0) {
      fprintf(stderr, "UART returned EOF\n");
      fprintf(log, "UART returned EOF\n");
      result = 1;
      break;
    }

    // buffer overflow
    if (pos == sizeof(buffer)) {
      printf("Buffer overflow, message may be corrupted\n");
      pos = 0;
    }

    buffer[pos++] = c;

    // message ends
    if (pos >= 2 && buffer[pos - 2] == '\r' && buffer[pos - 1] == '\n') {

      time_t now = time(NULL);
      struct tm now_tm;
      localtime_r(&now, &now_tm);

      char timestamp[32];
      strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &now_tm);

      fprintf(log, "[%s] ", timestamp);
      fwrite(buffer, 1, pos - 2, log);
      fputc('\n', log);
      fflush(log);

      // register algorhytm
      for (size_t i = 0; i < pos - 2; i++) {
        if (buffer[i] >= 'a' && buffer[i] <= 'z') {
          buffer[i] -= ('a' - 'A');
        } else if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
          buffer[i] += ('a' - 'A');
        }
      }

      // sending
      if (send_message(fd, buffer, pos) == -1) {
        if (!running)
          break;

        perror("UART write error");
        fprintf(log, "UART write error: %s\n", strerror(errno));
        result = 1;
        break;
      }

      pos = 0;
    }
  }

  printf("\nProgram stopped\n");

  if (configured)
    tcsetattr(fd, TCSANOW, &old_tty);

  close(fd);
  fclose(log);
  return result;

cleanup:
  if (configured)
    tcsetattr(fd, TCSANOW, &old_tty);

  close(fd);
  fclose(log);
  return 1;
}
