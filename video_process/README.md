# test_histogram

output yuv file's histogram data to STDOUT, you can use GNU plotting utilities's graph to display them.

## depend
`sudo apt-get install ffmpeg plotutils nodejs`

## usage
`make`

`./test_histogram.out | graph -T X`

default to read `test_612_816.yuv`, you can assign other file through the first parameter.

## convert jpg to yuv
`ffmpeg -i 330px-Image_processing_pre_otsus_algorithm.jpg -s 330x248 -pix_fmt yuv420p 330px-Image_processing_pre_otsus_algorithm.yuv`

## how to play yuv-I420?
`ffplay -video_size 612*816 test_612_816.yuv`

# black_white

binary yuv image

## how to test new jpg
`ffmpeg -i test2.jpg -s 2448*3264 -pix_fmt yuv420p test2.yuv`

`ffplay -video_size 2448*3264 test2.yuv`

`./black_white.out test2.yuv 2448 3264`

`ffplay -video_size 2448*3264 test2_bw.yuv`

## otsu.js
`nodejs otsu.js`

JavaScript implementation, copy from [Otsu](http://en.wikipedia.org/wiki/Otsu's_method)

histogram data come from '330px-Image_processing_pre_otsus_algorithm.yuv'