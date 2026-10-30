// 题目：2614. 对角线上的质数（Prime In Diagonal）
// 思路：枚举每一行，同时取出主对角线元素 nums[i][i] 与副对角线元素 nums[i][n-1-i]，用试除法判质数并取最大值。
// 时间复杂度：O(n * sqrt(V))，V 为矩阵中的最大数；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int diagonalPrime(vector<vector<int>>& nums) {  // nums 是 n x n 矩阵；返回两条对角线上最大的质数，没有则返回 0
        int n = nums.size();  // 矩阵边长
        int ans = 0;  // 记录目前找到的最大质数，0 表示还没找到
        for (int i = 0; i < n; ++i) {  // 每行取主对角线一个元素、副对角线一个元素
            if (isPrime(nums[i][i])) {  // 主对角线：行下标等于列下标
                ans = max(ans, nums[i][i]);  // 是质数就尝试更新答案
            }  // 主对角线判断结束
            if (isPrime(nums[i][n - i - 1])) {  // 副对角线：列下标为 n - 1 - i
                ans = max(ans, nums[i][n - i - 1]);  // 是质数就尝试更新答案
            }  // 副对角线判断结束
        }  // 逐行枚举结束
        return ans;  // 没有任何质数时自然返回 0
    }  // 方法结束

    bool isPrime(int x) {  // 试除法判断质数
        if (x < 2) {  // 0、1 与负数都不是质数
            return false;  // 直接判否
        }  // 特判结束
        for (int i = 2; i <= x / i; ++i) {  // 只需枚举到 sqrt(x)；写成 i <= x / i 可避免 i * i 溢出
            if (x % i == 0) {  // 找到了真因子
                return false;  // 说明 x 不是质数
            }  // 真因子分支结束
        }  // 试除结束
        return true;  // 没有找到因子，x 是质数
    }  // 判质数函数结束
};  // 题解类结束