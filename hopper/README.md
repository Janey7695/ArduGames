# JANEY_N2 - Hopper
在弹跳中向上进发，避免掉入虚空！

游戏源码取自 https://github.com/obono/ArduboyWorks/tree/master/hopper ， 感谢@obono

自己做了esp32上的移植，并添加了OTA下载更新固件功能

> 无音乐 还未移植 

## 额外外设 
- [x] AT24CXX - eeprom</br>
连接方式为 </br>
SDA -> pin_21</br>
SCL -> pin_22

## 说明
1. 在菜单选择start game开始游戏
2. 按方向键进行移动，落在方块上会被向上弹起，并获得分数
3. 可以一直按住某个方向一直移动·。
4. 不同的方块有不同的效果
5. 每满50分进入下一个难度等级

## TODO
- [x] 游戏暂停
- [ ] 编写音乐驱动