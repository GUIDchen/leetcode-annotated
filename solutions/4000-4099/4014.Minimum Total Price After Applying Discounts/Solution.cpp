// 题目：4014. 应用折扣后的最低总价（Minimum Total Price After Applying Discounts）
// 思路：价格数组与折扣数组都升序排序，用双指针分别从最贵的商品和最大的折扣开始反向配对——折扣是按比例的，越大折扣用在越贵的商品上省得越多，剩余商品原价支付，该贪心即为最优。
// 时间复杂度：O(n log n + m log m)，主要开销是两次排序；空间复杂度：O(1)，只用常数个指针与累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double minPrice(vector<int>& prices, vector<int>& discounts) {  // prices：每件商品的价格；discounts：可用的折扣百分比；返回所有商品最终价格之和的最小值
        sort(prices.begin(), prices.end());  // 价格升序排序，便于从最贵的商品入手
        sort(discounts.begin(), discounts.end());  // 折扣升序排序，配合后面从尾部取最大折扣

        int i = prices.size() - 1;  // i 指向当前最贵的未处理商品（原下标范围 0..size-1）
        int j = discounts.size() - 1;  // j 指向当前最大的未使用折扣

        double ans = 0;  // ans 累计最小总价，用 double 保存，最终价格不四舍五入

        while (i >= 0 && j >= 0) {  // 商品与折扣都还没用完时，把最大折扣用在最贵的商品上
            ans += prices[i] * (100 - discounts[j]) / 100.0;  // 打 d% 折扣后的价格 = p * (100 - d) / 100，除以 100.0 保证是浮点除法
            i--;  // 该商品处理完，指针前移
            j--;  // 该折扣已用掉，指针前移
        }  // 双指针配对循环结束

        while (i >= 0) {  // 折扣用完，剩下的商品一律原价支付
            ans += prices[i];  // 原价计入总价
            i--;  // 处理下一个更便宜的商品
        }  // 剩余商品处理完毕

        return ans;  // 返回所有商品最终价格之和的最小值
    }  // 方法结束
};  // 类定义结束