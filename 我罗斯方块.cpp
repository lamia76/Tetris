#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<time.h>
#include<windows.h>
#define heitht 31//长度大于实际显示一格 用于作出界结束游戏判定 
#define width 15
#define fall_time 800
using namespace std;
int map[140][35]={0};
long int last = 800;
clock_t start;
int game_over=1;
int key;
HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);
void clear_flash()
{   
    //清除光标 
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(hdl, &CursorInfo);//获取控制台光标信息
    CursorInfo.bVisible = false; //隐藏控制台光标
    SetConsoleCursorInfo(hdl, &CursorInfo);//设置控制台光标状态
}
void gotoxy(int x,int y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(hdl,pos);
}

class block{
	public:
		void InitateBlock();//初始化方块信息 
		void BuildBlock();//生成方块
		void TurnBlock();//方块转变方向 
		void MoveBlock_left();//方块左移 
		void MoveBlock_right();//方块右动 
		void DownBlock();//方块下落 
		void Speed_up();//方块加速 
		void b_start();//方块开始下落 
		void cunfang();//把生成的方块放到方框中，作为下一个方块用 
		block(int a)
		{
			player=a;
		}
	protected:
		int	Block_1form_1[8]={1,0,1,1,2,0,2,1};//分为4行4列，左行右列；
		int	Block_2form_1[8]={1,1,2,1,2,2,2,3};//11 21 22 23
		int	Block_2form_2[8]={1,1,1,2,2,1,3,1};//
		int	Block_2form_3[8]={1,2,2,0,2,1,2,2};//
		int	Block_2form_4[8]={3,1,3,2,2,2,1,2};//	 
		int	Block_3form_1[8]={0,2,1,0,1,1,1,2};//02 10 11 12
		int	Block_3form_2[8]={0,1,1,1,2,1,2,2};//
		int	Block_3form_3[8]={1,1,2,1,2,2,2,3};//
		int	Block_3form_4[8]={1,1,1,2,2,2,3,2};//
		int	Block_4form_1[8]={1,1,2,0,2,1,2,2};//11 20 21 22
		int	Block_4form_2[8]={1,1,2,1,3,1,2,2};//
		int	Block_4form_3[8]={2,0,2,1,2,2,3,1};//
		int	Block_4form_4[8]={1,1,2,1,3,1,2,0};//11 21 31 20
		int	Block_5form_1[8]={2,0,2,1,1,1,1,2};//20 21 11 12
		int	Block_5form_2[8]={0,0,1,0,1,1,2,1};//
		int	Block_6form_1[8]={0,1,0,2,1,0,1,1};//01 02 10 11
		int	Block_6form_2[8]={0,1,1,1,2,0,1,0};//01 11 20 10
		int	Block_7form_1[8]={1,0,1,1,1,2,1,3};//10 11 12 13
		int	Block_7form_2[8]={0,1,1,1,2,1,3,1};//
		int Block_color;//方块颜色 
		int Block_form;//方块形状 
		int Block_[8];//初始化后的方块 
		int Block_now[8];//现在的方块
		int Block_next[8];//下一个的方块
		int speed;//方块下落速度 
		int player;
		int x,y;
};
void block::InitateBlock()//初始化方块信息 
{
	srand((unsigned int)time(NULL));
	Block_form = rand() % 19;
	Block_color = rand() % 7;
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
	if(player==1)
	{
		for(int i=5;i<16;i++)
		for(int j=12;j<18;j++)
		map[i][j]=0;
	}
	if(player==2)
	{
		for(int i=115;i<126;i++)
		for(int j=12;j<18;j++)
		map[i][j]=0;
	}
	memcpy(Block_next,Block_,8*sizeof(int));
	if(player==1)
	for(int i=0;i<4;i++) {map[5+2*Block_next[2*i]][12+Block_next[2*i+1]]=1;}
	if(player==2)
	for(int i=0;i<4;i++) {map[115+2*Block_next[2*i]][12+Block_next[2*i+1]]=1;}
}
void block::b_start()
{
	int t=2*(rand() % 12)+1;
	if(player==1)
	{
		x=20+t;
		y=6;
		memcpy(Block_now,Block_,8*sizeof(int));
		for(int i=0;i<4;i++) {map[x+2*Block_now[2*i]][y+Block_now[2*i+1]]=1;}//下落中在地图表示为1
	}
	if(player==2)
	{
		x=80+t;
		y=6;
		memcpy(Block_now,Block_,8*sizeof(int));
		for(int i=0;i<4;i++) {map[x+2*Block_now[2*i]][y+Block_now[2*i+1]]=1;}//下落中在地图表示为1
	} 
}
void block::TurnBlock()//方块转变方向 
{
	for(int i=0;i<4;i++) {map[2*Block_now[2*i]+x][Block_now[2*i+1]+y]=0;}
	switch(Block_form)
	{
		case 0: memcpy(Block_now,Block_1form_1,8*sizeof(int));Block_form=0;break;
		case 1: memcpy(Block_now,Block_2form_2,8*sizeof(int));Block_form=2;break;
		case 2: memcpy(Block_now,Block_2form_3,8*sizeof(int));Block_form=3;break;
		case 3: memcpy(Block_now,Block_2form_4,8*sizeof(int));Block_form=4;break;
		case 4: memcpy(Block_now,Block_2form_1,8*sizeof(int));Block_form=1;break;
		case 5: memcpy(Block_now,Block_3form_2,8*sizeof(int));Block_form=6;break;
		case 6: memcpy(Block_now,Block_3form_3,8*sizeof(int));Block_form=7;break;
		case 7: memcpy(Block_now,Block_3form_4,8*sizeof(int));Block_form=8;break;
		case 8: memcpy(Block_now,Block_3form_1,8*sizeof(int));Block_form=5;break;
		case 9: memcpy(Block_now,Block_4form_2,8*sizeof(int));Block_form=10;break;
		case 10: memcpy(Block_now,Block_4form_3,8*sizeof(int));Block_form=11;break;
		case 11: memcpy(Block_now,Block_4form_4,8*sizeof(int));Block_form=12;break;
		case 12: memcpy(Block_now,Block_4form_1,8*sizeof(int));Block_form=9;break;
		case 13: memcpy(Block_now,Block_5form_2,8*sizeof(int));Block_form=14;break;
		case 14: memcpy(Block_now,Block_5form_1,8*sizeof(int));Block_form=13;break;
		case 15: memcpy(Block_now,Block_6form_2,8*sizeof(int));Block_form=16;break;
		case 16: memcpy(Block_now,Block_6form_1,8*sizeof(int));Block_form=15;break;
		case 17: memcpy(Block_now,Block_7form_2,8*sizeof(int));Block_form=18;break;
		case 18: memcpy(Block_now,Block_7form_1,8*sizeof(int));Block_form=17;break;
	}
	for(int i=0;i<4;i++) {map[2*Block_now[2*i]+x][Block_now[2*i+1]+y]=1;}
}
void block::MoveBlock_left()
{
	for(int i=0;i<4;i++) {map[x+2*Block_now[2*i]][y+Block_now[2*i+1]]=0;}
	x-=2;
	for(int i=0;i<4;i++) {map[x+2*Block_now[2*i]][y+Block_now[2*i+1]]=1;}
}
void block::MoveBlock_right()
{
	for(int i=0;i<4;i++) {map[x+2*Block_now[2*i]][y+Block_now[2*i+1]]=0;}
	x+=2;
	for(int i=0;i<4;i++) {map[x+2*Block_now[2*i]][y+Block_now[2*i+1]]=1;}
}
void block::Speed_up()
{
	for(int i=0;i<4;i++) {map[x+2*Block_now[2*i]][y+Block_now[2*i+1]]=0;}
	y++;
	for(int i=0;i<4;i++) {map[x+2*Block_now[2*i]][y+Block_now[2*i+1]]=1;}
}
void block::DownBlock()
{
	for(int i=0;i<4;i++) {map[x+2*Block_now[2*i]][y+Block_now[2*i+1]]=0;}
	y++;
	for(int i=0;i<4;i++) {map[x+2*Block_now[2*i]][y+Block_now[2*i+1]]=1;}
}

