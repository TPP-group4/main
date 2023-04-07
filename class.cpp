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
    int id_;
    int type_;
    int x_;
    int y_;
    int shield_life_;
    int is_controlled_;
    int health_;
    double operator-(const Entity &other)
    {
        int x = x_ - other.x_;
        int y = y_ - other.y_;
        x *= x;
        y *= y;
        return sqrt(x + y);
    }
public:
    Entity(int id, int type, int x, int y, int shield_life, int is_controlled, int health);
    const int get_ID() const { return id_; };
    const int get_X() const { return x_; };
    const int get_Y() const { return y_; };
    const int get_ShieldLife() const { return shield_life_; };
    const int get_IsControlled() const { return is_controlled_; };
    const int get_Health() const { return health_; };
};

Entity::Entity(int id, int type, int x, int y, int shield_life, int is_controlled, int health)
{
    id_ = id;
    type_ = type;
    x_ = x;
    y_ = y;
    shield_life_ = shield_life;
    is_controlled_ = is_controlled;
    health_ = health;
}

class Hero : public Entity
{
    public:
        Hero(int id, int type, int x, int y, int shield_life, int is_controlled, int health);
    private:
        // 不知道hero要不要其他的資訊
        // 比如：一開始的位置之類的
};

Hero::Hero(int id, int type, int x, int y, int shield_life, int is_controlled, int health) : Entity(id, type, x, y, shield_life, is_controlled, health)
{

};