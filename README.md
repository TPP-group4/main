# group 4
## 類別庫 文件
### function:
* 
```cpp
void sort_monsters( vector<Monsters> &monsters, const int &opt=0)
```  
    * 說明：
        將輸入的Monsters vector做遞增排序。

    > 輸入參數opt可選擇排序依據：  
            opt=0時，依照monster跟我方基地距離排序  
            opt=1時，依照monster跟對方基地距離排序  
            opt=2時，依照monster剩餘血量排序  
        預設opt = 0

* 
```cpp
void enable_previous_info( const int &clip=0)
```
    * 說明：儲存每回合對方英雄與怪物的資訊。  
    &emsp;&emsp;&ensp;&nbsp;  以關聯式容器(map)儲存物件(Entity)，鍵值為各物件的id。
        
    > 輸入參數clip可決定儲存回和數：  
            clip=0時只儲存當前回合資訊  
            clip=1時將儲存當前回合及上一回合資訊，以此類推。  
        預設clip = 0
*
```cpp
void get_previous_info( const int &pre_num, map<int, Entity> &info)
```
    * 說明：
        將要求的回合資訊儲存到輸入參數info。
    > 輸入參數pre_num可選擇要查看的回合：
            pre_num=0時可查看當前回合  
            pre_num=1時可查看上一回合，以此類推。
        預設pre_num = 0  
        **pre_num大於儲存的回和數，將無法查回合資訊看並輸出錯誤訊息。**