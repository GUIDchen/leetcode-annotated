// 题目：575. 分糖果（Distribute Candies）
// 核心思路：妹妹最多拿一半（n/2）颗，而糖果种类数决定她最多尝到多少种，答案是两者的较小值。
// 时间复杂度：O(n)，构建哈希集合一次遍历；空间复杂度：O(n)，集合最多存 n 个不同种类。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int distributeCandies(vector<int>& candyType) {  // candyType 是每种糖果的类型编号
        unordered_set<int> s(candyType.begin(), candyType.end());  // 用集合去重，集合大小就是不同种类数
        return min(candyType.size() >> 1, s.size());  // 妹妹最多拿一半（右移一位等于除以 2），取「一半」与「种类数」的较小值
    }  // distributeCandies 结束
};  // 类定义结束（源文件末尾无换行，此处保持原样）