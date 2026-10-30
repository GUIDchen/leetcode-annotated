// 题目：3115. 质数的最大距离（Maximum Prime Difference）
// 思路：先从左往右找到第一个质数，再从右往左找到最后一个质数，两个下标之差就是最大距离。
// 时间复杂度：O(n·√V)，最坏要扫完整个数组并对每个数试除到 √V；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumPrimeDifference(vector<int>& nums) {  // nums：输入数组；返回第一个与最后一个质数的下标之差
        for (int i = 0;; ++i) {  // 从左往右找第一个质数，题目保证至少两个质数，故循环可不写上界
            if (isPrime(nums[i])) {  // 找到一个质数，它就是最左边的质数
                for (int j = nums.size() - 1;; --j) {  // 固定左端点后，从最右端往左找最右边的质数
                    if (isPrime(nums[j])) {  // 找到最右侧的质数
                        return j - i;  // 两个下标之差即为答案
                    }  // 结束最右质数判断
                }  // 结束从右往左的扫描
            }  // 结束最左质数判断
        }  // 结束从左往右的扫描
    }  // 结束 maximumPrimeDifference

    bool isPrime(int n) {  // 辅助函数：试除法判断 n 是否为质数
        if (n < 2) {  // 0、1 和负数都不是质数
            return false;  // 直接返回假
        }  // 结束小值判断
        for (int i = 2; i <= n / i; ++i) {  // 只需试除到 √n，写成 i <= n / i 可避免 i * i 溢出
            if (n % i == 0) {  // 找到一个因子，说明 n 不是质数
                return false;  // 提前返回假
            }  // 结束因子判断
        }  // 结束试除循环
        return true;  // 没有因子，n 是质数
    }  // 结束 isPrime
};  // 类定义结束