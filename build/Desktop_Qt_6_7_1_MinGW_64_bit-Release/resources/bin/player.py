import pygame
import time
import threading
import sys

pygame.mixer.init()

PATH = "resources/music/"
PATH_DEBUG = "../music/"

timerElapsed = 0
duration = 10000

state = True

def timer():
    global timerElapsed
    while state:
        time.sleep(1)
        if pygame.mixer.music.get_busy():
            timerElapsed += 1

def start(time, volume):
    global timerElapsed
    timerElapsed = time
    pygame.mixer.music.play(start=time)
    pygame.mixer.music.set_volume(volume / 100)

def play():
    pygame.mixer.music.unpause()

def pause():
    if pygame.mixer.music.get_busy():
        pygame.mixer.music.pause()

def skip(time):
    global timerElapsed
    try:
        timerElapsed = time
        pygame.mixer.music.set_pos(time)
    except:
        pass

def volume(volume):
    pygame.mixer.music.set_volume(volume / 100)

def stop():
    pygame.mixer.music.stop()

def load(id):
    pygame.mixer.music.load(PATH + id + ".mp3")

def command():
    global state
    global duration
    command = input()
    if command == "PLAY":
        play()
    elif command == "PAUSE":
        pause()
    elif command == "STOP":
        stop()
    elif command == "SKIP":
        skip(int(input()))
    elif command == "VOLUME":
        volume(int(input()))
    elif command == "LOAD":
        stop()
        load(input())
        start(int(input()), int(input()))
        duration = int(input())
    elif command == "TIME":
        if timerElapsed >= duration:
            print("END")
        else:
            print(timerElapsed)
    elif command == "EXIT":
        stop()
        state = False
        sys.exit()

def main():
    threading.Thread(target=timer).start()
    while True:
        command()

if __name__ == "__main__":
    main()