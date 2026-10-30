// 题目：815. 公交路线（Bus Routes）
// 思路：以站点建反查表（站点 -> 经过它的线路），BFS 逐层扩展，visBus/visStop 去重，层数即乘车次数。
// 时间复杂度：O(S + L)，S 为站点数、L 为线路经过站点的总数；空间复杂度：O(S + L)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {  // routes 是每条线路的站点序列，source 起点，target 终点
        if (source == target) {  // 起点就是终点，一次车都不用坐
            return 0;  // 乘车次数为 0
        }  // if 结束

        unordered_map<int, vector<int>> g;  // 反查表：站点 -> 经过该站点的所有线路编号
        for (int i = 0; i < routes.size(); i++) {  // 遍历每条线路
            for (int stop : routes[i]) {  // 遍历该线路经过的每个站点
                g[stop].push_back(i);  // 记录站点被哪条线路覆盖
            }  // for 结束
        }  // for 结束

        if (!g.contains(source) || !g.contains(target)) {  // 起点或终点没被任何线路覆盖，必然不可达
            return -1;  // 返回 -1
        }  // if 结束

        queue<pair<int, int>> q;  // BFS 队列：元素为「站点, 已乘坐的线路数」
        unordered_set<int> visBus;  // 线路是否已经坐过，避免重复扩展同一条线
        unordered_set<int> visStop;  // 站点是否已经到达过，避免重复入队
        q.push({source, 0});  // 从起点出发，已乘车 0 次
        visStop.insert(source);  // 起点标记为已访问

        while (!q.empty()) {  // 队列非空就继续按层扩展
            auto [stop, busCount] = q.front();  // 取出队首元素，并结构化绑定出站点与乘车数
            q.pop();  // 弹出队首

            if (stop == target) {  // 到达终点，当前乘车数就是最少乘车次数
                return busCount;  // 返回答案
            }  // if 结束

            for (int bus : g[stop]) {  // 枚举所有经过当前站点的线路
                if (!visBus.contains(bus)) {  // 这条线路还没坐过才需要扩展
                    visBus.insert(bus);  // 标记该线路已使用
                    for (int nextStop : routes[bus]) {  // 坐上这条线路可以直达的所有站点
                        if (!visStop.contains(nextStop)) {  // 新站点还没访问过
                            visStop.insert(nextStop);  // 标记站点已访问
                            q.push({nextStop, busCount + 1});  // 入队时乘车数加一
                        }  // if 结束
                    }  // for 结束
                }  // if 结束
            }  // for 结束
        }  // while 结束

        return -1;  // 队列空了还没到终点，说明不可达
    }  // 方法结束
};  // 类定义结束
