import sys
from pymediainfo import MediaInfo

def getDuration(file):
    media_info = MediaInfo.parse(file)
    return int(media_info.tracks[0].duration / 1000)

try:
    print(getDuration("resources/music/" + sys.argv[1] + ".mp4"))
except:
    print("ERROR")