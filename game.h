class game{
	public:
	    void setcolot();//方块颜色设置 
	    void hit();//判断方块之间的或与界面的碰撞以及是否可以移动 
	    int score();//消除行以及加分判定
	    void add();//加一行随机行
	    void time();//时间统计
	    void accelerate();//随游戏时间推进方块加速下落 
	    bool out();//判断是否游戏失败（即方块是否超出界面上限） 
	    void return();//界面切换 
	private:	
}; 
