// 3492. Maximum Containers on a Ship / 3492. 船上可以装载的最大集装箱数量
// 核心思路：甲板共有 n * n 个位置，满载总重量 n * n * w 与承重上限 maxWeight 取较小值，再按单箱重量 w 折算箱数。
// 复杂度：时间 O(1)，空间 O(1)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 判题器调用的公有方法
    int maxContainers(int n, int w, int maxWeight) {  // n 为甲板边长，w 为单箱重量，maxWeight 为总承重上限，返回最多能装的箱数
        return min(n * n * w, maxWeight) / w;  // 满载总重量与实际承重上限取较小者，再除以单箱重量得到箱数
    }  // 方法结束
};  // 类定义结束
