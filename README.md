## 類別庫 文件
# 進階程式設計-2023
我們是第四組
# [遊戲簡介]( https://www.codingame.com/multiplayer/bot-programming/spring-challenge-2022)
> 名稱：spider attack
* 兩個角色
	* **spider**：通常是漫無目的，若離基地太近則會直衝基地，若碰到基地會使其檢少一條命
	* **Hero**：雙方都有三隻，到後期會有魔法可以使用
* 一對一的攻防遊戲
	* 守護自己的基地不被**spider**攻擊，或是成功讓對方被**spider**攻擊，並嘗試生存比對方久
	* 你可以控制三隻 **Hero**守護自己的基地或是透過一些戰略讓**spider**攻擊對方的基地
	* 雙方的基地有三條命
	
## 資料設計
* Monster：
	* id：ID
	* type = 0
	* x, y：在地圖上的位置
	* shieldLife：盾牌還剩多久
	* isControlled：有被控制嗎？
	* health：血量
	* vx, vy：下一步的向量
	* nearBase：1&rarr;會往我的基地衝, 2&rarr;其他
	* threatFor

	> Monster tmp(id, type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for);
 * Hero :
  * myHero：
    * id：ID
    * type = 1
    * x, y：在地圖上的位置
    * shieldLife：盾牌還剩多久
    * isControlled：有被控制嗎？
    * **nearBase**：
      * 0&rarr;在地圖空白區域
      * 1&rarr;距離我的基地<5500
      * 2&rarr;距離對方的基地<5500
  * enemyHero：
    * id：ID
    * type = 2
    * x, y：在地圖上的位置
    * shieldLife：盾牌還剩多久
    * isControlled：有被控制嗎？
    * **nearBase**：
      * 0&rarr;在地圖空白區域
      * 1&rarr;距離我的基地<5500
      * 2&rarr;距離對方的基地<5500
	> Hero tmp(id, type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for);

		
> Entity, Hero和Monster之間可以用剪法操作：
> `monster - my_base `
> * 回傳值：他們之間的距離

## class design：類別設計

* Entity：來保存基地的資訊，並提供剪法的操作
	* get_X()：獲取x
	* get_Y()：獲取y
* Monster：來保存**spider**的資訊
	* get_ID()：獲取其ID
	* get_health：獲取其血量
	* get_VX(), get_VY()：獲取其向量
	* get_NearBase()：獲取其nearBase的數值
	* get_ThreatFor()：獲取其threatFor的數值
 	* get_IsControlled()：有被控制嗎？
 	* get_ShieldLife()：盾牌還有多久
* Hero：來保存**hero**的資訊
	* get_NearBase()：獲取其nearBase的數值
	> hero的nearBase與monster的定義不同
* action 用來記錄行為
	* option "WAIT" "MOVE" "WIND" "CONTROL"
	* id
	* `pair <int,int>` 座標
	> 可以將 action 給 cout ,ex : `cout << (Action)a`;
* namespace::Player：

	* 資料內容
		Entity my_Base;
		Entity enemy_Base;
		list<map<int, Entity>> previous_info;
		vector<Monsters> my_monsters;
		vector<Hero> my_heros;
		vector<Hero> enemy_heros;
		vector<Monsters> enemy_monsters;
		vector<Monsters> neutral_monsters;
		vector<Monsters> monsters;
		> 每回合結束需呼叫 clearVector() 
	* `void input(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled, const int &health, const int &vx, const int &vy, const int &near_base, const int &threat_for)；`
		* 將整筆資料讀入根據 type 加入到 
			> vector<Hero> my_heros;  
			vector<Hero> enemy_heros;  
			vector<Monsters> monsters;

    * `void base_init( const int base_x)`

        * 說明：
            辨識基地座標位置
  
    * `void sort_monsters( vector<Monsters> &monsters, const int &opt=0 )`  

        * 說明：
            將輸入的Monsters vector做遞增排序

			>	輸入參數opt可選擇排序依據：  
			  
				opt = mybase時，依照monster跟我方基地距離排序  
				opt = enemybase時，依照monster跟對方基地距離排序  
				opt = lesshealth時，依照monster剩餘血量排序  
				...  
				預設opt = 0

    * `void enable_previous_info( const int &clip=1 )`  
        * 說明：設定儲存的回和數
        
			>	輸入參數clip可決定儲存回和數：  
				
				clip=0時，只儲存當前回合資訊  
				clip=1時，將儲存當前回合及上一回合資訊  
				...  
				預設clip = 1  
  
	* `void save_info()`  
		*說明：儲存每回合對方英雄與怪物的資訊，以關聯式容器(map)儲存物件(Entity)，鍵值為各物件的id
  
    * `map<int, Entity> get_previous_info( const int &pre_num )`

        * 說明：
            將要求的回合資訊儲存到輸入參數info
            
			> 輸入參數pre_num可選擇要查看的回合： 
			   
				pre_num=0時，可查看當前回合  
				pre_num=1時，可查看上一回合  
				...   
				預設pre_num = 0  

            *pre_num大於儲存的回和數，將無法查看回合資訊看並輸出錯誤訊息 ! ! !*
  
    * `bool find_wind_starting_point(vector<pair<int,int> > &wind_points )`

        * 說明：比對本回合與上一回合資料，偵測怪物是否有被風吹過的跡象

			> 以輸入參數wind_points儲存被風吹過的怪獸其原始位置：

				1. 缺少上一回合資料時，將不儲存任何資料並回傳false及輸出錯誤訊息  
				2. 沒有偵測到被風吹過的怪獸時，將不儲存任何資料並回傳false 
				3. 偵測到被風吹過的怪獸時，將依照monster的id順序儲存位置並回傳true
				
	* `pair<int, int> random_pos_circle(int range) `
		* 返回隨機的位置距離自己的基地`range`=>在固定範圍內活動

			> 使用方法：  
			  
				`pair<int, int> tmp = Player::random_pos_circle(10500);`  
				`cout << "MOVE " << tmp.first << " " << tmp.second << endl;`
