ffmpeg -i input.mp4 -vf scale=1920:1080 -c:a copy output.mp4
ffmpeg -i 入力ファイル名 -vf transpose=1 -metadata:s:v:0 rotate=0 出力ファイル名