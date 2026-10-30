// 题目：3238. 求出胜利玩家的数目（Find the Number of Winning Players）
// 思路：二维计数表统计「玩家 → 颜色」的拿球次数，一旦某颜色的次数严格大于玩家编号，就把该玩家记为胜利者，用集合去重。
// 时间复杂度：O(k)，k 为 pick 的长度；空间复杂度：O(1)，计数表固定为 10×11。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int winningPlayerCount(int n, vector<vector<int>>& pick) {  // n：玩家个数（其中 n-1 是最大编号）；pick：每次捡球的 [玩家编号, 颜色] 记录
        int cnt[10][11]{};  // cnt[x][y] 是玩家 x 拿到颜色 y 的球数；玩家最多 10 个、颜色取值 0~10，定长数组就够
        unordered_set<int> s;  // s 存放胜利玩家编号，用集合自动去重
        for (const auto& p : pick) {  // 逐个遍历捡球记录
            int x = p[0], y = p[1];  // 拆出玩家编号 x 与颜色 y
            if (++cnt[x][y] > x) {  // 先自增再比较：某颜色的数量严格大于玩家编号即满足获胜条件
                s.insert(x);  // 把该玩家编号放进集合重复也不会重复计数
            }  // if 结束
        }  // for 结束
        return s.size();  // 集合大小就是胜利玩家的个数
    }  // 方法结束
};  // 类结束
