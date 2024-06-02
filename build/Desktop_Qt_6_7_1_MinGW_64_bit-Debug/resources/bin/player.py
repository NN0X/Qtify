import threading
import time
from pydub import AudioSegment
from pydub.playback import play
import sys
import os

def counter(audioLen, startS):
    count = startS
    while True:
        print(count)
        time.sleep(1)
        count += 1
        if count >= audioLen:
            print("END")
            break

def checker():
    while True:
        if input() == "STOP":
            os._exit(0)

def playMusic(file, startS):
    audio = AudioSegment.from_file(file)
    audioLen = audio.duration_seconds
    counter_thread = threading.Thread(target=counter, args=(audioLen,startS), daemon=True)
    checker_thread = threading.Thread(target=checker, daemon=True)
    checker_thread.start()
    counter_thread.start()
    play(audio[startS*1000:])
    counter_thread.join()

try:
    playMusic("resources/music/" + sys.argv[1] + ".mp4", int(sys.argv[2]))
except:
    print("ERROR")