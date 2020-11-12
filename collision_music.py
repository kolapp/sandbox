import musicalbeeps
from random import randint, random, choice
import time
import threading

# TODO: params

# mote sending frequency [secs]
mote_sending_freq = 12*60
# mote_sending_freq = 60
# mote_sending_freq = 5

# mote transmit time [ms]
mote_transmit_times = [60/1000, 100/1000, 200/1000, ]

# change data rate, longer sends
# for k, v in enumerate(mote_transmit_times):
#     mote_transmit_times[k] = mote_transmit_times[k]*3

# number of motes
number_of_motes = 100


def play_something(delay):
    player = musicalbeeps.Player(volume=0.3, mute_output=False)

    # scattering motes in time
    print(f"delay={delay}")
    time.sleep(delay)

    while True:
        try:
            # play music
            note = '{}{}'.format(
                # note
                choice(list(player.note_frequencies.keys())),
                # octave
                randint(3, 5)
            )

            player.play_note(
                note,
                duration=choice(mote_transmit_times)
            )

            # wait for next send
            time.sleep(mote_sending_freq)
        except KeyboardInterrupt:
            print("ok bye.")


if __name__ == '__main__':
    motes = []
    for _ in range(number_of_motes):
        motes.append(threading.Thread(
            target=play_something,
            kwargs={"delay": random() * mote_sending_freq}
        ))

    for m in motes:
        m.start()
