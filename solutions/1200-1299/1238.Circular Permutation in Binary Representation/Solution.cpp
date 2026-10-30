// 题目：1238. 循环码排列（Circular Permutation in Binary Representation）
// 思路：先求出 2^n 个格雷码 g[i] = i ^ (i >> 1)，相邻格雷码只差一位；再从 start 所在下标开始环状取完所有数即可。
// 时间复杂度：O(2^n)，生成与输出各一遍；空间复杂度：O(2^n)，格雷码数组与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> circularPermutation(int n, int start) {  // n 是二进制位数，start 是要求的起点，返回首尾也相邻的循环排列
        int g[1 << n];  // 格雷码数组：g[i] = i ^ (i >> 1)，相邻两项恰好只差一位比特
        int j = 0;  // j 用来记录 start 在格雷码数组中的下标
        for (int i = 0; i < 1 << n; ++i) {  // 生成全部 2^n 个格雷码
            g[i] = i ^ (i >> 1);  // 经典格雷码公式：i 异或 i 右移一位
            if (g[i] == start) {  // 定位题目要求的起点 start
                j = i;  // 记下它的下标，后面从这里开始取
            }  // if 结束
        }  // for 结束
        vector<int> ans;  // 按题目要求的顺序收集答案
        for (int i = j; i < j + (1 << n); ++i) {  // 从 j 开始环状取 2^n 个数（越过末尾就绕回开头）
            ans.push_back(g[i % (1 << n)]);  // 取模 (1 << n) 实现循环下标
        }  // for 结束
        return ans;  // 返回循环排列
    }  // 方法结束
};  // 类定义结束