block Block1(1);
block Block2(2);

class render{
	public:
		void grade();//显示分数
		void time_show();//显示时间 
		void draw_main_screen();//绘制主界面
		void draw_option();//绘制游戏设置画面
		void draw_kong();//绘制方块
		void screen_refresh();//刷新屏幕显示 
	private: 
};


void render::draw_option()//绘制游戏设置画面
{
	system("mode con cols=120 lines=40");
	SetConsoleTitle("Welcome To 我罗斯方块");
	SetConsoleTextAttribute(hdl,0x3);
	for(int i=25;i<=90;i+=2)
	{
		gotoxy(i,1);
		cout<<"*";
		gotoxy(i,30);
		cout<<"*";
	}
	for(int i=1;i<=30;i++)
	{
		gotoxy(25,i);
		cout<<"*";
		gotoxy(90,i);
		cout<<"*";
	}
	SetConsoleTextAttribute(hdl,0x3);
    gotoxy(53,5);
    cout<<"我罗斯方块"<<endl;
    gotoxy(54,8);
    cout<<"操作方法"<<endl;
    gotoxy(53,10);
    cout<<"W/↑:转向";
    gotoxy(53,12);
    cout<<"S/↓:加速";
    gotoxy(53,14);
    cout<<"A/←:左移";
    gotoxy(53,16);
    cout<<"D/←:右移";
    gotoxy(50,19);
    cout<<"按任意键进入游戏";
    gotoxy(51,22);
    cout<<"按P键暂停游戏";
    gotoxy(40,25);
    cout<<"部分系统用户请先按下shift键关闭输入法";
    gotoxy(48,28);
    cout<<"By 侯钦凯 AND 卢浩玮";
    SetConsoleTextAttribute(hdl,0x07);
    gotoxy(1,30);
}
void render::draw_main_screen()
{
	system("mode con cols=160 lines=40");
	SetConsoleTitle("我罗斯方块");
	SetConsoleTextAttribute(hdl,0x3);
	gotoxy(20,3);
	cout<<"Player1";
	gotoxy(6,8);
	cout<<"SCORE:0 "; 
	gotoxy(5,10);
	cout<<"下一个方块";
	for(int i=4;i<=16;i+=2)
	{
		gotoxy(i,11);
		cout<<"*";
		gotoxy(i,18);
		cout<<"*";
	}
	for(int i=11;i<=18;i++)
	{
		gotoxy(4,i);
		cout<<"*";
		gotoxy(16,i);
		cout<<"*" ;
	}
	for(int i=20;i<=51;i+=2)
	{
		gotoxy(i,5);
		cout<<"*";
		gotoxy(i,30);
		cout<<"*";
		map[i][5]=3;
		map[i][30]=3;
		map[i+1][5]=3;
		map[i+1][30]=3;
	}
	for(int i=5;i<=30;i++)
	{
		gotoxy(20,i);
		cout<<"*";
		gotoxy(51,i);
		cout<<"*";
		map[20][i]=3;
		map[51][i]=3;
	}
	gotoxy(80,3);
	cout<<"Player2"; 
	gotoxy(116,8);
	cout<<"SCORE: 0"; 
	gotoxy(115,10);
	cout<<"下一个方块"; 
	for(int i=114;i<=126;i+=2)
	{
		gotoxy(i,11);
		cout<<"*";
		gotoxy(i,18);
		cout<<"*";
	}
	for(int i=11;i<=18;i++)
	{
		gotoxy(114,i);
		cout<<"*";
		gotoxy(126,i);
		cout<<"*" ;
	}
	for(int i=80;i<=111;i+=2)
	{
		gotoxy(i,5);
		cout<<"*";
		gotoxy(i,30);
		cout<<"*";
		map[i][5]=3;
		map[i][30]=3;
		map[i+1][5]=3;
		map[i+1][30]=3;
	}
	for(int i=5;i<=30;i++)
	{
		gotoxy(80,i);
		cout<<"*";
		gotoxy(111,i);
		cout<<"*";
		map[80][i]=3;
		map[111][i]=3;
	}
	gotoxy(130,35);
	cout<<"By 侯钦凯 AND 卢浩玮";
	SetConsoleTextAttribute(hdl,0x3);
    SetConsoleTextAttribute(hdl,0x07);
    gotoxy(1,35);
    CONSOLE_CURSOR_INFO cursorInfo = {1, FALSE};
    SetConsoleCursorInfo(hdl, &cursorInfo);
}
void render::screen_refresh()
{
    SetConsoleTextAttribute(hdl, 0x00);
    for(int i=21;i<51;i++)
    for(int j=6;j<30;j++)
    {
    	gotoxy(i,j);
    	cout<<" ";
	}
    for(int i=81;i<111;i++)
    for(int j=6;j<30;j++)
    {
    	gotoxy(i,j);
    	cout<<" ";
	}
}
void render::draw_kong()
{
	SetConsoleTextAttribute(hdl,0x04);
    for(int i=21;i<51;i+=2)
    for(int j=6;j<30;j++)
    {
    	if(map[i][j]==1)
    	{
    		gotoxy(i,j);
    		cout<<"■";
		}
	}
	SetConsoleTextAttribute(hdl,0x04);
	for(int i=81;i<111;i+=2)
    for(int j=6;j<30;j++)
    {
    	if(map[i][j]==1)
    	{
    		gotoxy(i,j);
    		cout<<"■";
		}
	}
	SetConsoleTextAttribute(hdl,0x3);
	for(int i=0;i<112;i+=2)
	for(int j=1;j<36;j++)
	{
		if(map[i][j]==3)
    	{
    		gotoxy(i,j);
    		cout<<"*";
		}
	}
	SetConsoleTextAttribute(hdl,0x3);
	for(int i=21;i<140;i++)
	for(int j=6;j<30;j++)
	{
		if(map[i][j]==2)
    	{
    		gotoxy(i,j);
    		cout<<"■";
		}
	}
}
class game{
	public:
		int try_generate();//生成新方块前扫描地图判定是否有玩家game over 
	    void try_movedown();//下落碰撞判定
	    void over(int f1,int f2);//游戏结束
	    void clear_block1();
	    void clear_block2();
	    void keyboard_hit();
	    bool if_over();
	    void shengchenghang(int n);
	    void pengzhuang(int key);
	private:	
        int socre1;
        int score2;
}; 


