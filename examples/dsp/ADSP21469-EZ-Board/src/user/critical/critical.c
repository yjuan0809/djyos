//----------------------------------------------------
//Copyright (C), 2004-2009,  lst.
//��Ȩ���� (C), 2004-2009,   lst.
//����ģ��:��ȫ����
//���ߣ�lst
//�汾��V1.0.0
//�ļ�����:��ȫ�����Ǳ����ڿ����󾡿��ܿ��ִ�еĲ��ִ���
//����˵��:
//�޶���ʷ:
//2. ...
//1. ����: 2009-01-04
//   ����: lst
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
//------------------------------------------------------
#include "os_inc.h"
#include "cpu_peri.h"

//----����ȫ��IO��--------------------------------------------------------------
//���ܣ���������⣬ȫ�����óɳ�ʼ̬�������ܿ�����Ӧ�Ĺ���ģ�����ж��塣
//��������
//���أ���
//------------------------------------------------------------------------------
void gpio_init(void)
{
}

void critical(void)
{
    gpio_init();        //������ִ��,��ΪӲ���ĳ�ʼ״̬���ܹغ���ȫ
}

