class block{
	public:
		void InitateBlock();//��ʼ��������Ϣ 
		void BuildBlock(int x,int y);//���ɷ���
		void TurnBlock();//����ת�䷽�� 
		void MoveBlock_left;//�������� 
		void MoveBlock_right;//�����Ҷ� 
		void DownBlock;//�������� 
		void Speed_up;//������� 
	private:
		int	Block_1form_1[8]={1,0,1,1,2,0,2,1};//��Ϊ4��4�У��������У�00 01 10 11
		int	Block_2form_1[8]={1,1,2,1,2,2,2,3};//01 11 12 13
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
		int	Block_4form_4[8]={1,1,1,2,1,3,0,2};//
		int	Block_5form_1[8]={2,0,2,1,1,1,1,2};//20 21 11 12
		int	Block_5form_2[8]={0,0,1,0,1,1,2,1};//
		int	Block_6form_1[8]={0,1,0,2,1,0,1,1};//21 22 10 11
		int	Block_6form_2[8]={0,1,1,1,2,0,2,1};//
		int	Block_7form_1[8]={1,0,1,1,1,2,1,3};//10 11 12 13
		int	Block_7form_2[8]={0,1,1,1,2,1,3,1};//
		int Block_color;//������ɫ 
		int Block_form;//������״ 
		int Block_now[8]={0};//���ڵķ���
		int Block_next[8]={0};//��һ������ 
		int speed;//���������ٶ� 
};
