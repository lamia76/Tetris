class block{
	public:
		void InitateBlock();//初始化方块信息 
		void RandBlock();//随机生成方块
		void TurnBlock();//方块转变方向 
		int Speed();//规定方块下落的速度
		void MoveBlock_left;//方块左移 
		void MoveBlock_right;//方块右动 
		void DownBlock;//方块下落 
		void Speed_up;//方块加速 
	private:
		int	Block_1form_1[4][4];//分为4行4列，左行右列；00 01 10 11
		int	Block_2form_1[4][4];//00 10 11 12
		int	Block_2form_2[4][4];//
		int	Block_2form_3[4][4];//
		int	Block_2form_4[4][4];//	 
		int	Block_3form_1[4][4];//02 10 11 12
		int	Block_3form_2[4][4];//
		int	Block_3form_3[4][4];//
		int	Block_3form_4[4][4];//
		int	Block_4form_1[4][4];//01 10 11 12
		int	Block_4form_2[4][4];//
		int	Block_4form_3[4][4];//
		int	Block_4form_4[4][4];//
		int	Block_5form_1[4][4];//00 01 11 12
		int	Block_5form_2[4][4];//
		int	Block_6form_1[4][4];//01 02 10 11
		int	Block_6form_2[4][4];//
		int	Block_7form_1[4][4];//10 11 12 13
		int	Block_7form_2[4][4];//
};
