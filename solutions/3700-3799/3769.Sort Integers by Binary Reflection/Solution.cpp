// 3769. 二进制反射排序 / Sort Integers by Binary Reflection
// 核心思路：先算出每个数的二进制反射值，再以 (反射值, 原数值) 为双关键字升序排序。
// 复杂度：时间 O(n log n · log V)，空间 O(log n)（排序递归栈）。
class Solution {  // 定义解法类
public:  // 公有方法区
    vector<int> sortByReflection(vector<int>& nums) {  // 按二进制反射值排序并返回数组
        auto f = [](int x) {  // 定义反射值计算 lambda
            int y = 0;  // 反射结果
            while (x) {  // 逐位取出最低位
                y = (y << 1) | (x & 1);  // 把最低位接到结果的最低位上，实现位序反转
                x >>= 1;  // 原数右移一位
            }
            return y;  // 返回反射值
        };

        sort(nums.begin(), nums.end(), [&](int a, int b) {  // 以反射值为第一关键字排序
            int fa = f(a);  // a 的反射值
            int fb = f(b);  // b 的反射值
            if (fa != fb) {  // 反射值不同时按反射值升序
                return fa < fb;  // 反射值小的排在前面
            }
            return a < b;  // 反射值相同时按原数值升序
        });

        return nums;  // 返回排序后的数组
    }  // 方法结束
};  // 类结束
