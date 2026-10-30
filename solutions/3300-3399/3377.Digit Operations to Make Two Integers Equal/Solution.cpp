// 题目：3377. 使两个整数相等的数位操作（Digit Operations to Make Two Integers Equal）
// 思路：先筛出 1e5 以内的质数（操作过程中不允许出现质数），把每个整数当节点、「某一位 +1 或 -1」当一条边（边权为目标数字），从 n 跑 Dijkstra，首次弹出 m 时的累计和即答案。
// 时间复杂度：O(V log V)，V = 1e5，每个点最多扩展 O(log V) 条边；空间复杂度：O(V)，用于质数表与访问集合。
class Solution {  // LeetCode 约定的题解类
private:  // 以下为内部辅助成员，只在类内使用
    vector<bool> sieve;  // 质数表：sieve[x] 为 true 表示 x 是质数，操作过程中禁止出现质数
    void runSieve() {  // 预处理 1e5 以内的质数（数据规模由题目给出）
        sieve.resize(100000, true);  // 先假设全部是质数，随后由筛法把合数改成 false
        sieve[0] = false, sieve[1] = false;  // 0 和 1 都不是质数，单独置 false
        for (int i = 2; i < 1e5; ++i) {  // 从最小的质数 2 开始枚举
            if (sieve[i]) {  // i 仍是质数，就用它去筛掉自己的倍数
                for (int j = 2 * i; j < 1e5; j += i) {  // 从 2i 开始，步长为 i，覆盖所有 i 的倍数
                    sieve[j] = false;  // i 的倍数一定是合数，标记为非质数
                }  // 筛除 i 的倍数结束
            }  // 枚举筛子结束
        }  // 外层循环结束
    }  // runSieve 方法结束
    int solve(int n, int m) {  // 在「非质数」构成的隐式图上求 n 到 m 的最小累计和
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;  // 小根堆，元素为 (累计和, 当前数字)，堆顶是累计和最小的状态
        unordered_set<int> vis;  // 已确定最短路的数字集合，用于 Dijkstra 的出堆去重
        pq.push({n, n});  // 起点入堆，累计和初始为 n 本身（每次操作会把新数字累加进和里）
        while (!pq.empty()) {  // 堆不空就继续扩展
            int sum = pq.top().first, cur = pq.top().second;  // 取出堆顶：sum 是走到 cur 的累计和，cur 是当前数字
            pq.pop();  // 弹出堆顶元素
            if (vis.find(cur) != vis.end()) continue;  // cur 之前已经出过堆，说明这是更差的旧记录，直接跳过
            vis.insert(cur);  // 第一次出堆即为最短路，标记已确定
            if (cur == m) return sum;  // 首次弹出 m，其累计和就是最小答案（Dijkstra 的贪心正确性）
            string s = to_string(cur);  // 把数字转成字符串，便于逐位修改
            for (int i = 0; i < s.size(); ++i) {  // 枚举要修改的位
                char c = s[i];  // 备份当前字符，改完这一位后要还原，才能继续尝试其他位
                if (s[i] < '9') {  // 这一位可以加一（小于 '9'，保证不进位、位数不变）
                    s[i]++;  // 该位字符加一，构造出下一个数字
                    int next = stoi(s);  // 字符串转回整数
                    if (!sieve[next] && vis.find(next) == vis.end()) {  // 新数字必须是合数（sieve 为 false）且还没有确定最短路
                        pq.push({sum + next, next});  // 边权就是新数字本身，累计和增加后入堆
                    }  // 合法性判断结束
                    s[i] = c;  // 还原该位，准备尝试减一
                }  // 加一分支结束
                if (s[i] > '0' && !(i == 0 && s[i] == '1')) {  // 可以减一：不能小于 '0'，且首位不能由 '1' 变成 '0'（否则少一位，成了另一个数）
                    s[i]--;  // 该位字符减一
                    int next = stoi(s);  // 字符串转回整数
                    if (!sieve[next] && vis.find(next) == vis.end()) {  // 同样要求新数字是合数且未访问
                        pq.push({sum + next, next});  // 累计和加上新数字后入堆
                    }  // 合法性判断结束
                    s[i] = c;  // 还原该位，供下一轮循环使用
                }  // 减一分支结束
            }  // 枚举位数结束
        }  // while 循环结束
        return -1;  // 堆空仍未到达 m，说明两点不可达
    }  // solve 方法结束

public:  // 对外暴露的解法接口
    int minOperations(int n, int m) {  // n：起点数字；m：目标数字
        runSieve();  // 先建好质数表，供后面 O(1) 查询
        if (sieve[n] || sieve[m]) return -1;  // 起点或终点本身是质数时，第一步就非法，直接判定不可达
        return solve(n, m);  // 在合数图上跑 Dijkstra 求最小操作和
    }  // minOperations 方法结束
};  // Solution 类定义结束
