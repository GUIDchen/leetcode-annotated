// 题目：360. 有序转化数组（Sort Transformed Array）
// 思路：f(x)=ax²+bx+c 在有序数组上的值呈抛物线，两端必有一端是极值，用双指针从两端取较大/较小值填表。
// 时间复杂度：O(n)，双指针各走一遍；空间复杂度：O(n)，结果数组。
class Solution {  // LeetCode 题解类
public:  // 对外接口
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {  // nums 已升序；a、b、c 是二次函数系数
        int n = nums.size();  // 数组长度
        vector<int> ans(n);  // 预分配结果数组，后续按下标填值
        int i = 0, j = n - 1;  // 双指针：i 指向左端，j 指向右端

        auto f = [&](int x) {  // 定义二次函数 f(x) = a*x*x + b*x + c
            return a * x * x + b * x + c;  // 计算单个元素的转化结果
        };  // lambda 结束

        for (int k = 0; k < n; k++) {  // 共填 n 个位置
            int y1 = f(nums[i]);  // 左端元素转化值
            int y2 = f(nums[j]);  // 右端元素转化值
            if (a > 0) {  // 开口向上：最大值在两端，从后往前填
                if (y1 > y2) {  // 左端更大
                    ans[n - k - 1] = y1;  // 把较大值放到当前最大的空位
                    i++;  // 左端用掉，指针右移
                } else {  // 右端不小于左端
                    ans[n - k - 1] = y2;  // 把右端值放到当前最大空位
                    j--;  // 右端用掉，指针左移
                }  // 分支结束
            } else {  // 开口向下或退化为直线：最小值在两端，从前往后填
                if (y1 > y2) {  // 左端更大
                    ans[k] = y2;  // 较小值放前面
                    j--;  // 右端用掉
                } else {  // 右端不小于左端
                    ans[k] = y1;  // 左端较小，放前面
                    i++;  // 左端用掉
                }  // 分支结束
            }  // 开口方向判断结束
        }  // 填表结束
        return ans;  // 返回升序结果
    }  // 方法结束
};  // 题解类结束