long int socre1=0;
long int score2=0;
void game::keyboard_hit()
{
while(_kbhit())
{
	key=_getch();
	switch(key)
  { 
    case 'A':case'a':
	Block1.MoveBlock_left();break; 
	 case 'W':case'w':
	Block1.TurnBlock();break; 
	 case 'S':case's':
    Block1.DownBlock();break; 
	 case 'D':case'd':
	Block1.MoveBlock_right();break;
	 case 'P':case'p':
	gotoxy(63,15);cout<<"已暂停";_getch();break;
	case 0xE0:
 	{
	switch(key=_getch())
	   {
	 case 72:
	Block2.TurnBlock();break; 
	 case 80:
	Block2.DownBlock();break; 
	 case 75:
	Block2.MoveBlock_left();break; 
	 case 77:
	Block2.MoveBlock_right();break;
       }
     }
  }
 pengzhuang(key);
}
}
void game::pengzhuang(int key)
{ 
	if(key=='A'||key=='a')
	{
		for(int i=5;i<=30;i++)
		{
			if(map[19][i]==1)
			{
				map[19][i]=0;
				Block1.MoveBlock_right();
				break;
			}
		}
	}
	else if(key=='D'||key=='d')
	{
		for(int i=5;i<=30;i++)
		{
			if(map[51][i]==1)
			{
				map[51][i]=3; 
				Block1.MoveBlock_left();
				break;
			}
		}
	}
	else if(key=='W'||key=='w')
	{
		for(int i=5;i<=30;i++)
		{
			if(map[19][i]==1||map[51][i]==1)
			{
				map[19][i]=0;
				map[51][i]=3; 
				for(int t=0;t<3;t++)
				Block1.TurnBlock();
				break;
			}
		}
	}
	else if(key==75)
	{
		for(int i=5;i<=30;i++)
		{
			if(map[79][i]==1)
			{
				map[79][i]=0; 
				Block2.MoveBlock_right();
				break;
			}
		}
	}
	else if(key==77)
	{
		for(int i=5;i<=30;i++)
		{
			if(map[111][i]==1)
			{
				map[111][i]=3; 
				Block2.MoveBlock_left();
				break;
			}
		}
	}
	else if(key==80)
	{
		for(int i=5;i<=30;i++)
		{
			if(map[79][i]==1||map[111][i]==1)
			{
				map[79][i]=0;
				map[111][i]=3;
				for(int t=0;t<3;t++)
				Block1.TurnBlock();
				break;
			}
		}
	}

 } 
