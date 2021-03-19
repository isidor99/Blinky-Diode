#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static volatile int run = 1;

void sigintHandler(int dummy) {
	run = 0;
}

void writeFile(int file, const char* cmd, const char* err) {
	if (write(file, cmd, strlen(cmd)) != strlen(cmd)) {
		perror(err);
		exit(1);
	}
}

int main() {

	// catch Ctrl + C
	//
	signal(SIGINT, sigintHandler);

	// init
	//
	int file = open("/sys/class/gpio/export", O_WRONLY);
	if (file == -1) {
		perror("Unable to open /sys/class/gpio/export");
		exit(1);
	}

	writeFile(file, "18", "Error writing /sys/class/gpio/export");

	close(file);

	// set the pin direction
	//
	file = open("/sys/class/gpio/gpio18/direction", O_WRONLY);
	if (file == -1) {
		perror("Unable to open /sys/class/gpio/gpio18/direction");
		exit(1);
	}

	writeFile(file, "out", "Error writing to /sys/class/gpio/gpio18/direction");

	close(file);

	// turn on and off
	//
	file = open("/sys/class/gpio/gpio18/value", O_WRONLY);
	if (file == -1) {
		perror("Unable to open /sys/class/gpio/gpio18/value");
		exit(1);
	}

	const char* err = "Error writing to /sys/class/gpio/gpio18/value";

	while (run) {

		writeFile(file, "1", err);

		usleep(200000);

		writeFile(file, "0", err);

		usleep(200000);

		writeFile(file, "1", err);

		usleep(200000);

		writeFile(file, "0", err);

		usleep(200000);

		writeFile(file, "1", err);

		usleep(200000);

		writeFile(file, "0", err);

		usleep(200000);

		writeFile(file, "1", err);

		usleep(200000);

		writeFile(file, "0", err);

		usleep(200000);

		writeFile(file, "1", err);

		usleep(200000);

		writeFile(file, "0", err);

		usleep(200000);

		writeFile(file, "1", err);

		usleep(200000);

		writeFile(file, "0", err);

		usleep(2000000);
	}

	close(file);

	file = open("/sys/class/gpio/unexport", O_WRONLY);
	if (file == -1) {
		perror("Unable to open /sys/class/gpio/unexport");
		exit(1);
	}

	writeFile(file, "18", "Error writing to /sys/class/gpio/unexport");

	close(file);

	return 0;
}

