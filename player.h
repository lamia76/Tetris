
class player{
	public:
		void GetName();//输入玩家姓名
		void GetScore();//获取玩家当前得分 
		void AddBlock();//底部增加带空格的一行 
		void GetMap();//玩家得到地图 
		void pause;//暂停游戏
                void quit;//退出游戏
	private:
		string name;//玩家姓名 
		int score();//得分
		int blockA();//下落中的方块 
		int blockB();//即将下落的方块 
		int map();//玩家的的地图 
		bool ending();//游戏是否结束 
};
