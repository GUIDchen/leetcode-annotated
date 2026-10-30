// 题目：1686. 石子游戏 VI（Stone Game VI）
// 思路：按「Alice 得分 + Bob 得分」降序排出取石顺序，双方轮流取当前收益和最大的石子，累计两人总分后比较大小。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，额外的 (得分和, 下标) 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {  // aliceValues：Alice 取该石子的得分；bobValues：Bob 取该石子的得分
        vector<pair<int, int>> vals;  // 存放 (双方得分之和, 原下标)，排序后还能还原原始得分
        int n = aliceValues.size();  // 石子个数
        for (int i = 0; i < n; ++i) {  // 逐颗石子构造配对
            vals.emplace_back(aliceValues[i] + bobValues[i], i);  // 两得分之和代表这颗石子的「总收益」，同时记下原下标 i
        }  // 构造循环结束
        sort(vals.rbegin(), vals.rend());  // 按收益和降序排序：rbegin/rend 是反向迭代器
        int a = 0, b = 0;  // a：Alice 累计得分；b：Bob 累计得分
        for (int k = 0; k < n; ++k) {  // 按排序后的顺序轮流取石子
            int i = vals[k].second;  // 还原该配对在原数组中的下标
            if (k % 2 == 0) {  // 第 0、2、4… 颗（偶数下标）由先手 Alice 取走
                a += aliceValues[i];  // Alice 得到 aliceValues[i]
            } else {  // 第 1、3、5… 颗（奇数下标）由后手 Bob 取走
                b += bobValues[i];  // Bob 得到 bobValues[i]
            }  // 分支结束
        }  // 轮流取石循环结束
        if (a == b) {  // 两人总分相同即平局
            return 0;  // 平局返回 0
        }  // 平局分支结束
        return a > b ? 1 : -1;  // Alice 分高返回 1，否则返回 -1
    }  // 方法结束
};  // 类结束