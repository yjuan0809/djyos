/*
 * pwd.c
 *
 *  Created on: 2015年10月16日
 *      Author: zqf
 */

#include <pwd.h>
//
//--------------------------------------------------------------------------------
//
//当您需要取得有关某个使用者的资讯时，大致上有以下几个函数可以使用：
//
//--------------------------------------------------------------------------------

//当您知道使用者的uid(user id)时，可以透过getpwuid来得知所有关於该使用者的相关资讯。
struct passwd * getpwuid(uid_t uid)
{
	return NULL;
}



//--------------------------------------------------------------------------------
//当您知道使用者名称时，可以透过getpwnam来得知所有关於该使用者的相关资讯。

struct passwd * getpwnam(char * name)
{
	return NULL;
}



//--------------------------------------------------------------------------------
//当您仅需要取得使用者的密码进行比对时，可以使用getpw。

int getpw(uid_t uid, char *buf)
{
	return 0;
}



//--------------------------------------------------------------------------------

//另外，有存取一系列使用者资讯的方法。


//--------------------------------------------------------------------------------
//开启password档案。

FILE * pwdopen(void)
{
	return NULL;
}



//--------------------------------------------------------------------------------
//读取一个使用者资讯进来，填到p中，返回p为成功，NULL为失败。

struct passwd * pwdread(FILE * stream,struct passwd *p)
{
	return NULL	;
}



//--------------------------------------------------------------------------------
//将读取资料流重设到起点。

void setpwent(void)
{

}



//--------------------------------------------------------------------------------
//关闭password档案资料流。

void endpwent(void)
{

}



//--------------------------------------------------------------------------------
//读取一个使用者资讯进来，有必要的话，则将进行开档动作。

struct passwd * getpwent(void)
{
	return NULL;
}



//--------------------------------------------------------------------------------
//从档案中读取一个使用者资讯进来。

struct passwd * fgetpwent(FILE * stream)
{
	return NULL;
}



//--------------------------------------------------------------------------------
//将一个使用者资讯写入档案中。

int putpwent(struct passwd *p,FILE *f)
{
	return 0;
}



//--------------------------------------------------------------------------------
//配置一个记忆体区块给passwd用。

struct passwd * pwdalloc(void)
{
	return NULL;
}
