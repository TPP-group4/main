
## Headers
# group 4
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
	* pair <int,int> 座標
	> 可以將 action 給 cout ,ex : cout << (Action)a;
* namespace::Player：
	* void base_init( const int base_x)

        * 說明：
            辨識基地座標位置
  
    * void sort_monsters( vector<Monsters> &monsters, const int &opt=0)

        * 說明：
            將輸入的Monsters vector做遞增排序

			> 輸入參數opt可選擇排序依據：  
					opt=0時，依照monster跟我方基地距離排序  
					opt=1時，依照monster跟對方基地距離排序  
					opt=2時，依照monster剩餘血量排序  
					...  
				預設opt = 0

    * void enable_previous_info( const int &clip=0)
        * 說明：儲存每回合對方英雄與怪物的資訊  
    &emsp;&emsp;&ensp;&nbsp;  以關聯式容器(map)儲存物件(Entity)，鍵值為各物件的id
        
			> 輸入參數clip可決定儲存回和數：  
					clip=0時，只儲存當前回合資訊  
					clip=1時，將儲存當前回合及上一回合資訊  
					...  
				預設clip = 0
    * void get_previous_info( const int &pre_num, map<int, Entity> &info)

        * 說明：
            將要求的回合資訊儲存到輸入參數info
            
			> 輸入參數pre_num可選擇要查看的回合：  
					pre_num=0時，可查看當前回合  
					pre_num=1時，可查看上一回合  
					...   
				預設pre_num = 0  

	* void find_wind_starting_point(vector<pair<int,int> > &wind_points)

		* 說明：
			比對本回合與上一回合資料，偵測怪物是否有被風吹過的跡象

			> 以輸入參數wind_points儲存被風吹過的怪獸其原始位置：  
				1. 缺少上一回合資料時，將不返還任何資料並輸出錯誤訊息  
				2. 沒有偵測到被風吹過的怪獸時，將不儲存任何資料  
				3. 偵測到被風吹過的怪獸時，將依照monster的id順序儲存位置  