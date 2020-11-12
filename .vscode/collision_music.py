import musicalbeeps
from random import randint, random, choice
import time
import threading

# TODO: params
# mote sending frequency
# mote transmit time
# number of motes


def play_something():
    try:
        while True:
            # random wait
            time.sleep(random() * 2)

            if randint(0, 100) > 50:
                # play music
                note = '{}{}'.format(
                    # note
                    choice(list(player.note_frequencies.keys())),
                    # octave
                    randint(3, 5)
                )

                player.play_note(
                    note,
                    duration=random() / 3 + 0.2
                )
    except KeyboardInterrupt:
        print("ok bye.")


if __name__ == '__main__':

    player = musicalbeeps.Player(volume=0.3, mute_output=False)

    threads = []
    for _ in range(8):
        threads.append(
            threading.Thread(target=play_something)
        )

    for t in threads:
        t.start()
