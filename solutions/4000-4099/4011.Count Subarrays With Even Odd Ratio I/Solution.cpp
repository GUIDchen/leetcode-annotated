// 题目：4011. 按奇偶比统计子数组 I（Count Subarrays With Even Odd Ratio I）
// 思路：枚举左端点并向右扩张右端点，实时维护子数组中的奇数个数 y 与偶数个数 x；用交叉相乘 x * b <= y * a 判断 x / y <= a / b，避免浮点误差。
// 时间复杂度：O(n^2)，枚举了所有子数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countRatioSubarrays(vector<int>& nums, int a, int b) {  // nums：待统计的数组；a、b：偶数个数与奇数个数比值的上界 a / b；返回满足条件的子数组个数
        int n = nums.size();  // n 为数组长度
        long long ans = 0;  // ans 记录满足条件的子数组个数（可能超过 int 范围，用 long long）

        for (int i = 0; i < n; i++) {  // 枚举子数组的左端点 i
            int y = 0;  // y 记录当前子数组中奇数的个数

            for (int j = i; j < n; j++) {  // 右端点从 i 起逐步右移，枚举所有以 i 开头的子数组
                y += nums[j] % 2;  // 当前元素为奇数则 y 加 1（取模 2 得 0 或 1）
                int x = j - i + 1 - y;  // 偶数个数 = 子数组长度 - 奇数个数

                if (y > 0 && 1LL * x * b <= 1LL * y * a) {  // 交叉相乘比较 x / y <= a / b，避免浮点除法；y > 0 保证分母不为零
                    ans++;  // 满足比例条件，计数加 1
                }  // 结束比例判断
            }  // 结束右端点枚举
        }  // 结束左端点枚举

        return ans;  // 返回满足条件的子数组总数
    }  // 结束 countRatioSubarrays
};  // 结束 Solution 类