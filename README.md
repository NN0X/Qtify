# Qtify

Qtify is a music player taking advantage of YouTube API for searching and downloading audio files. Files are downloaded in MP4 and then converted to MP3 using FFmpeg.

Qtify additionaly allows user to create and manage custom playlists, which can be done through simple GUI or manually.

As of version 1.0.0 GUI doesn't support importing own songs, however it can be achieved through simple txt file edition.

## Installation

### Requrements

- FFmpeg (tested on version 7.0.0, should work on other versions)

In case FFmpeg is not installed Qtify will work, however it's usage will be limited to playlists and playing already downloaded MP3s

1. Check whether FFmpeg is installed by entering this command in CMD
   ```
   ffmpeg
   ```
   In case of the followning output follow [this](https://www.wikihow.com/Install-FFmpeg-on-Windows) guide
   ```
   'ffmpeg' is not recognized as an internal or external command,
   operable program or batch file.
   ```
2. Go to [releases](https://github.com/NN0X/Qtify/releases) page of the repository
3. Download `Qtify.zip`
4. Unzip the archive and find `Qtify.exe`
5. Run `Qtify.exe`
6. (OPTIONALLY) Create link to `Qtify.exe`

## Troubleshooting

### Windows Defender SmartScreen

Windows Defender may incorrectly flag safe programs, such as in this case. Just press 'Run anyway'.

### Other antivirus software

If other antivirus programs flag `Qtify.exe`, wait for the check to finish and then restart Qtify.

### Download issues

Sometimes the download will fail the first time. This is indicated by the title changing back from yellow to white. In this case, try again. If the download still fails, there are three posibilities:

1. Problem is on your side (for example, internet issues)
2. Problem is on YouTube's side (for example, the API is down)
3. Problem is on video owner's side (the video is blocked from being downloaded)

## Additional information

### Importing songs

1. Navigate to `resources\music` directory in Qtify root directory
2. Paste your MP3 file into `music` directory
3. Open `all songs.txt`. It should look something like this
   ```
   1XK5-n4rR7Q     SongTitle1
   RYQUsp-jxDQ     SongTitle2
   wLBe61xINTo     SongTitle3
   ...
   ```
4. Paste name of your MP3 file on the left and desired title on the right
   > **IMPORTANT**  
   > Name of the file and title have to be separated by tabulation `\t`!
5. Now `all songs.txt` should look like this
   ```
   audio_name      custom_title
   1XK5-n4rR7Q     SongTitle1
   RYQUsp-jxDQ     SongTitle2
   wLBe61xINTo     SongTitle3
   ...
   ```
   where `audio_name` is the name of the MP3 file and `custom_title` is the song title
6. Restart Qtify

### Commercial use

As stated in the [NOTICE](NOTICE.md), Qtify is not for commercial use due to the nature of the program, specifically the use of the YouTube API with potentially copyrighted audio.

### License

Qtify is under [Apache 2.0](LICENSE.md) license and [Common Clause](NOTICE.md)
