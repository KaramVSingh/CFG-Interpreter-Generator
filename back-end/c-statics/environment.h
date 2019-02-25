#if !defined(ENVIRONMENT_H)
#define ENVIRONMENT_H
#define SIZE 100

// This struct can be changed to include what you want data to be stored as in your language.
typedef struct data_t {
    void *data; 
    char **attributes; 
    int n_attributes;
} data_t;

typedef struct _data_t {
    char *_name;
    struct _data_t *next;
    data_t *_data;
} _data_t;

typedef struct environment_t {
    _data_t **data;
} environment_t;

environment_t* init(environment_t *h);
int hash_string(char *s);
data_t* get_from_environment(char *name, environment_t *map);
void set_in_environment(char *name, data_t *d, environment_t *map);
data_t** get_all_environment(environment_t *map, int *len, char ***names);

#endif