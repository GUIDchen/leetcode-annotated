// 题目：779. 第K个语法符号（K-th Symbol in Grammar）
// 思路：第 n 行长度是 2^(n-1)，它的前半段与第 n-1 行完全相同、后半段是前半段逐位取反；先看 k 落在哪一半，落后半段就把对应前半段位置的结果取反。
// 时间复杂度：O(n)，每次把行号减一、问题规模减半；空间复杂度：O(n)，递归栈深度为 n。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int kthGrammar(int n, int k) {  // n：行号（从 1 开始）；k：该行第 k 个字符（从 1 开始）；返回 0 或 1
        if (n == 1) return 0;  // 第一行只有一个字符 0，递归到边界直接返回
        if (k <= (1 << (n - 2))) return kthGrammar(n - 1, k);  // 第 n 行前半段长度为 2^(n-2)；k 在前半段则与第 n-1 行第 k 个字符相同
        return kthGrammar(n - 1, k - (1 << (n - 2))) ^ 1;  // k 落在后半段：先映射回前半段的对应位置 k-2^(n-2)，再把结果异或 1 取反
    }  // kthGrammar 方法结束
};  // Solution 类定义结束