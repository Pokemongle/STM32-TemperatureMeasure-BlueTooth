# Summary
We connect an STM32 development board with a cellphone(android system) by bluetooth module.
STM32 for temperature detection
Mobile phone for displaying data in app we made.
## Cover and animation
![image.png](https://pokemongle-images-1319763739.cos.ap-nanjing.myqcloud.com/sandox/img/202309141029145.png)

## Bluetooth connection
![image.png](https://pokemongle-images-1319763739.cos.ap-nanjing.myqcloud.com/sandox/img/202309141032641.png)

## Control led and beep
Through bluetooth connection, we can control the led light on the board to be lighten or off, and turn on/ off the beep for alert.
If the current temperature is higher than the threshold value set by the left and right arrow, the beep will ring.

![image.png](https://pokemongle-images-1319763739.cos.ap-nanjing.myqcloud.com/sandox/img/202309141033639.png)

## Temperature measurement
We can also view the change of the temperature in the past 5 minutes.
![image.png](https://pokemongle-images-1319763739.cos.ap-nanjing.myqcloud.com/sandox/img/202309141034999.png)


CMSIS是系统启动文件（不用管）；
FWLib是标准库函数（不用管）；
MY是自己写的.c和.h，里面除了inc以外装的是和文件名对应的外设的.c文件，inc里面装的是所有外设的头文件；
OBJ里面装的是.hex文件；
USER里面是工程文件，每个文件夹里面是对应名称的实验的main.c文件
	大作业对应的main.c在demo/USER/finalproj 里面
	包含中断函数所在文件stm32f10x_it.c
使用之前要对Target1进行路径配置，勾选UseMicroLib等。
