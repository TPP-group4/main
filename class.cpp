#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 也許彥儒是這個意思，這部分更詳細的東西要再討論
class Pos
{
    public:
        const int get_x() const { return loc_.first; };
        const int get_y() const { return loc_.second; };
    private:
        pair<int, int> loc_;
};

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
        Entity(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled);
        Entity(const int &x, const int &y);
        const int get_X() const { return x_; };
        const int get_Y() const { return y_; };

        // operator overloading for computing distance between two entities
        double operator-(const Entity &other)
        {
            int x = x_ - other.x_;
            int y = y_ - other.y_;
            x *= x;
            y *= y;
            return sqrt(x + y);
        }
};

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
        Hero(int id, int type, int x, int y, int shield_life, int is_controlled);
    private:
        // 不知道hero要不要其他的資訊
        // 比如：一開始的位置之類的
};

Hero::Hero(int id, int type, int x, int y, int shield_life, int is_controlled) : Entity(id, type, x, y, shield_life, is_controlled)
{

};

class Monsters : public Entity
{
public:
    Monsters(int id, int type, int x, int y, int shield_life, int is_controlled, int health, int vx, int vy, int nearBase, int threatFor);
    const int get_Health() const { return health_; };
    const int get_VX() const { return vx_; };
    const int get_VY() const { return vy_; };
    const int get_NearBase() const { return nearBase_; };
    const int get_ThreatFor() const { return threatFor_; };
    const int get_ID() const { return id_; };
    const int get_ShieldLife() const { return shield_life_; };
    const int get_IsControlled() const { return is_controlled_; };
private:
    int health_;
    int vx_;
    int vy_;
    int nearBase_;
    int threatFor_;
};

Monsters::Monsters(int id, int type, int x, int y, int shield_life, int is_controlled, int health, int vx, int vy, int nearBase, int threatFor) : Entity(id, type, x, y, shield_life, is_controlled)
{
    health_ = health;
    vx_ = vx;
    vy_ = vy;
    nearBase_ = nearBase;
    threatFor_ = threatFor;
}

int main()
{
    // The corner of the map representing your base
    int base_x; 
    int base_y;
    cin >> base_x >> base_y; cin.ignore();

    // 判斷base在哪
    if(base_x == 0)
    {
        Entity enemy_Base(176300, 9000);
        Entity my_Base(0, 0);
    }
    else
    {
        Entity my_Base(176300, 9000);
        Entity enemy_Base(0, 0);
    }
    
    // Always 3
    int heroes_per_player;                      
    cin >> heroes_per_player; cin.ignore();

    vector<Monsters> my_monsters;
    vector<Hero> my_heros;
    vector<Hero> enemy_heros;
    vector<Monsters> enemy_monsters;
    vector<Monsters> neutral_monsters;

    // game loop
    while(1)
    {
        int my_health, my_mana;
        int enemy_health, enemy_mana;

        cin >> my_health >> my_mana; cin.ignore();
        cin >> enemy_health >> enemy_mana; cin.ignore();

        // Amount of heros and monsters you can see
        int entity_count;
        cin >> entity_count; cin.ignore();

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
            int threat_for;         // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither

            if(type == 1)
            {
                Hero tmp(id, type, x, y, shield_life, is_controlled);
                my_heros.emplace_back(tmp);

            }
            else if(type == 2)
            {

            }
        }
    }
}