/*
	原逆向作者：nezza@github
	来自于：https://gist.github.com/nezza/a25bee13f25a1733a4c7a1d3d1cf5882
	
	本人将所有的十六进制转换成十进制，并重写了部分代码，并以The Unlicense授权协议发布
	详细文本可在 http://unlicense.org/ 中查看
	
	数组计数从0开始，请务必注意
	2021 SuperBart & BenderBlog
*/

undefined2 __stdcall16far check_oem_key(char *key,int len)
{
	int first_3_digits_int;		 //整型变量：前三位数字
	int second_2_digits_int;	 //整型变量：之后两位数字
	char first_three_digits[4];  //字符串：前三位数字
	char second_two_digits[3];	 //字符串：之后两位数字
	undefined2 check_result;	 //应为原程序中的结构体：是否有效

	/* 原逆向者注释：检查前五个字符，必须是数字 */
	/* 密钥长度为23 第6,10&18位为‘-’字符 */
	if ((strlen(key) == 23) && (key[5] == '-') && (key[9] == '-') && (key[17] == '-'))
	{
		/* 并且是OEM密钥格式 */
		if ( check_oem_str(3,0x11704f9d,key + 6,len) == 0 )
		{
			/* 以下代码是为了保证密钥前五个字符确实是数字字符 */
			int i;		//整型变量：循环使用的数字
			for (i = 0; i < 5; ++i)
				if (key[i] < '0' && key[i] > '9')
					return 0;
			
			/* 以下代码是将密钥前三个字符提取出来，转换为数字 */
			copy_partial(3,key,len,first_three_digits);
			first_3_digits_int = atoi(first_three_digits);
			
			/* 判断前三个数字是否在0~366的闭区间范围中，若是，对后两位代码进行同样处理 */
			if ((first_3_digits_int != 0) && (first_3_digits_int < 367))
			{
				copy_partial(2,key + 3,len,second_two_digits);
				second_2_digits_int = atoi(second_two_digits);
				
				/* 判断后两个数字不在3~94的闭区间范围内，也就是 */
				/* 判断第11位是0，第17位是在0~8的开区间内 */
				if ((second_2_digits_int < 3) || (94 < second_2_digits_int))
				{
					if ((key[10] == '0') && ('0' < key[16]) && (key[16] < '8'))
					{
						/* 保证后面五位全都是数字字符，只要是数字就行 */
						for (i = 18; i < 23; ++i)
							if ((key[i] < '0') && (key[i] > '9'))
								return 0;
						
						/* 现在只要对中间的七位进行相加，并除以7取余  */
						/* 详情请看视频https://www.bilibili.com/video/BV1Kp4y1p7LF ，空降 05:08 */
						if (i == 22)
						{
							check_result = mod7_check(key + 10,len);
							return check_result;
						}
					}
				}
			}
		}
	}
}