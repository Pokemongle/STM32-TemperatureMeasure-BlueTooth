CMSIS是系统启动文件（不用管）；
FWLib是标准库函数（不用管）；
MY是自己写的.c和.h，里面除了inc以外装的是和文件名对应的外设的.c文件，inc里面装的是所有外设的头文件；
OBJ里面装的是.hex文件；
USER里面是工程文件，每个文件夹里面是对应名称的实验的main.c文件
	大作业对应的main.c在demo/USER/finalproj 里面

使用之前要对Target1进行路径配置，勾选UseMicroLib等。