# VirtualButtonToGame
解决某些游戏会屏蔽虚拟按键的问题

此版只支持64位系统。
驱动加载时，需要联网认证。

## 普通版：
	DD32.dll
	
	DD64.dll
	
## 免安装版：
	DD94687.32.dll
	
	DD94687.64.dll
	
## HID版：
	DDHID32.dll
	
	DDHID64.dll
	
32位程序调用 *.32.dll

64位程序调用 *.64.dll

以EFI方式启动的64位系统，如果无法正常加载驱动，

进入BIOS，查找“secure boot”选项，设置成“disable”，

或改以传统方式启动。


收费版通过MicroSoft官方WHQL认证。

不联网认证，不绑定机器，没有数量限制。
