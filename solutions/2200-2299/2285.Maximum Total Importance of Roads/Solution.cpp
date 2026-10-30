// 题目：2285. 道路的最大总重要性（Maximum Total Importance of Roads）
// 核心思路：总重要性等于每条道路两端城市重要性之和，等价于每个城市的重要性乘它的度数；度数越大给越大的值，故把度数升序后依次乘 1..n 求和。
// 时间复杂度：O(E + n log n)，E 为道路数，主要开销是排序 n 个度数；空间复杂度：O(n)，存放各城市度数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumImportance(int n, vector<vector<int>>& roads) {  // n：城市个数；roads：无向道路列表；返回最大总重要性
        vector<int> deg(n);  // deg[i] 记录城市 i 的度数（与它相连的道路条数），初始全为 0
        for (auto& r : roads) {  // 遍历每条道路，为两端城市各累加一次度数
            ++deg[r[0]];  // 道路起点城市度数 +1
            ++deg[r[1]];  // 道路终点城市度数 +1
        }  // 度数统计完毕
        sort(deg.begin(), deg.end());  // 度数升序排序，好让度数大的城市拿到更大的重要性
        long long ans = 0;  // 累加总重要性，用 long long 防止乘加溢出
        for (int i = 0; i < n; ++i) {  // 按度数从小到大，依次分配重要性 1, 2, ..., n
            ans += (i + 1LL) * deg[i];  // 第 i 小的度数配重要性 i+1，乘积累加；1LL 保证按 64 位整数计算
        }  // 累加结束
        return ans;  // 返回最大总重要性
    }  // 方法结束
};  // 类定义结束