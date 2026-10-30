// 题目：2579. 统计染色格子数（Count Total Number of Colored Cells）
// 思路：第 i 圈比上一圈多 4(i-1) 个格子，累加后通项为 2n(n-1)+1，直接套公式。
// 时间复杂度：O(1)，只有一次乘加运算；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long coloredCells(int n) {  // n 表示第几圈，返回染色格子总数
        return 2LL * n * (n - 1) + 1;  // 第 i 圈新增 4(i-1) 个格子，累加得通项 2n(n-1)+1；写 2LL 让中间结果用 64 位，避免 n 较大时 int 溢出
    }
};