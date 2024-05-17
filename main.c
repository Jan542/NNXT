#include <nnxt.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_TIMERS 16

typedef uint16_t EventType;
typedef uint16_t TimerType;
uint16_t MAX_TIMER_TYPES;

typedef uint16_t TimerType {
    TIMER_1,
    TIMER_2,
    // Weitere Timer können hier hinzugefügt werden
    MAX_TIMER_TYPES; // Marker für die Anzahl der Timer-Typen
}

typedef struct {
    int duration; // Dauer des Timers in Millisekunden
    int remainingTime; // Verbleibende Zeit des Timers
    bool active; // Status des Timers
    EventType event; // Ereignis, das ausgelöst wird, wenn der Timer abgelaufen ist
} Timer;

static Timer timers[MAX_TIMERS];

void setTimer(TimerType timer, int time, EventType ev) {
    if (timer < MAX_TIMER_TYPES) {
        timers[timer].duration = time;
        timers[timer].remainingTime = time;
        timers[timer].active = false;
        timers[timer].event = ev;
    }
}

void startTimer(TimerType timer) {
    if (timer < MAX_TIMER_TYPES) {
        timers[timer].active = true;
    }
}

void cancelTimer(TimerType timer) {
    if (timer < MAX_TIMER_TYPES) {
        timers[timer].active = false;
    }
}

// Funktion zum Aktualisieren der Timer
void updateTimers() {
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (timers[i].active) {
            if (timers[i].remainingTime > 0) {
                timers[i].remainingTime--;
                if (timers[i].remainingTime == 0) {
                    // Timer ist abgelaufen, löse das entsprechende Ereignis aus
                    setEvent(timers[i].event);
                    timers[i].active = false; // Timer deaktivieren
                }
            }
        }
    }
}
