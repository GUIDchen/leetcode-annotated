// 题目：1103. 分糖果 II（Distribute Candies to People）
// 思路：按 1,2,3,... 递增发放，用下标对人数取模循环，剩余不足时把剩下的全给当前人。
// 时间复杂度：O(√candies + n)，第 i 轮已发 i(i+1)/2 颗；空间复杂度：O(n)，答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> distributeCandies(int candies, int num_people) {  // candies：糖果总数；num_people：人数
        vector<int> ans(num_people);  // 答案数组，下标 i 对应第 i + 1 个人，初始都是 0
        for (int i = 0; candies > 0; ++i) {  // i 表示第 i + 1 轮要发 i + 1 颗；糖果发完就停止
            ans[i % num_people] += min(candies, i + 1);  // 下标对人数取模实现循环发放；min 保证最后一轮不足时只发剩下的
            candies -= min(candies, i + 1);  // 扣掉刚发出去的糖果
        }  // for 结束
        return ans;  // 返回每个人的糖果数
    }  // 方法结束
};  // 类定义结束