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
        Entity(int id, int type, int x, int y, int shield_life, int is_controlled);
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

Entity::Entity(int id, int type, int x, int y, int shield_life, int is_controlled)
{
    id_ = id;
    type_ = type;
    x_ = x;
    y_ = y;
    shield_life_ = shield_life;
    is_controlled_ = is_controlled;
}

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