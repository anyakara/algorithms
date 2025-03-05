/**
 * @file pathplanning.cpp
 * @author Ananya Karra (ananya.karra@gmail.com)
 * @brief A* algorithm combines the best aspects of two other algorithms
 * greedy best-first search: algorithm explores the node that appears, to be closest
 * to the goal, based on a heuristic function.
 * distance traveled from start, smart estimate of the remaining distance to the goal
 * @version 0.1
 * @date 2025-03-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <cmath>
#include <vector>
// f(n) = g(n) + h(n)
// [start] -- g(n) --> [current] -- h(n) --> [goal]
/*
path cost g(n) calculated path cost function g(n) represents the exact,
known distance from the initial starting node to the current position
in our search. unlike estimated values, cost is precise and calculated
by adding up all the individual edge weights that have been traversed 
along with our chosen path.
*/

struct node {
    int x; int y;
    double h_cost, g_cost, f_cost;
    node* parent;
    node(int x_, int y_, double h_cost_, double g_cost_, double f_cost_, node*parent_) : x(x_), y(y_), h_cost(h_cost_), g_cost(g_cost_), f_cost(f_cost_), parent(parent_) {}
    bool operator!=(node other) {
        if (x != other.x) {
            return true;
        } return false;
    }
    bool operator==(node other) {
        if (x == other.x) {
            return true;
        } return false;
    }

    void operator=(node other) {
        x = other.x;
        y = other.y;
        double h_cost = other.h_cost;
        double g_cost = other.g_cost;
        double f_cost = other.f_cost;
        parent = other.parent;
    };
};

// heuristic decision
int manhattan_heuristic(node start, node end) {
    return std::abs(start.x-end.x) + std::abs(start.y-end.y);
};

int euclidean_distance(int x1, int x2, int y1, int y2) {
    return std::sqrt(std::pow((x1-x2), 2) + std::pow((y1-y2), 2));
};

// maintaining two essential lists
// open list;
// contains the nodes that need to be evaluated
// sorted by f(n) value lowest first
// new nodes are added as they're discovered

// closed list:
// contains already evaluted nodes
// helps avoid re-evaluating nodes
// used to reconstruct the final path


node fetchLowest(std::vector<node> openSet) {
    node minCostNode = openSet[0];
    for (int i = 0; i < (int)openSet.size(); i++) {
        if (minCostNode.f_cost < openSet[i].f_cost ) {
            minCostNode = openSet[i];
        }
    }
    return minCostNode;
}


std::vector<node> reconstruct_path(node startnode, node goal) {
    std::vector<node> path;
    node *tempNode = new node(startnode.x, startnode.y, startnode.h_cost, startnode.g_cost, startnode.f_cost, startnode.parent);
    while(startnode != goal) {
        path.push_back(startnode);
        tempNode = tempNode->parent;
    }
    delete tempNode;
    return path;
}


std::vector<node> getNeighbors(std::vector<node> allNodes, node currentNode) {
    std::vector<node> neighbors;
    std::vector<std::pair<int, int> > directions;
    std::pair<int, int> dir1 = {0, 1}; directions.emplace_back(dir1);
    std::pair<int, int> dir2 = {1, 0}; directions.emplace_back(dir2);
    std::pair<int, int> dir3 = {0, -1}; directions.emplace_back(dir3);
    std::pair<int, int> dir4 = {-1, 0}; directions.emplace_back(dir4);
    
    for (int i = 0; i < 4; i++) {
        int x = directions[i].first + currentNode.x;
        int y = directions[i].second + currentNode.y;
        neighbors.emplace_back(new node(x, y, 0, 0, 0, nullptr));
    }
};


std::vector<node> A_Star(node &start, node &goal) {
    std::vector<node> toEvaluate;
    toEvaluate.push_back(start);
    std::vector<node> closedList;

    // initialize the first algorithm
    start.g_cost = 0;
    start.h_cost = manhattan_heuristic(start, goal);
    start.f_cost = start.g_cost + start.h_cost;
    start.parent = nullptr;

    while (!toEvaluate.empty()) {
        // Get node with lowest f value - implement using a priority queue
        // for faster retrieval of the best node
        node currentNode = fetchLowest(toEvaluate);
        if (currentNode == goal) {
            return reconstruct_path(currentNode, goal);
        }
        // move current node from open to closed list
        toEvaluate.erase(std::remove(toEvaluate.begin(), toEvaluate.end(), currentNode));
        closedList.emplace_back(currentNode);

        std::vector<node> neighbors = getNeighbors(toEvaluate, currentNode);
        for (auto neighbor: neighbors) { 
            if (std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end()) {
                continue;
            }
            double tentative_g = currentNode.g_cost + manhattan_heuristic(currentNode, neighbor);
            if (std::find(toEvaluate.begin(), toEvaluate.end(), neighbor) != toEvaluate.end()) {
                toEvaluate.emplace_back(neighbor);
            } else if (tentative_g >= neighbor.g_cost) {
                continue;
            }

            neighbor.parent = &currentNode;
            neighbor.g_cost = tentative_g;
            neighbor.h_cost = manhattan_heuristic(neighbor, goal);
            neighbor.f_cost = neighbor.g_cost + neighbor.h_cost;

        }
        std::vector<node> vec;
        return vec; 
        // return failure -- no valid path exists
    };
    std::vector<node> path = reconstruct_path(start, goal);
    return path;
};

int main(int argc, char *argv[]) { return 1; }; // define the grid ad run the algorithm