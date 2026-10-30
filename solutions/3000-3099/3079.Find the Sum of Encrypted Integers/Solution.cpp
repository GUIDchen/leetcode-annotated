// 题目：3079. 求出加密整数的和（Find the Sum of Encrypted Integers）
// 思路：对每个数求各位数字的最大值 mx，再用同位数全 1 数 p 把 mx 复制满，累加所有加密结果。
// 时间复杂度：O(n·log10 M)，每个数按位处理一次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumOfEncryptedInt(vector<int>& nums) {  // nums：待加密的整数数组，返回所有加密整数之和
        auto encrypt = [&](int x) {  // 局部 lambda：把单个整数 x 按题意加密
            int mx = 0, p = 0;  // mx 记录各位数字的最大值；p 生成与位数等长的全 1 数（1、11、111…）
            for (; x; x /= 10) {  // 逐位取出 x 的每一位，每轮把 x 除以 10
                mx = max(mx, x % 10);  // x % 10 是当前最低位，用它更新最大数字
                p = p * 10 + 1;  // 每多处理一位就让 p 扩展成 11…1，用于把最大数字复制满所有数位
            }
            return mx * p;  // 加密结果：最大数字重复与原数相同的位数
        };
        int ans = 0;  // 累加所有加密后的整数
        for (int x : nums) {  // 遍历数组中的每个整数
            ans += encrypt(x);  // 把当前整数的加密值累加到答案
        }
        return ans;  // 返回加密整数之和
    }
};