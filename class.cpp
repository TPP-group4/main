#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

class Entity
{
    private:
        int x_;
        int y_;

    protected:
        int id_;
        int type_;
        int shield_life_;
        int is_controlled_;
    
    public:
        Entity();
        Entity(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled);
        Entity(const int &x, const int &y);
        const int get_X() const { return x_; };
        const int get_Y() const { return y_; };
        const int get_ShieldLife() const { return shield_life_; };

        // operator overloading for computing distance between two entities
        double operator-(const Entity &other)const{
            int x = x_ - other.x_;
            int y = y_ - other.y_;
            x *= x;
            y *= y;
            return sqrt(x + y);
        }
};

Entity::Entity()
{
    id_ = -1;
    type_ = -1;
    x_ = -1;
    y_ = -1;
    shield_life_ = -1;
    is_controlled_ = -1;
}
// for base
Entity::Entity(const int &x, const int &y)
{
    id_ = -1;
    type_ = -1;
    x_ = x;
    y_ = y;
    shield_life_ = -1;
    is_controlled_ = -1;
}

// for reuse code
Entity::Entity(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled)
{
    id_ = id;
    type_ = type;
    x_ = x;
    y_ = y;
    shield_life_ = shield_life;
    is_controlled_ = is_controlled;
}

// 繼承 Entity 的建構子
class Hero : public Entity
{
    public:
        Hero() : Entity() { nearBase_ = -1; };
        Hero(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled) : Entity(id, type, x, y, shield_life, is_controlled) { is_near_myBase_ = false; };
        Hero(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled);
        void set_nearBase(const int& a) { nearBase_ = a; };
        const int& get_nearBase() { return nearBase_; };
    private:
        // 用於判斷對方 hero 是否在我方的base裡面
        int nearBase_;
};

Hero::Hero(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled) : Entity(id, type, x, y, shield_life, is_controlled)
{
    nearBase_ = -1;
};

class Monsters : public Entity
{
public:
    Monsters();
    Monsters(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled, const int &health, const int &vx, const int &vy, const int &nearBase, const int &threatFor);
    const int get_Health() const { return health_; };
    const int get_VX() const { return vx_; };
    const int get_VY() const { return vy_; };
    const int get_NearBase() const { return nearBase_; };
    const int get_ThreatFor() const { return threatFor_; };
    const int get_IsControlled() const { return is_controlled_; };
private:
    int health_;
    int vx_;
    int vy_;
    int nearBase_;
    int threatFor_;
    bool is_near_myBase_;
};

Monsters::Monsters():Entity()
{
    health_ = -1;
    vx_ = -1;
    vy_ = -1;
    nearBase_ = -1;
    threatFor_ = -1;
}

Monsters::Monsters(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled, const int &health, const int &vx, const int &vy, const int &nearBase, const int &threatFor) : Entity(id, type, x, y, shield_life, is_controlled)
{
    health_ = health;
    vx_ = vx;
    vy_ = vy;
    nearBase_ = nearBase;
    threatFor_ = threatFor;
}

class action{
    public:
        string option = "WAIT";
        int id = -1;
        pair<int, int> pos = make_pair(-1,-1);
};

namespace Player{
    Entity my_Base;
    Entity enemy_Base;

    vector<Monsters> my_monsters;
    vector<Hero> my_heros;
    vector<Hero> enemy_heros;
    vector<Monsters> enemy_monsters;
    vector<Monsters> neutral_monsters;
    int my_health, my_mana;
    int enemy_health, enemy_mana;

    Monsters find_nearest_monster(Entity e,vector<Monsters> M){
        Monsters m;
        int distance = INT32_MAX;
        for(auto monster : M ){
            if (monster-e < distance){
                distance = monster - e ;
                m = monster;
            }
        }
        return m;
    }

