// 题目：365. 水壶问题（Water and Jug Problem）
// 思路：把 (i, j) 两壶水量当作状态做 DFS，枚举装满、倒空、互相倒六种转移，用哈希集合去重，任一状态达到 z 即可行。
// 时间复杂度：O(x·y)，状态数上限；空间复杂度：O(x·y)，访问集合与栈。
class Solution {  // LeetCode 题解类
public:  // 对外接口
    bool canMeasureWater(int x, int y, int z) {  // 两壶容量分别为 x、y，目标是量出水量 z
        using pii = pair<int, int>;  // 用 (i, j) 表示两壶当前水量
        stack<pii> stk;  // DFS 栈，保存待扩展的状态
        stk.emplace(0, 0);  // 初始状态：两壶都为空
        auto hash_function = [](const pii& o) { return hash<int>()(o.first) ^ hash<int>()(o.second); };  // 自定义哈希：把两个分量的哈希异或
        unordered_set<pii, decltype(hash_function)> vis(0, hash_function);  // 访问集合去重，防止状态重复展开
        while (stk.size()) {  // 栈非空就继续搜索
            auto st = stk.top();  // 取栈顶状态
            stk.pop();  // 出栈
            if (vis.count(st)) {  // 该状态已经访问过
                continue;  // 跳过，避免重复展开
            }  // 判断结束
            vis.emplace(st);  // 标记为已访问
            auto [i, j] = st;  // 结构化绑定取出两壶水量
            if (i == z || j == z || i + j == z) {  // 任一壶或两壶合计等于目标即可
                return true;  // 找到可行方案
            }  // 判断结束
            stk.emplace(x, j);  // 操作一：装满第一壶
            stk.emplace(i, y);  // 操作二：装满第二壶
            stk.emplace(0, j);  // 操作三：倒空第一壶
            stk.emplace(i, 0);  // 操作四：倒空第二壶
            int a = min(i, y - j);  // 第一壶能倒进第二壶的水量
            int b = min(j, x - i);  // 第二壶能倒进第一壶的水量
            stk.emplace(i - a, j + a);  // 操作五：第一壶倒向第二壶
            stk.emplace(i + b, j - b);  // 操作六：第二壶倒向第一壶
        }  // 搜索结束
        return false;  // 所有可达状态都试过仍无解
    }  // 方法结束
};  // 题解类结束