import sys
from pytube import Search

def download(name):
    search = Search(name)
    video = search.results[0].streams.filter(file_extension="mp4", only_audio=True).first()
    video.download(output_path="resources/music")


download(sys.argv[1])