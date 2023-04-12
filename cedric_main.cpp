#include "class.cpp"
int main()
{
    // The corner of the map representing your base
    int base_x; 
    int base_y;

    cin >> base_x >> base_y; cin.ignore();

    // 判斷base在哪 //要不要包成Player::base_init
    Player::base_init(base_x);
    // Always 3
    int heroes_per_player;                      
    cin >> heroes_per_player; cin.ignore();

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
        int cnt =0;
        for(int i=0 ; i < heroes_per_player ; i++){
            Player::sort_monsters(Player::monsters,Player::near_mybase);
            if(Player::monsters.size() > cnt){
                action a;
                a.option = "MOVE";
                a.pos = make_pair(Player::monsters[cnt].get_X(),Player::monsters[cnt].get_Y());
                cout << a;
                cnt++;
            }
            else{
                action a;
                a.option = "WAIT";
                cout << a;
            }
        }
        Player::clearVector();
    }
}