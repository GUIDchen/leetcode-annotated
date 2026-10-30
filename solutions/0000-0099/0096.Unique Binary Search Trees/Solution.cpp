// 题目：96. 不同的二叉搜索树（Unique Binary Search Trees）
// 思路：卡特兰数 DP，f[i] 表示 i 个结点的 BST 种数；枚举根的位置 j，左 j 个、右 i-j-1 个，方案数相乘后累加。
// 时间复杂度：O(n^2)，双重循环枚举；空间复杂度：O(n)，一维 DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numTrees(int n) {  // n 是结点个数，返回不同结构的 BST 数量
        vector<int> f(n + 1);  // f[i]：i 个结点能组成的 BST 种数，默认初始化为 0
        f[0] = 1;  // 边界：空树算 1 种，乘法累加的基准
        for (int i = 1; i <= n; ++i) {  // 依次计算结点数为 1..n 的答案
            for (int j = 0; j < i; ++j) {  // j 是左子树的结点数，则右子树有 i-j-1 个
                f[i] += f[j] * f[i - j - 1];  // 左右子树方案数相乘，对所有根的划分求和
            }
        }
        return f[n];  // n 个结点的种数即答案
    }
};
