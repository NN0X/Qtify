from pydub import AudioSegment
import sys

def getDuration(file):
    audio = AudioSegment.from_mp3(file)
    duration = len(audio) / 1000
    return int(duration)

try:
    print(getDuration("resources/music/" + sys.argv[1] + ".mp3"))
except:
    print("ERROR")