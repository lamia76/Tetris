#include"block.h"
#include <cstdlib>
#include <cstring>
void block::InitateBlock()//初始化方块信息 
{
	Block_form = rand() % 19;
	Block_color = rand() % 7;
	speed = 1;
}
void block::BuildBlock()//生成方块
{
	switch(Block_form)
	{
		case 0: memcpy(Block_,Block_1form_1,8*sizeof(int));break;
		case 1: memcpy(Block_,Block_2form_1,8*sizeof(int));break;
		case 2: memcpy(Block_,Block_2form_2,8*sizeof(int));break;
		case 3: memcpy(Block_,Block_2form_3,8*sizeof(int));break;
		case 4: memcpy(Block_,Block_2form_4,8*sizeof(int));break;
		case 5: memcpy(Block_,Block_3form_1,8*sizeof(int));break;
		case 6: memcpy(Block_,Block_3form_2,8*sizeof(int));break;
		case 7: memcpy(Block_,Block_3form_3,8*sizeof(int));break;
		case 8: memcpy(Block_,Block_3form_4,8*sizeof(int));break;
		case 9: memcpy(Block_,Block_4form_1,8*sizeof(int));break;
		case 10: memcpy(Block_,Block_4form_2,8*sizeof(int));break;
		case 11: memcpy(Block_,Block_4form_3,8*sizeof(int));break;
		case 12: memcpy(Block_,Block_4form_4,8*sizeof(int));break;
		case 13: memcpy(Block_,Block_5form_1,8*sizeof(int));break;
		case 14: memcpy(Block_,Block_5form_2,8*sizeof(int));break;
		case 15: memcpy(Block_,Block_6form_1,8*sizeof(int));break;
		case 16: memcpy(Block_,Block_6form_2,8*sizeof(int));break;
		case 17: memcpy(Block_,Block_7form_1,8*sizeof(int));break;
		case 18: memcpy(Block_,Block_7form_2,8*sizeof(int));break;
	}
	
}
void block::cunfang()
{
	memcpy(Block_next,Block_,8*sizeof(int));
}
void block::start()
{
	memcpy(Block_now,Block_next,8*sizeof(int));
	for(int i=0;i<4;i++) {map[Block_now[2*i+1]][Block_now[2*i]]=1;}//下落中在地图表示为1 
}
void block::TurnBlock()//方块转变方向 
{
	switch(Block_form)
	{
		case 0: memcpy(Block_now,Block_1form_1,8*sizeof(int));break;
		case 1: memcpy(Block_now,Block_2form_2,8*sizeof(int));break;
		case 2: memcpy(Block_now,Block_2form_3,8*sizeof(int));break;
		case 3: memcpy(Block_now,Block_2form_4,8*sizeof(int));break;
		case 4: memcpy(Block_now,Block_2form_1,8*sizeof(int));break;
		case 5: memcpy(Block_now,Block_3form_2,8*sizeof(int));break;
		case 6: memcpy(Block_now,Block_3form_3,8*sizeof(int));break;
		case 7: memcpy(Block_now,Block_3form_4,8*sizeof(int));break;
		case 8: memcpy(Block_now,Block_3form_1,8*sizeof(int));break;
		case 9: memcpy(Block_now,Block_4form_2,8*sizeof(int));break;
		case 10: memcpy(Block_now,Block_4form_3,8*sizeof(int));break;
		case 11: memcpy(Block_now,Block_4form_4,8*sizeof(int));break;
		case 12: memcpy(Block_now,Block_4form_1,8*sizeof(int));break;
		case 13: memcpy(Block_now,Block_5form_2,8*sizeof(int));break;
		case 14: memcpy(Block_now,Block_5form_1,8*sizeof(int));break;
		case 15: memcpy(Block_now,Block_6form_2,8*sizeof(int));break;
		case 16: memcpy(Block_now,Block_6form_1,8*sizeof(int));break;
		case 17: memcpy(Block_now,Block_7form_2,8*sizeof(int));break;
		case 18: memcpy(Block_now,Block_7form_1,8*sizeof(int));break;
	}
	for(int i=0;i<4;i++) {map[Block_now[2*i+1]+y][Block_now[2*i]+x]=1;}
}
void block::MoveBlock_left()
{
	for(int i=0;i<4;i++)
	Block_now[2*i]--;
	x++;
}
void block::MoveBlock_right()
{
	for(int i=0;i<4;i++)
	Block_now[2*i]++;
	x++;
}
void block::Speed_up()
{
	for(int i=0;i<4;i++)
	Block_now[2*i+1]++;
	y++;
}void block::DownBlock()
{
	for(int i=0;i<4;i++)
	Block_now[2*i+1]+speed;
	y+=speed;
}
