// 3411. 最长乘积等价子数组 / Maximum Subarray With Equal Products
// 核心思路：枚举子数组，用乘积 == gcd * lcm 判定等价，并以全局 lcm*max 作为乘积上界提前剪枝。
// 复杂度：时间复杂度 O(n^2 log V)，空间复杂度 O(1)，V 为元素最大值。
class Solution {  // 题解类定义
public:  // 公有接口
    int maxLength(vector<int>& nums) {  // 求满足乘积等于 gcd*lcm 的最长子数组长度
        int mx = 0, ml = 1;  // mx 为全局最大值，ml 为全局最小公倍数
        for (int x : nums) {  // 遍历所有元素
            mx = max(mx, x);  // 更新最大值
            ml = lcm(ml, x);  // 更新最小公倍数
        }  // 结束预处理

        long long maxP = (long long) ml * mx;  // 乘积上界：全局最小公倍数乘最大值，超过它必然不满足等式
        int n = nums.size();  // 数组长度
        int ans = 0;  // 答案
        for (int i = 0; i < n; ++i) {  // 枚举子数组左端点
            long long p = 1, g = 0, l = 1;  // p 为乘积，g 为 gcd，l 为 lcm
            for (int j = i; j < n; ++j) {  // 枚举子数组右端点
                p *= nums[j];  // 累乘
                g = gcd(g, nums[j]);  // 更新最大公约数
                l = lcm(l, nums[j]);  // 更新最小公倍数

                if (p == g * l) {  // 满足乘积等于 gcd*lcm
                    ans = max(ans, j - i + 1);  // 更新最长长度
                }  // 结束等式判断
                if (p > maxP) {  // 乘积已超过上界
                    break;  // 继续扩展只会更大，提前剪枝
                }  // 结束剪枝判断
            }  // 结束右端点循环
        }  // 结束左端点循环
        return ans;  // 返回最长长度
    }  // 结束 maxLength
};  // 结束题解类
