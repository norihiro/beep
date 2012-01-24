#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


FILE *out;
unsigned long interval=1000000;
int length=500;
int count=-1;
int fmin=50, fmax=4000;

int randmm(int min, int max)
{
	return min+(int)((long long)random()*(max-min+1)/RAND_MAX);
}

int check_pcspkr()
{
	FILE *fp = fopen("/proc/modules", "r");
	if(fp) {
		int ret=1;
		char line[128];
		while(fgets(line, sizeof(line)-1, fp)) {
			if(strncmp(line, "pcspkr ", 7)==0) {
				ret = 0;
				break;
			}
		}
		fclose(fp);
		return ret;
	}
	return -1;
}

main(int argc, char **argv)
{
	int i, c;
	FILE * fp = 0;
	int digit_optind = 0;
	uid_t uid = getuid();
	setuid(0);

#ifdef ENABLE_INSPCSPKR
	if(check_pcspkr()==1) {
		system("/sbin/modprobe pcspkr");
	}
#endif

	/* open console */
	out=fopen("/dev/console", "w");
	if(!out) {
		fputs("error: cannot open /dev/console\n", stderr);
		return __LINE__;
	}

	/* restore UID */
	setuid(uid);

	srandom(getpid());

	while(1)
	{
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			// name, has_arg, flag, val
			{"interval", 1, 0, 'i'},
			{"count", 1, 0, 'c'},
			{"length", 1, 0, 'l'},
			{"file", 1, 0, 'f'},
			{"version", 0, 0, 'v'},
			{0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, "i:c:l:f:v", long_options, &option_index);
		if(c==-1) break;
		switch(c)
		{
			case 'v':
				puts("beep version 1.3 (C) Kamae Norihiro 2008");
				return 0;
			case 'i':
				interval = atof(optarg)*1000000;
				break;
			case 'c':
				count = atoi(optarg);
				break;
			case 'l':
				length = atof(optarg)*1000;
				break;
			case 'f':
				if(strcmp(optarg, "-")==0)
					fp = stdin;
				else
					fp = fopen(optarg, "r");
				if(!fp)
				{
					fprintf(stderr, "error: file %s\n", optarg);
					return __LINE__;
				}
				break;
			default:
				//fprintf(stderr, "unknown option: 0%o\n", c);
				return __LINE__;
		}
	}
	if(optind < argc)
	{
		fprintf(stderr, "non-option argv-elements:");
		while(optind<argc) fprintf(stderr, " %s", argv[optind++]);
		fprintf(stderr, "\n");
		return __LINE__;
	}

	while(1)
	{
		int freq;
		if(fp)
		{
			char sz[126];
			int ret;
			ret = fgets(sz, sizeof(sz), fp);
			if(!ret) break;
			ret = sscanf(sz, "%d%d%d", &freq, &length, &interval);
			if(ret!=3) continue;

			interval *= 1000;
		}
		else
		{
			freq = randmm(fmin, fmax);
		}

		fprintf(out, "\33[11;%d]\33[10;%d]\a", length, freq);
		fflush(out);

		if(count>0) if(!--count) break;

		usleep(interval);
	}
	fclose(out);
	return 0;
}

