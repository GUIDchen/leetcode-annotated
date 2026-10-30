// 题目：1051. 高度检查器（Height Checker）
// 思路：把数组拷贝一份升序排序得到期望排列，再与当前排列逐位比较，统计不相等的位置个数。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n)，保存期望排列的副本。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int heightChecker(vector<int>& heights) {  // heights：当前排列；返回与「非递减顺序」不一致的下标个数
        vector<int> expected = heights;  // 拷贝一份作为期望排列，避免破坏输入
        sort(expected.begin(), expected.end());  // 升序排序即题目要求的期望顺序
        int ans = 0;  // 统计不匹配的位置个数
        for (int i = 0; i < heights.size(); ++i) {  // 逐位比较
            ans += heights[i] != expected[i];  // 布尔值只有 0/1，可以直接累加到答案里
        }  // 比较循环结束
        return ans;  // 需要调整的位置数量
    }  // 方法结束
};  // 题解类结束