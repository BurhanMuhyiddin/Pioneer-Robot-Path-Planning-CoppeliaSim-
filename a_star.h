#ifndef A_STAR_H_INCLUDED
#define A_STAR_H_INCLUDED

#define INF				9999999

void solve_a_star(int clientID);
void get_initial_and_goal_positions(int clientID);
void init_a_star(int clientID);
int calculate_heuristic(int x, int y);
int* calculate_min_f_cost();
void update_costs(int current, int index);
bool check_node(int index);
bool check_node_environment(int index);

#endif // !A_STAR_H_INCLUDED