void game::try_movedown()//下落碰撞判定
{
	int f1=0,f2=0;
	for(int i=21;i<51&&f1!=1;i++)
	for(int j=6;j<30&&f1!=1;j++)
	{ 
		if(map[i][j]==1&&(map[i][j+1]==2||map[i][j+1]==3))
		{
			for(int k=21;k<51;k++)
			for(int t=6;t<30;t++)
			{
				if(map[k][t]==1)
				{
					map[k][t]=2;
				}
			}
			Block1.InitateBlock();
			Block1.BuildBlock();
			Block1.b_start();
			f1=1;
		}
	}
	for(int i=81;i<111&&f2!=1;i++)
	for(int j=6;j<30&&f2!=1;j++)
	{
		if(map[i][j]==1&&(map[i][j+1]==2||map[i][j+1]==3))
		{
			for(int k=81;k<111;k++)
			for(int t=6;t<30;t++)
			{
				if(map[k][t]==1)
				{
					map[k][t]=2;
				}
			}
			Block2.InitateBlock();
			Block2.BuildBlock();
			Block2.b_start();
			f2=1;
		}
	}
}

void game::clear_block1()//player1消行判定 
{
	int flag;
	for (int j = 29;j>5;j--)
	{
	    flag = 1;
		for(int i=21;i<51;i+=2)
		{
			if(map[i][j]==0)
			flag=0;
		}
		if(flag!=0)
		{
			for(int i=11;i<51;i+=2)
			{
				map[i][j]=0;
			}
		    for(int k=j;k>6;k--)
		    {
				for(int t=21;t<51;t++)
				{
				    map[t][k]=map[t][k-1];
				}
		    }
			j++;
			shengchenghang(2);
		}
	}
}
void game::clear_block2()//player2消行判定 
{
	int flag;
	for (int j = 29;j>5;j--)
	{
	    flag = 1;
		for(int i=81;i<111;i+=2)
		{
			if(map[i][j]==0)
			flag=0;
		}
		if(flag!=0)
		{
			for(int i=81;i<111;i+=2)
			{
				map[i][j]=0;
			}
		    for(int k=j;k>6;k--)
		    {
				for(int t=81;t<111;t++)
				{
				    map[t][k]=map[t][k-1];
				}
		    }
			j++;
			shengchenghang(1);
		}
	}
}
void game::shengchenghang(int n)
{
	int f=0;
	if(n==1)
	{
		for(int j=7;j<30;j++)
		for(int i=21;i<51;i+=2)
		{
			map[i][j-1]=map[i][j];//从上往下找已下落的方块，如果找到就把从最底层的所有方块上移一层。 
		}
			for(int t=21;t<51;t+=2)
			{
				int r=rand()%2;
				if(r==1)
				map[t][29]=2;//把最后一行随机生成方块 
			}
	}
	if(n==2)
	{
		for(int j=7;j<30;j++)
		for(int i=81;i<111;i+=2)
		{
			map[i][j-1]=map[i][j];//从上往下找已下落的方块，如果找到就把从最底层的所有方块上移一层。 
		}
			for(int t=81;t<111;t+=2)
			{
				int r=rand()%2;
				if(r==1)
				map[t][29]=2;//把最后一行随机生成方块 
			}
	}
}

