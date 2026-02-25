//includes
#include <set>
#include <vector>
#include <cmath>
#include <queue>
#include <map>

#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/twist.hpp>

//grid dimensions and obstacle creation

int height = 11;
int width = 11;
//int obs_no = __;

void obstacle_generate(){
    //remaining
}

//define node
struct Node{
    int x, y;
    double cost_f, cost_g;
};


//create A* Planner
class AStar{
public:
    //instance var
    std::pair<int,int> start, goal;
    std::set<std::pair<int, int>> obs;

    //constructor
    AStar(std::pair<int, int> s, std::pair<int, int> g, std::vector<std::pair<int, int>> obstacles){
        start = s;
        goal = g;
        obs.insert(obstacles.begin(), obstacles.end());
    }

    //heuristic calculator
    double cost_h(std::pair<int, int> p1, std::pair<int, int> p2){
        return hypot(p1.first - p2.first, p1.second - p2.second);
    }

    //create neighbours
    std::vector<std::pair<int, int>> neighbor(std::pair<int, int> current){
        std::vector<std::pair<int, int>> neighbor;
        
        int x[4] = {-1, 1, 0, 0};
        int y[4] = {0, 0, 1, -1};

        for(int i = 0; i < 4; i++){
            int new_x = current.first + i;
            int new_y = current.second + i;
            if(new_x >= 0 && new_y >= 0 && new_x <= width && new_y <= height){
                if(obs.count({new_x, new_y}) == 0){
                    neighbor.push_back({new_x, new_y});
                }
            }
        }
        return neighbor;
    }
    
    //the search function
    std::vector<std::pair<int, int>> AStarSearch(){
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;
        std::map<std::pair<int, int>, std::pair<int, int>> came_from;
        std::map<std::pair<int, int>, double> cost_g;

        frontier.push({start.first, start.second, 0, 0});
        cost_g[start] = 0;

        while(!frontier.empty()){
            Node current = frontier.top();
            frontier.pop(); //analyse

            std::pair<int, int> c = {current.x, current.y};
            
            if(c == goal){
                std::vector<std::pair<int, int>> path;
                //remaining
            }

            for(auto &nb : neighbor(c)){
                double tentative=cost_g[c]+1;
                if(!cost_g.count(nb) || tentative<cost_g[nb]){
                    came_from[nb]=c;
                    cost_g[nb]=tentative;
                    double f=tentative + cost_h(nb,goal);
                    frontier.push({nb.first, nb.second, f, tentative});
                }
            }

        }

        return {};

    }

};

//create turtle movement class

int main(int argc, char** argv){

}