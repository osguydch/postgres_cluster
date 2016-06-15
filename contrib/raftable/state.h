#ifndef RAFTABLE_STATE_H
#define RAFTABLE_STATE_H

#define RAFTABLE_KEY_LEN (64)

typedef struct RaftableKey
{
	char data[RAFTABLE_KEY_LEN];
} RaftableKey;

typedef struct RaftableEntry
{
	RaftableKey key;
	int block;
} RaftableEntry;

typedef struct RaftableField {
	size_t keylen;
	size_t vallen;
	bool isnull;
	char data[1];
} RaftableField;

typedef struct RaftableUpdate {
	int expector;
	int fieldnum;
	char data[1];
} RaftableUpdate;

typedef struct State *StateP;

void state_set(StateP state, const char *key, const char *value, size_t len);
char *state_get(StateP state, const char *key, size_t *len);

void state_update(StateP state, RaftableUpdate *update, bool clear);
void *state_make_snapshot(StateP state, size_t *size);

void *state_scan(StateP state);
bool state_next(StateP state, void *scan, char **key, char **value, size_t *len);

void state_shmem_request(void);
StateP state_shmem_init(void);

#endif
