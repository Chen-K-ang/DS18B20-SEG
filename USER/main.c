#include "public.h"
#include "smg.h"
#include "ds18b20.h"

//�̵���IO
sbit Relay = P1^4;

#define TEMP_LIMIT      28.0f      //�¶ȸ��ڴ�ֵ��̵�������

void main()
{	
	u8 i = 0;
   	int temp_value;
	float temp;
	u8 temp_buf[5];

	ds18b20_init();//��ʼ��DS18B20
	while(1)
	{				
		i++;
		if (i % 50 == 0) {//���һ��ʱ���ȡ�¶�ֵ�����ʱ��Ҫ�����¶ȴ�����ת���¶�ʱ��
			temp = ds18b20_read_temperture();
			if (temp > TEMP_LIMIT) {
				Relay = 0;//�̵�������	
			} else {
				Relay = 1;//�̵����Ͽ�
			}
			temp_value = temp * 10;//�����¶�ֵС����һλ
		}
		if (temp_value < 0) {//���¶�
		
			temp_value=-temp_value;
			temp_buf[0]=0x40;//��ʾ����	
		} else
			temp_buf[0]=0x00;//����ʾ
		temp_buf[1] = gsmg_code[temp_value / 1000];//��λ
		temp_buf[2] = gsmg_code[temp_value % 1000 / 100];//ʮλ
		temp_buf[3] = gsmg_code[temp_value % 1000 % 100 / 10] | 0x80;//��λ+С����
		temp_buf[4] = gsmg_code[temp_value % 1000 % 100 % 10];//С�����һλ
		smg_display(temp_buf, 4);
	}
}
