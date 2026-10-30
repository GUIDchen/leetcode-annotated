// 题目：2145. 统计隐藏数组数目（Count the Hidden Sequences）
// 思路：隐藏数组的每一项都等于首项 a 加上差分的前缀和，于是 a 必须落在 [lower-mi, upper-mx] 内，区间长度即答案。
// 时间复杂度：O(n)，只遍历一次差分数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfArrays(vector<int>& differences, int lower, int upper) {  // differences：相邻元素之差；lower/upper：元素取值范围
        long long x = 0, mi = 0, mx = 0;  // x：前缀和（即相对首项的偏移）；mi/mx：前缀和的最小值与最大值，用 long long 防溢出
        for (int d : differences) {  // 依次遍历每个差分值
            x += d;  // 累加差分，得到下一个前缀和
            mi = min(mi, x);  // 维护前缀和的最小值
            mx = max(mx, x);  // 维护前缀和的最大值
        }
        return max(upper - lower - (mx - mi) + 1, 0LL);  // 合法首项个数 = 值域长度 - 偏移极差 + 1，负数说明无解取 0
    }
};  // 类定义结束
