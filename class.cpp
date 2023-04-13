#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <list>

using namespace std;

class Entity
{
    private:

    protected:
        int x_;
        int y_;
        int id_;
        int type_;
        int shield_life_;
        int is_controlled_;
        int health_;
        int vx_;
        int vy_;
        int nearBase_;
        int threatFor_;
        Entity(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled, const int &health, const int &vx, const int &vy, const int &nearBase, const int &threatFor);
    
    public:
        Entity();
        Entity(const int &x, const int &y);
        const int& get_X() const { return x_; };
        const int& get_Y() const { return y_; };
        const int& get_ShieldLife() const { return shield_life_; };
        const int& get_ID() const { return id_; };

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
Entity::Entity(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled, const int &health, const int &vx, const int &vy, const int &nearBase, const int &threatFor)
{
    id_ = id;
    type_ = type;
    x_ = x;
    y_ = y;
    shield_life_ = shield_life;
    is_controlled_ = is_controlled;
    shield_life_ = shield_life;
    is_controlled_ = is_controlled;
    health_ = health;
    vx_ = vx;
    vy_ = vy;
    nearBase_ = nearBase;
    threatFor_ = threatFor;
}

// 繼承 Entity 的建構子
class Hero : public Entity
{
    public:
        Hero() : Entity() { nearBase_ = -1; };
        Hero(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled, const int &health, const int &vx, const int &vy, const int &nearBase, const int &threatFor) : Entity(id, type, x, y, shield_life, is_controlled, health, vx, vy, nearBase, threatFor){};
        bool nearBase(Entity base) {
            if(*this - base < 5500){
                return true;
            }
            else{
                return false;
            }
        };
        void set_nearBase(int nearBase){
            nearBase_ = nearBase;
        }
       
    private:
        // 用於判斷對方 hero 是否在我方的base裡面
};

class Monsters : public Entity
{
    public:
        Monsters() : Entity(){};
        Monsters(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled, const int &health, const int &vx, const int &vy, const int &nearBase, const int &threatFor) : Entity(id, type, x, y, shield_life, is_controlled, health, vx, vy, nearBase, threatFor){};
        const int& get_Health() const { return health_; };
        const int& get_VX() const { return vx_; };
        const int& get_VY() const { return vy_; };
        const int& get_NearBase() const { return nearBase_; };
        const int& get_ThreatFor() const { return threatFor_; };
        const int& get_IsControlled() const { return is_controlled_; };
    private:

};

class action{
    public:
        action(){};
        string option = "WAIT";
        int id = -1;
        pair<int, int> pos = make_pair(-1,-1);
};

namespace Player{
    Entity my_Base;
    Entity enemy_Base;
    list<map<int, Entity>> previous_info;
    vector<Monsters> my_monsters;
    vector<Hero> my_heros;
    vector<Hero> enemy_heros;
    vector<Monsters> enemy_monsters;
    vector<Monsters> neutral_monsters;
    vector<Monsters> monsters;
    int my_health, my_mana;
    int enemy_health, enemy_mana;
    enum{
        near_mybase,
        near_enemybase,
        less_health,
    };

    void base_init(const int &base_x){
        if(base_x == 0)
        {
            enemy_Base = Entity(17630, 9000);
            my_Base = Entity(0, 0);
        }
        else
        {
            my_Base = Entity(17630, 9000);
            enemy_Base = Entity(0, 0);
        }
        return;
    }

    void input(const int &id, const int &type, const int &x, const int &y, const int &shield_life, const int &is_controlled, const int &health, const int &vx, const int &vy, const int &near_base, const int &threat_for){
        if(type == 1)
        {
            // Hero tmp(id, type, x, y, shield_life, is_controlled);
            Hero tmp(id, type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for);
            my_heros.emplace_back(tmp);
            if(tmp.nearBase(my_Base)){
                tmp.set_nearBase(1);
            }
            else if(tmp.nearBase(enemy_Base)){
                tmp.set_nearBase(2);
            }
            else{
                tmp.set_nearBase(0);
            }
        }
        else if(type == 2)
        {
            // Hero tmp(id, type, x, y, shield_life, is_controlled);
            Hero tmp(id, type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for);
            enemy_heros.emplace_back(tmp);
        }
        else if(type == 0)
        {
            // 1=your base, 2=your opponent's base, 0=neither
            Monsters tmp(id, type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for);       
            monsters.emplace_back(tmp);
            if(near_base == 1)
            {
                my_monsters.emplace_back(tmp);
            }
            else if(near_base == 0)
            {
                enemy_monsters.emplace_back(tmp);
            }
            else if(near_base == 2)
            {
                neutral_monsters.emplace_back(tmp);
            }
        }
    }

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
        monsters.clear();
        return;
    }
    bool compare_dist_mybase(Monsters first, Monsters second){
        return first-my_Base < second-my_Base;
    }
    bool compare_dist_enemybase(Monsters first, Monsters second){
        return first-enemy_Base < second-enemy_Base;
    }
    bool compare_health(Monsters first, Monsters second){
        return first.get_Health() < second.get_Health();
    }

