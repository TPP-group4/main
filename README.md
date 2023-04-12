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
* Hero：
	* id：ID
	* type = 0
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
* namespace::Player：
	* sort()
	* get_previous_info()
	* enable_previous_info()
