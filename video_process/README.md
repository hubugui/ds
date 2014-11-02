video process
============================

# test_histogram

output yuv file's histogram data to STDOUT, you can use GNU plotting utilities's graph to display them.

## depend
`sudo apt-get install ffmpeg plotutils`

### draw yuv
`ffplay -video_size 612*816 test_612_816.yuv`

## usage
`make`

`./test_histogram.out | graph -T X`

default to read `test_612_816.yuv`, you can assign other file through the first parameter.