// 题目：1431. 拥有最多糖果的孩子（Kids With the Greatest Number of Candies）
// 思路：先用 max_element 求原有糖果数的最大值，再逐个判断加上额外糖果后能否达到它。
// 时间复杂度：O(n)，两遍扫描；空间复杂度：O(n)，存放返回的 bool 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {  // candies：每个孩子已有的糖果数；extraCandies：可额外给的糖果数
        int mx = *max_element(candies.begin(), candies.end());  // 第一遍扫描：求所有孩子糖果数的最大值
        vector<bool> res;  // res 按输入顺序保存每个孩子能否成为最多之一
        for (int candy : candies) {  // 第二遍扫描：逐个判断
            res.push_back(candy + extraCandies >= mx);  // 加上额外糖果后不小于原最大值，该位置为 true
        }  // 循环结束
        return res;  // 返回结果数组
    }  // 方法结束
};  // 类定义结束