# TouhouDoom PKGBUILD
正在按照brutal-doom的PKGBUILD魔改，保证能单独文件夹保存进度（貌似GZDOOM加载了其他的WAD，原先的存档全部无法读取）  
只有地狱的鲜血才能对抗魔法少女的降妖法术:-)  
P.S 我正在考虑是否将依赖从doom2-data-steam改成freedoom  
  
Update: 打包完毕，默认为freedoom2.wad，如果有系统级安装DOOM2.WAD的话(/usr/share/doom或/usr/share/games/doom)，会使用DOOM2.WAD.  
单独文件夹保存实现，但是更换WAD后，仍然无法读取原先存档。  
理论上可以使用TNT.WAD和PLUTONIA.WAD加载touhoudoom，但是我没有实现，因为GZDOOM的存档读取。  
  
Update: 现在支持TNT和PLUTONIA了，也支持到用户目录下寻找WAD了。  
  
Trying to modify this PKGBUILD with the reference of the brutal-doom PKGBUILD, to make the progress can be saved. Since the GZDOOM cannot load the save if loaded with other WAD file.  
Only the blood of the Hell could fight with the magic girl.  
P.S I am considering whether change the dependence from doom2-data-steam to freedoom.  
  
Update: PKGBUILD completed, use freedoom2.wad by default. However, if the DOOM2.WAD had been installed universal(/usr/share/doom or /usr/share/games/doom), use DOOM2.WAD instead.  
Can save progress in a folder, however, GZDOOM still cannot read the progress one the WAD file changed.  
I considered support TNT.WAD and PLUTONIA.WAD because touhoudoom can be load with them. However I gave up because of GZDOOM's progress reading.  
  
Update：Now support TNT and PLUTONIA. And have the ability to search for wad from user's folder.  
  
I hate touhou, but who could resist the cute girls;-)  
SuperBart 2021-7-19  