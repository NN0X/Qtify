import sys
from pytube import Search
from pydub import AudioSegment
import os

def download(id):
    search = Search(id)
    video = search.results[0].streams.filter(file_extension="mp4", only_audio=True).first()
    video.download(output_path="resources/music", filename=id+".mp4")
    audio = AudioSegment.from_file("resources/music/"+id+".mp4", format="mp4")
    audio.export("resources/music/"+id+".mp3", format="mp3")
    os.remove("resources/music/"+id+".mp4")


try:
    download(sys.argv[1])
    print("OK")
except:
    print("ERROR")