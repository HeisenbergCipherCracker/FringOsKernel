#include <fudge.h>
#include <abi.h>

static void onmain(unsigned int source, void *mdata, unsigned int msize)
{

    struct ctrl_clocksettings settings;
    unsigned int timestamp;

    if (!call_walk_absolute(FILE_L0, option_getstring("clock")))
        PANIC();

    if (!call_walk_relative(FILE_L1, FILE_L0, "ctrl"))
        PANIC();

    call_read_all(FILE_L1, &settings, sizeof (struct ctrl_clocksettings), 0);

    timestamp = time_unixtime(settings.year, settings.month, settings.day, settings.hours, settings.minutes, settings.seconds);

    channel_send_fmt1(CHANNEL_DEFAULT, EVENT_DATA, "%u\n", &timestamp);

}

void init(void)
{

    option_add("clock", "system:clock/if.0");
    channel_bind(EVENT_MAIN, onmain);

}

