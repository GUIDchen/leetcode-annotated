// 题目：477. 汉明距离总和（Total Hamming Distance）
// 思路：逐位统计。第 i 位上若有 a 个数为 1、b 个数为 0，则这一位对总距离的贡献就是 a*b（一 0 一 1 的配对都会产生一次差异）。
// 时间复杂度：O(32n)，即 O(n)，每个数只被扫描 32 次；空间复杂度：O(1)，只用若干计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int totalHammingDistance(vector<int>& nums) {  // nums 是给定的整数数组，返回两两汉明距离之和
        int ans = 0, n = nums.size();  // ans 累加答案，n 是元素个数
        for (int i = 0; i < 32; ++i) {  // 依次处理二进制的第 0~31 位
            int a = 0;  // a 记录当前位上 1 的个数
            for (int x : nums) {  // 遍历所有数字
                a += x >> i & 1;  // 取出 x 的第 i 位，是 1 就让 a 加一
            }
            int b = n - a;  // b 是当前位上 0 的个数
            ans += a * b;  // 这一位的贡献 = 1 的个数 × 0 的个数
        }
        return ans;  // 32 位贡献之和即总汉明距离
    }
};