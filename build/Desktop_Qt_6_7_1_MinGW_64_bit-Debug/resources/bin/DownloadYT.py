import sys
from pytube import Search

def download(id):
    search = Search(id)
    video = search.results[0].streams.filter(file_extension="mp4", only_audio=True).first()
    video.download(output_path="resources/music", filename=id+".mp4")

try:
    download(sys.argv[1])
    print("OK")
except:
    print("ERROR")