    void sort_monsters( vector<Monsters> &m, const int &opt){
        switch(opt)
        {
            case near_mybase:
                sort( m.begin(), m.end(), compare_dist_mybase);
                break;
            case near_enemybase:
                sort( m.begin(), m.end(), compare_dist_enemybase);
                break;
            case less_health:
                sort( m.begin(), m.end(), compare_health);
                break;
            default:
                break;
        }

        return;
    }
    void enable_previous_info( const int &clip=0){
        map<int, Entity> tmp_map;
         for(auto &e:my_heros)
        {   tmp_map.insert(pair< int, Entity> (e.get_ID(), e) ); }
         for(auto &e:enemy_heros)
        {   tmp_map.insert(pair< int, Entity> (e.get_ID(), e) ); }
        for(auto &e:my_monsters)
        {   tmp_map.insert(pair< int, Entity> (e.get_ID(), e) ); }
        for(auto &e:enemy_monsters)
        {   tmp_map.insert(pair< int, Entity> (e.get_ID(), e) ); }
        for(auto &e:neutral_monsters)
        {   tmp_map.insert(pair< int, Entity> (e.get_ID(), e) ); }

        previous_info.push_front(tmp_map);
        if(previous_info.size() > clip+1)
        {
            previous_info.pop_back();
        }
    }

    void get_previous_info( const int &pre_num, map<int, Entity> &info){
        info.clear();
        if(pre_num >= previous_info.size())
        {
            cerr<<"Info size error! "<<"pre_num: "<< pre_num << ", previous info size: " << previous_info.size() <<endl;
            cerr <<" => pre_num out of list's size !!!"<<endl;
            return;
        }
        else
        {
            auto it = next(previous_info.begin(), pre_num);
            info = *it;
            return;
        }
    }

    void find_wind_starting_point(vector<pair<int,int> > &wind_points){
        wind_points.clear();
        
        if(previous_info.size()<1)
        {
            cerr <<"Don't have enough previous info"<<endl;
            return;
        }
        else
        {
            auto it_0 = next(previous_info.begin(), 0);
            auto it_1 = next(previous_info.begin(), 1);
            map<int, Entity> info_0 = *it_0;
            map<int, Entity> info_1 = *it_1;
            
            //cerr << "winded id: ";
            for(auto m: info_0)
            {
                if(info_1.find(m.first) != info_1.end() && m.second-info_1[m.first] >= 2000)
                {
                    wind_points.push_back(make_pair(info_1[m.first].get_X(), info_1[m.first].get_Y()) );
                    //cerr << m.first << " ";
                }
            }
            //cerr<<endl;
            
        }
        return;
    }

    // 輸入r
    // 隨機回傳在1/4圓中的任意位置
    // 圓心：mybase
    pair<int, int> random_pos_circle(int range)
    {
        int base_top_left = my_Base.get_X() == 0 ? 1 : 0; 
        int theta;
        if(base_top_left)
        {
            int minValue = 0;
            int maxValue = 90;
            theta = rand() % (maxValue - minValue + 1) + minValue;
        }
        else
        {
            int minValue = 180;
            int maxValue = 270;
            theta = rand() % (maxValue - minValue + 1) + minValue;
        }
        auto pi = acos(-1.0);
        // 將角度轉為弧度
        double radian = theta * pi / 180.0;
        // generate number between 1 and range
        int r = rand() % range + 1;
        int x = r * cos(radian);
        int y = r * sin(radian);
        pair<int, int> tmp;
        if(base_top_left)
        {
            tmp = make_pair(x, y);
        }
        else
        {
            tmp = make_pair(17639 + x, 9000+ y);
        }
        return tmp;
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