bool game::if_over()//产生新方块前先对地图进行扫描，判定是否有人出局 
 {    
 	for(int i=21;i<51;i++)
	{  
		if(map[i][6]==2)
		{
		over(0,1);
		game_over= 0; 
		break;
		}
	}	
	for(int i=81;i<111;i++)
	{
		if(map[i][6]==2)
		{
		over(1,0);
		game_over= 0;
		break;
		}
	}
    if(game_over==1)
	return true;
	else if(game_over==0)
	return false;
 }
void game::over(int f1,int f2)
{
	if(f1)
	{    
		gotoxy(59,13);
		printf("Player1 Win!");
		gotoxy(59,20);
		printf("Player2 Lose...");
	}
	if(f2)
	{
		gotoxy(59,13);
		printf("Player2 Win!");
		gotoxy(59,20);
		printf("Player1 Lose...");
	}
}

game G;
render R;
int main()
{
	srand((unsigned int)time(NULL));
	R.draw_option();
	key=_getch();
	R.draw_main_screen();
	Block1.InitateBlock();
	Block2.InitateBlock();
	Block1.BuildBlock();
	Block2.BuildBlock();
	Block1.cunfang();
	Block2.cunfang();
	Block1.b_start();
	Block2.b_start();
	while(1)
	{
		if(G.if_over())//如果没有结束游戏 
		{
			G.try_movedown();
			start = clock();
			if(start>last)
			{
				G.try_movedown();
				Block1.DownBlock();
				Block2.DownBlock();
				G.clear_block1();
				G.clear_block2();
				R.screen_refresh();
				R.draw_kong();
				last+=fall_time;
			}
			G.try_movedown();
			G.keyboard_hit();
			G.clear_block1();
			G.clear_block2();
			R.screen_refresh();
			R.draw_kong();
		}
		else break;
		}
	_getch();
	return 0;
}
