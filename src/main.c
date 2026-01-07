#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define GAMEMODE_CONFIG_PATH "gamemodes"
#define DEFAULT_GAMEMODE "sandbox"
#define DEFAULT_MAP "gm_construct"
#define DEFAULT_MAX_PLAYERS 20
#define DEFAULT_HOSTNAME "fart server please"


// Gamemode-Workshop ID Map Structure
struct gmws_t {
	char gamemode[32];
	char workshop_id[16];
};


// Printing out usage information
static void print_usage(char *command_name) {
	printf("Usage: %s [-g gamemode] [-m map] [-p max_players] [-h hostname]\n", command_name);
}

static void trim(char *s) {
	int i = 0, j = 0;
	while (s[i] == ' ') i++;
	while (s[j++] = s[i++]);
}

int main(int argc, char **argv) {
	if (argc <= 1) {
		print_usage(argv[0]);
		return 0;
	}

	char gamemode[32]	= DEFAULT_GAMEMODE;
	char map[32]		= DEFAULT_MAP;
	int  max_players	= DEFAULT_MAX_PLAYERS;
	char hostname[64]	= DEFAULT_HOSTNAME;
	char workshop_id[16];

	// Read gamemodes from GAMEMODE_CONFIG_PATH. Stick 'em into the gmws_map
	struct gmws_t gmws_map[64];
	FILE *file = fopen(GAMEMODE_CONFIG_PATH, "r");
	if (!file) {
		printf("File open error!\n");
		return 1;
	}
	int i = 0;
	while (fscanf(file, "%31s %15s", gmws_map[i].gamemode, gmws_map[i].workshop_id) != EOF) {
		i++;
	}

	for (int i = 1; i < argc; i++) {
		char *arg = argv[i];
		char *next = argv[i + 1];

		if (strcmp(arg, "-g") == 0 || strcmp(arg, "--gamemode") == 0) {
			strcpy(gamemode, next);

			// Where that damn index
			for (int j = 0; j < 64; j++) {
				if (strcmp(gmws_map[j].gamemode, gamemode) != 0) continue;
				strcpy(workshop_id, gmws_map[j].workshop_id);
				break;
			}

			i++;
			continue;
		}

		if (strcmp(arg, "-m") == 0 || strcmp(arg, "--map") == 0) {
			strcpy(map, next);
			i++;
			continue;
		}
		
		if (strcmp(arg, "-p") == 0 || strcmp(arg, "--players") == 0) {
			max_players = atoi(next);
			i++;
			continue;
		}

		if (strcmp(arg, "-h") == 0 || strcmp(arg, "--hostname") == 0) {
			strcpy(hostname, next);
			i++;
			continue;
		}
	}

	// exec functions don't take numbers, so convert numbers to strings.
	char max_players_str[4];
	sprintf(max_players_str, "%d", max_players);

	printf("\n==========================================================================\n");
	printf("Executing: srcds_run +maxplayers %s -console -allowquit +host_workshop_collection %s +gamemode %s +map %s +hostname %s\n", max_players_str, workshop_id, gamemode, map, hostname);
	printf("==========================================================================\n\n");
	int exec_err = execlp("srcds_run", "srcds_run", "+maxplayers", max_players_str, "-console", "-allowquit", "+host_workshop_collection", workshop_id, "+gamemode", gamemode, "+map", map, "+hostname", hostname, NULL);
	if (exec_err == -1) {
		printf("execlp error! %s", strerror(errno));
	}

	return 0;
}
