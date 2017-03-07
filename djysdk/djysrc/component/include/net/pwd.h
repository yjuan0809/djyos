/*
 * pwd.h
 *
 *  Created on: 2015��10��16��
 *      Author: zqf
 */

#ifndef PWD_H_
#define PWD_H_

#include <stdint.h>
#include <stdio.h>

#include <sys/types.h>

struct passwd
{
    char * pw_name; /* Username, POSIX.1 */
    char * pw_passwd; /* Password */
    __uid_t pw_uid; /* User ID, POSIX.1 */
    __gid_t pw_gid; /* Group ID, POSIX.1 */
    char * pw_gecos; /* Real Name or Comment field */
    char * pw_dir; /* Home directory, POSIX.1 */
    char * pw_shell; /* Shell Program, POSIX.1 */
};

//
//--------------------------------------------------------------------------------
//
//������Ҫȡ���й�ĳ��ʹ���ߵ���Ѷʱ�������������¼�����������ʹ�ã�
//
//--------------------------------------------------------------------------------

struct passwd * getpwuid(uid_t uid);
//����֪��ʹ���ߵ�uid(user id)ʱ������͸��getpwuid����֪���й�춸�ʹ���ߵ������Ѷ��



//--------------------------------------------------------------------------------

struct passwd * getpwnam(char * name);
//����֪��ʹ��������ʱ������͸��getpwnam����֪���й�춸�ʹ���ߵ������Ѷ��



//--------------------------------------------------------------------------------

int getpw(uid_t uid, char *buf);
//��������Ҫȡ��ʹ���ߵ�������бȶ�ʱ������ʹ��getpw��



//--------------------------------------------------------------------------------

//���⣬�д�ȡһϵ��ʹ������Ѷ�ķ�����


//--------------------------------------------------------------------------------

FILE * pwdopen(void);
//����password������



//--------------------------------------------------------------------------------

struct passwd * pwdread(FILE * stream,struct passwd *p);
//��ȡһ��ʹ������Ѷ�������p�У�����pΪ�ɹ���NULLΪʧ�ܡ�



//--------------------------------------------------------------------------------

void setpwent(void);
//����ȡ���������赽��㡣



//--------------------------------------------------------------------------------

void endpwent(void);
//�ر�password������������



//--------------------------------------------------------------------------------

struct passwd * getpwent(void);
//��ȡһ��ʹ������Ѷ�������б�Ҫ�Ļ����򽫽��п���������



//--------------------------------------------------------------------------------

struct passwd * fgetpwent(FILE * stream);
//�ӵ����ж�ȡһ��ʹ������Ѷ������



//--------------------------------------------------------------------------------

int putpwent(struct passwd *p,FILE *f);
//��һ��ʹ������Ѷд�뵵���С�



//--------------------------------------------------------------------------------

struct passwd * pwdalloc(void);
//����һ�������������passwd�á�

#endif /* PWD_H_ */