// 题目：789. 逃脱阻碍者（Escape The Ghosts）
// 思路：从 (0,0) 到 target 的曼哈顿距离是固定下界；只要有阻碍者的距离不超过我，它就必然能先到或拦截，否则一定能逃脱。
// 时间复杂度：O(g)，g 为阻碍者数量；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {  // ghosts 是阻碍者坐标列表，target 是目的地；返回能否安全到达
        int tx = target[0], ty = target[1];  // 拆出目的地的横纵坐标
        for (auto& g : ghosts) {  // 逐个比较每个阻碍者
            int x = g[0], y = g[1];  // 取出当前阻碍者的横纵坐标
            if (abs(tx - x) + abs(ty - y) <= abs(tx) + abs(ty)) {  // 它到目的地的曼哈顿距离 <= 我从 (0,0) 到目的地的距离
                return false;  // 它必然能先到或在路上拦截，无法逃脱
            }  // 分支结束
        }  // 比较循环结束
        return true;  // 所有阻碍者都更远，沿最短路径走即可安全到达
    }  // 方法结束
};  // 题解类结束