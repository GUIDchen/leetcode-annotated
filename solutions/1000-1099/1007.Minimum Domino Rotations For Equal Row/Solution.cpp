// 题目：1007. 行相等的最少多米诺旋转（Minimum Domino Rotations For Equal Row）
// 核心思路：枚举第一张骨牌的上/下作为目标点数，统计最少旋转次数
// 复杂度：时间 O(n)，两种目标各扫一遍；空间 O(1)
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {  // tops/bottoms：每张骨牌的上、下两个点数
        int n = tops.size();  // n：骨牌张数
        auto f = [&](int x) {  // 局部函数 f：把某一行全部变成 x 所需的最少旋转次数
            int cnt1 = 0, cnt2 = 0;  // cnt1/cnt2：上下两行中本来就等于 x 的张数
            for (int i = 0; i < n; ++i) {  // 逐张检查骨牌
                if (tops[i] != x && bottoms[i] != x) {  // 两面都不是 x，说明这一行不可能全部变成 x
                    return n + 1;  // 返回一个大于 n 的哨兵值表示无解
                }  // 可行性检查结束
                cnt1 += tops[i] == x;  // 上面本来就等于 x 就计入 cnt1
                cnt2 += bottoms[i] == x;  // 下面本来就等于 x 就计入 cnt2
            }  // 所有骨牌检查完毕
            return n - max(cnt1, cnt2);  // 保留本来就较多的一面 x，需要旋转的张数就是 n 减去它
        };  // lambda 结束
        int ans = min(f(tops[0]), f(bottoms[0]));  // 能统一的那一行只可能是第一张骨牌的上或下，取两种目标的较优者
        return ans > n ? -1 : ans;  // 结果为哨兵值说明两种目标都无解，返回 -1
    }  // 方法结束
};  // 类定义结束