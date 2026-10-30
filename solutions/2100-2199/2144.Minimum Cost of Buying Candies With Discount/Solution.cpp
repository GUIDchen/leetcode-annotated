// 题目：2144. 打折购买糖果的最小开销（Minimum Cost of Buying Candies With Discount）
// 思路：降序排序后每 3 颗为一组，组内第 3 贵的那颗免费，因此累加每组下标为 0、3、6… 与其后一位的价格。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(1)，只用了常数个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumCost(vector<int>& cost) {  // cost：每颗糖果的价格列表
        sort(cost.rbegin(), cost.rend());  // 原地降序排序：让免费的总是每组里最便宜的那颗
        int ans = 0;  // 累计需要支付的总额
        for (int i = 0; i < cost.size(); i += 3) {  // 每 3 颗一组，i 是每组最贵那颗的下标
            ans += cost[i];  // 每组第 1 贵的糖果必须付钱
            if (i < cost.size() - 1) {  // 判断本组是否还存在第 2 颗（最后一组可能不足 3 颗）
                ans += cost[i + 1];  // 第 2 贵的糖果也要付钱
            }
        }
        return ans;  // 返回最小总开销
    }
};  // 类定义结束