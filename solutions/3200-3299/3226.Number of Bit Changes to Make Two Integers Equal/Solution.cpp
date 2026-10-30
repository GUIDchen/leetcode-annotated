// 题目：3226. 使两个整数相等的位更改次数（Number of Bit Changes to Make Two Integers Equal）
// 思路：只能把 1 改成 0，所以 k 中为 1 的位必须是 n 中为 1 的位的子集；可行时答案就是 n 与 k 异或结果中 1 的个数。
// 时间复杂度：O(log n)，与二进制位数成正比；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外公开
    int minChanges(int n, int k) {  // n：原数；k：目标数；返回最少位改动次数
        return (n & k) != k ? -1 : __builtin_popcount(n ^ k);  // (n & k) != k 说明 k 有 n 里没有的 1 位，无法只靠 1→0 达成，返回 -1；否则 __builtin_popcount(n ^ k) 就是需要改的位数
    }
};