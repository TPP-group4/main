#include "class.cpp"

int main()
{
    // The corner of the map representing your base
    int base_x; 
    int base_y;

    cin >> base_x >> base_y; cin.ignore();

    // 判斷base在哪
    Player::base_init(base_x);
    // Always 3
    int heroes_per_player;                      
    cin >> heroes_per_player; cin.ignore();

    vector<pair<int, int>> wind_points;

    map<int, Entity> info;
    map<int, Entity> info_1;
    map<int, Entity> info_2;
    Player::enable_previous_info(1); //啟用功能，設定儲存回和數

    // game loop
    while(1)
    {
        cin >> Player::my_health >> Player::my_mana; cin.ignore();
        cin >> Player::enemy_health >> Player::enemy_mana; cin.ignore();

        // Amount of heros and monsters you can see
        int entity_count;
        cin >> entity_count; cin.ignore();

        for(int i = 0; i < entity_count; ++i)
        {
            int id; // Unique identifier
            int type; // 0=monster, 1=your hero, 2=opponent hero
            int x; // Position of this entity
            int y;
            int shield_life; // Ignore for this league; Count down until shield spell fades
            int is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell
            int health; // Remaining health of this monster
            int vx; // Trajectory of this monster
            int vy;
            int near_base; // 0=monster with no target yet, 1=monster targeting a base
            int threat_for; // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
            cin >> id >> type >> x >> y >> shield_life >> is_controlled >> health >> vx >> vy >> near_base >> threat_for; cin.ignore();
        
            Player::input(id , type , x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for);
        }

        Player::save_info();
        info = Player::get_previous_info(0); //取得當前回合資訊
        info_1 = Player::get_previous_info(1);//取得上一回合資訊
        info_2 = Player::get_previous_info(2); //欲取得兩回合前資訊，超出enable_previous_info設定大小，會輸出錯誤訊息
        
        cerr << "map present clip: ";
        for(auto m: info)
        { cerr << m.first <<" "; }
        cerr<<endl;
        
        cerr << "map 1 clip before: ";
        for(auto m: info_1)
        {cerr << m.first <<" ";}
        cerr<<endl;

        cerr << "map 2 clips before (error_test): ";
        for(auto m: info_2)
        {cerr << m.first <<" ";}
        cerr<<endl;
        cerr <<"--------------------------------------------------"<<endl;
        
        Player::find_wind_starting_point(wind_points); //確認是否有物件被吹風，並取得吹風起點

        cerr <<"Found someone blowing winds: " << wind_points.size() << endl;
        if(wind_points.size() > 0)
        {
            for(auto p:wind_points)
            cerr <<"( "<< p.first<< ", " << p.second <<" )" <<  endl; //輸出吹風起點
        }
        cerr <<"--------------------------------------------------"<<endl;

        Player::sort_monsters(Player::monsters, Player::near_mybase); //依照怪物與基地距離排序
        cerr <<"Sort near mybase: "<<endl;
        for(auto m:Player::monsters)
        { cerr <<m.get_ID() <<" -> " << m-Player::my_Base << endl; }

        Player::sort_monsters(Player::monsters, Player::near_enemybase); //依照怪物與對方基地距離排序
        cerr <<"Sort near enemybase: "<<endl;
        for(auto m:Player::monsters)
        { cerr <<m.get_ID() <<" -> " << m-Player::enemy_Base << endl; }

        Player::sort_monsters(Player::monsters, Player::less_health);  //依照怪物剩餘血量排序
        cerr <<"Sort less health: "<<endl;
        for(auto m:Player::monsters)
        { cerr <<m.get_ID() <<" -> " << m.get_Health() << endl; }
        cerr <<"--------------------------------------------------"<<endl;
        
        for(int i = 0; i < 3; ++i)
        {
            action a;
            Monsters tmp = Player::find_nearest_monster(Player::my_Base ,Player::monsters);
            if(i==0)
            {
                a.option = "MOVE";
                a.pos = make_pair(Player::enemy_Base.get_X()-7000, Player::enemy_Base.get_Y()-7500);
                cout << a;
                continue;
            }
            if(Player::my_monsters.size())
            {
                a.option = "MOVE";
                a.pos = make_pair(tmp.get_X(), tmp.get_Y());
                cout << a;
            }
            else
            {
                pair<int, int> tmp = Player::random_pos_circle(7500);
                cout << "MOVE " << tmp.first << " " << tmp.second << endl;
            }
        }
        Player::clearVector();
    }
}