#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <sched.h>

static int g_is_done;
int timer_getcounter() {
	struct itimerval cur_it;
	getitimer(ITIMER_REAL, &cur_it);
	return cur_it.it_value.tv_usec;
}

void timer_handler(void);

void signal_handler(int signal, siginfo_t *info, void *ctx) {
	printf("%s: in\n", __func__);
// CHECK begin
	timer_handler();
// CHECK begin
	printf("%s: out\n", __func__);
}

// TODO start

typedef struct {
    long int priority;
    void *data;
} node_t;

typedef struct {
    node_t *nodes;
    int len;
    int size;
} pq_t;


pq_t* pq_create() {

    pq_t *h = (pq_t *)calloc(1, sizeof (pq_t));

    if (h == NULL) {
        printf("MEMORY ERROR\n");
        exit(EXIT_FAILURE);
    }

    return h;
}


void pq_push(pq_t *h, long int priority, void *data) {

    if (h->len + 1 >= h->size) {

        h->size = h->size ? h->size * 2 : 4;

        h->nodes = (node_t *)realloc(h->nodes, h->size * sizeof (node_t));
        if (h->nodes == NULL) {
            printf("MEMORY ERROR\n");
            exit(EXIT_FAILURE);
        }

    }

    int i = h->len + 1;
    int j = i / 2;

    while (i > 1 && h->nodes[j].priority > priority) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }

    h->nodes[i].priority = priority;
    h->nodes[i].data = data;
    h->len++;

}

void *pq_pop(pq_t *h) {

    int i, j, k;

    if (!h->len) {
        return NULL;
    }

    char *data = h->nodes[1].data;
    h->nodes[1] = h->nodes[h->len];
    h->len--;
    i = 1;

    while (1) {
        k = i;
        j = 2 * i;

        if (j <= h->len && h->nodes[j].priority < h->nodes[k].priority) {
            k = j;
        }

        if (j + 1 <= h->len && h->nodes[j + 1].priority < h->nodes[k].priority) {
            k = j + 1;
        }

        if (k == i) {
            break;
        }

        h->nodes[i] = h->nodes[k];
        i = k;
    }

    h->nodes[i] = h->nodes[h->len + 1];
    return data;
}

void *pq_show_next(pq_t *h) {

    if (!h->len) {
        return NULL;
    }

    return h->nodes[1].data;
}

struct timeval time_from_start = {
	.tv_sec = 0,
	.tv_usec = 0
};

typedef struct {
	long int interval_sec;
	long int expires_in_sec;
	void(*handler)(void);
} my_timer;

pq_t* PQ;

void timer_add_new(int sec, void(*soft_hnd)(void)) {

	my_timer* new_timer = (my_timer*)malloc(sizeof(my_timer));
	if (new_timer == NULL) {
            printf("MEMORY ERROR\n");
            exit(EXIT_FAILURE);
    }

	new_timer->interval_sec = sec;
	new_timer->expires_in_sec = sec;
	new_timer->handler = soft_hnd;

	pq_push(PQ, sec, new_timer);
}

void timer_handler(void) {

	time_from_start.tv_sec++;

	my_timer* next_timer = pq_show_next(PQ);

	if (next_timer != NULL) {

		next_timer->expires_in_sec--;

		if (next_timer->expires_in_sec <= 0) {

			while ((next_timer = pq_pop(PQ)) != NULL) {

				next_timer->handler();
				next_timer->expires_in_sec = time_from_start.tv_sec + next_timer->interval_sec;
				pq_push(PQ, next_timer->expires_in_sec, next_timer);
				my_timer* next_next_timer = pq_show_next(PQ);

				if (next_next_timer != NULL) {
					next_next_timer->expires_in_sec -= time_from_start.tv_sec;

					if (next_next_timer->expires_in_sec > 0) {
						break;
					}

				}
			}
		}
	}
}

int timer_init(int sec, void(*soft_hnd)(void)) {
	timer_add_new(sec, soft_hnd);
	return 0;
}

int timer_gettime() {
	return 1e6 * (time_from_start.tv_sec + 1) - timer_getcounter();
}

// TODO end


void hnd3(void) {
	printf("%s: called every 3 secs\n", __func__);
}

void hnd5(void) {
	printf("%s: called every 5 secs\n", __func__);
}

int main(int argc, char *argv[]) {

	PQ = pq_create();

	struct sigaction sa = {
		.sa_sigaction = signal_handler,
	};
	sigemptyset(&sa.sa_mask);
	sigaction(SIGALRM, &sa, NULL);


	timer_init(3, hnd3);
	timer_init(5, hnd5);

	const struct itimerval setup_it = {
		.it_interval = { 1 /*sec*/, 0 /*usec*/},
		.it_value    = { 1 /*sec*/, 0 /*usec*/},
	};
	setitimer(ITIMER_REAL, &setup_it, NULL);

	int count = 0;
	while (!g_is_done) {
		if (!count--) {
			printf("cur_it = %d\n", timer_gettime());
			count = 1000000;
		}

		sched_yield();
	}
	return 0;
}