    bool canWind (const Hero &a,const Entity &b){
        return ( (a-b) < 1280 && my_mana > 10 && b.get_ShieldLife()==0 );
    }
    bool canControl(const Hero &a,const Entity &b){
        return ( (a-b) < 2200 && my_mana > 10 && b.get_ShieldLife()==0 );
    }
    bool canShield(const Hero &a,const Entity &b){
        return ( (a-b) < 2200 && my_mana > 10 && b.get_ShieldLife()==0 );
    }

    void clearVector(){
        my_monsters.clear();
        my_heros.clear();
        enemy_heros.clear();
        enemy_monsters.clear();
        neutral_monsters.clear();
        return;
    }

    void sort(){

    }

    pair<int ,int > &windPos(){

    }
};

ostream & operator <<(ostream &os, const action &a){
    if( a.option == "WAIT" ){
        os << a.option << endl;
    }
    else if( a.option == "WIND" ){
        os << "SPELL " << a.option << " " << a.pos.first << " " << a.pos.first << endl;
    }
    else if( a.option == "CONTROL" ){
        os << "SPELL " << a.option << " " << a.id << " " << a.pos.first << " " << a.pos.first << endl;
    }
    else if( a.option == "SHIELD" ){
        os << "SPELL " << a.option << " " << a.id << endl;
    }
    else if( a.option == "MOVE" ){
        os << "MOVE " << a.pos.first << " " << a.pos.second << endl;
    }
    else{
        os << "WAIT" << endl;
    }
    return os;
}

int main()
{
    // The corner of the map representing your base
    int base_x; 
    int base_y;

    //cin >> base_x >> base_y; cin.ignore();

    // 判斷base在哪
    if(base_x == 0)
    {
        Player::enemy_Base = Entity(176300, 9000);
        Player::my_Base = Entity(0, 0);
    }
    else
    {
        Player::my_Base = Entity(176300, 9000);
        Player::enemy_Base = Entity(0, 0);
    }
    
    // Always 3
    int heroes_per_player;                      
    //cin >> heroes_per_player; cin.ignore();

    // game loop
    while(1)
    {
       
        // cin >> Player::my_health >> Player::my_mana; cin.ignore();
        // cin >> Player::enemy_health >> Player::enemy_mana; cin.ignore();

        // Amount of heros and monsters you can see
        int entity_count;
        //cin >> entity_count; cin.ignore();

        for(int i = 0; i < entity_count; ++i)
        {
            int id;                 // Unique identifier
            int type;               // 0=monster, 1=your hero, 2=opponent hero
            int x;                  // Position of this entity
            int y;
            int shield_life;        // Ignore for this league; Count down until shield spell fades
            int is_controlled;      // Ignore for this league; Equals 1 when this entity is under a control spell
            int health;             // Remaining health of this monster
            int vx;                 // Trajectory of this monster
            int vy;
            int near_base;          // 0=monster with no target yet, 1=monster targeting a base
            int threat_for =0;         // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither

            if(type == 1)
            {
                Hero tmp(id, type, x, y, shield_life, is_controlled);
                Player::my_heros.emplace_back(tmp);
                // 要解構嗎不曉得?
            }
            else if(type == 2)
            {
                Hero tmp(id, type, x, y, shield_life, is_controlled);
                if(hypot(Player::my_Base.get_X() - x, Player::my_Base.get_Y() - y) < 5000)
                {
                    tmp.set_iSNearMyBase(true);
                }
                else
                {
                    tmp.set_iSNearMyBase(false);
                }
                Player::enemy_heros.emplace_back(tmp);
            }
            else if(type == 0)
            {
                // 1=your base, 2=your opponent's base, 0=neither
                Monsters tmp(id, type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for);
                switch (threat_for)
                {
                    case 0:
                        Player::neutral_monsters.emplace_back(tmp);
                        break;
                    case 1:
                        Player::my_monsters.emplace_back(tmp);
                        break;
                    case 2:
                        Player::enemy_monsters.emplace_back(tmp);
                        break;
                    default:
                        break;
                }
            }
        }
        action a;
        a.option = "MOVE";
        a.pos = make_pair(17630,9000);
        cout << a;
    }
}