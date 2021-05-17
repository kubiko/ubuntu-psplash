/**
 * Copyright (C) 2021 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "psplash.h"

#ifndef PROGRESS_INCREMENTS
# define PROGRESS_INCREMENTS 20 // use default 20%
#endif
#ifndef PROGRESS_UPDATES
#define PROGRESS_UPDATES  1000 // use defaukt 500 milliseconds
#endif

/**
 * Run forewer loop increasing progress by PROGRESS_INCREMENTS
 * every PROGRESS_UPDATES milliseconds
 * until writing to PSPLASH_FIFO fails, signaling psplash main process died
*/
int main() {
	char *rundir;
	int pipe_fd;
	char buffer[20];
	int len = 0;
	int progress = 0;
	int r = 0;

	rundir = getenv("PSPLASH_FIFO_DIR");

	if (!rundir)
		rundir = "/run";

	r = chdir(rundir);
	if (r < 0) {
		printf("Failed to change current dir, ignoring\n");
	}

	if ((pipe_fd = open (PSPLASH_FIFO,O_WRONLY|O_NONBLOCK)) == -1) {
		printf("Failed to open pipe to psplash, quiently exiting as psplash probaly died\n");
		/* Silently exit. psplash probably exitted due to a VC switch */
		exit (0);
	}

	while (1) {
		len = snprintf(buffer, 20, "PROGRESS %d", progress);
		printf("Progress: [%s]\n", buffer);
		r = write(pipe_fd, buffer, len+1);
		if (r < 0) {
			printf("Failed to write to the pipe: %s\n", strerror(-r));
			goto finish;
		}
		// update progress for next run, max progress is 100%
		progress = (progress + PROGRESS_INCREMENTS) % (100 + PROGRESS_INCREMENTS);
		usleep(PROGRESS_UPDATES * 1000); // sleep is in milliseconds, we need micro seconds
	}

finish:
	close(pipe_fd);
	return 0;
}

