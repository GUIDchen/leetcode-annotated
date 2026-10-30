// 题目：871. 最低加油次数（Minimum Number of Refueling Stops）
// 思路：按距离顺序经过各站，先扣掉行驶所耗的油；油量不足时就用大根堆从「已经路过、但还没加油」的站里反复取油量最大的一桶补上，补不够即无法到达。
// 时间复杂度：O(n log n)，每桶油至多入堆、出堆各一次；空间复杂度：O(n)，堆里最多存 n 个站的油量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {  // target 是目标距离，startFuel 是初始油量，stations 按距离升序给出（位置, 油量）
        priority_queue<int> pq;  // 大根堆：存「已经路过、但还没决定加」的加油站油量，缺油时优先取最大的
        stations.push_back({target, 0});  // 在终点补一个油量为 0 的虚拟站，保证循环一定会遍历到终点
        int ans = 0, pre = 0;  // ans 记录加油次数，pre 记录上一个位置
        for (const auto& station : stations) {  // 按距离顺序经过每个站（含终点）
            int pos = station[0], fuel = station[1];  // 解构出当前站的位置与可加油量
            int dist = pos - pre;  // 从上一个位置到当前位置要消耗的油量
            startFuel -= dist;  // 先扣掉行驶这段距离所耗的油
            while (startFuel < 0 && !pq.empty()) {  // 油不够就回头从堆里补：每次加历史经过站里油量最大的那一桶
                startFuel += pq.top();  // 取出并加上最大的一桶油
                pq.pop();  // 这桶油已使用，从堆中弹出
                ++ans;  // 加油次数加一
            }
            if (startFuel < 0) {  // 补完所有能补的油仍不足以到达当前位置
                return -1;  // 说明无法抵达，返回 -1
            }
            pq.push(fuel);  // 把当前站的油放进堆里，先不加，等以后缺油时再来取
            pre = pos;  // 更新上一个位置，为下一段路程计算距离做准备
        }
        return ans;  // 走到终点后返回最少加油次数
    }
};  // 题解类定义结束
