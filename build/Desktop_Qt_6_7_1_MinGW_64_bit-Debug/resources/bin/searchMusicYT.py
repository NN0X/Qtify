import sys
from pytube import Search

def searchMusic(term):
    search = Search(term)
    # return top 10 results
    return [video.title for video in search.results[:9]]


try:
    found = searchMusic(sys.argv[1])
    for i in found:
        print(i)
except:
    pass
