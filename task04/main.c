#include <stdio.h>
#include <time.h>
#include <sys/utsname.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct utsname info;

    char hostname[256];

    time_t currentTime;

    FILE *output = stdout;

    gethostname(hostname, sizeof(hostname));

    uname(&info);

    currentTime = time(NULL);

    if (argc > 1)
    {
        FILE *checkFile = fopen(argv[1], "r");

        if (checkFile != NULL)
        {
            printf("Warning: file already exists. Information will be appended.\n");
            fclose(checkFile);
        }

        output = fopen(argv[1], "a");

        if (output == NULL)
        {
            printf("Cannot open file.\n");
            return 1;
        }
    }

    fprintf(output, "============================\n");
    fprintf(output, "System information\n");
    fprintf(output, "============================\n");

    fprintf(output, "Hostname: %s\n", hostname);
    fprintf(output, "Current time: %s", ctime(&currentTime));
    fprintf(output, "OS: %s\n", info.sysname);
    fprintf(output, "Kernel release: %s\n", info.release);
    fprintf(output, "Kernel version: %s\n", info.version);
    fprintf(output, "Hardware: %s\n", info.machine);

    if (output != stdout)
    {
        fclose(output);
    }

    return 0;
}
