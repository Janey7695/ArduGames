# ArduGames

## 使用
里面是一些运行在esp32平台上的基于`arduboy2`库的小游戏。其中的`arduboy2`库,已经移植到esp32上，可以直接在esp32对应的平台进行编译。

### 接线(esp32)
`↑` -> IO 27 </br>
`↓` -> IO 26 </br>
`←` -> IO 25 </br>
`→` -> IO 33 </br>
`A` -> IO 12 </br>
`B` -> IO 14 </br>

`oled-D0` -> IO 18 </br>
`oled-D1` -> IO 23 </br>
`oled-DC` -> IO 2 </br>
`oled-CS` -> IO 15 </br>
`oled-RES` -> IO 4 </br>
## 下载
每个游戏有其单独的readme文件，进入相应文件夹查看并下载源文件。

## 注意
我的开发平台是platformIO，文件夹里面只有`src`是主要的逻辑部分。如果你要将游戏移植回正经`arduino`上,只需要在Arduino上下载`lib`中对应的包，然后在src中将`main.cpp`改为`main.ino`即可。

## 已有游戏~

### JANEY_N1 - FlappyBird
尝试在管道中穿梭，别磕到头！ - 仿制FLAPPYBIRD