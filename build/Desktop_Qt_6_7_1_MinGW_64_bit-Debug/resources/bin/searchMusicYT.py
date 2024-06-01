import sys
from pytube import Search

def searchMusic(term):
    search = Search(term)
    info = [video.vid_info for video in search.results[:9]]
    titles = [video.title for video in search.results[:9]]
    ids = [info['videoDetails']['videoId'] for info in info]
    return titles, ids


try:
    for title, id in zip(*searchMusic(sys.argv[1])):
        print(f"{title}\t{id}")
except:
    pass



