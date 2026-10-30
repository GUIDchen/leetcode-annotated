// 题目：744. 寻找比目标字母大的最小字母（Find Smallest Letter Greater Than Target）
// 核心思路：letters 已按升序排列，用 upper_bound 二分出第一个严格大于 target 的位置，再取模让越界时绕回首字母。
// 时间复杂度：O(log n)，一次二分查找；空间复杂度：O(1)，只用了下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    char nextGreatestLetter(vector<char>& letters, char target) {  // letters：升序字符数组；target：要比较的目标字母
        int i = upper_bound(letters.begin(), letters.end(), target) - letters.begin();  // 二分找第一个严格大于 target 的位置，减去 begin 得到 0 起始下标
        return letters[i % letters.size()];  // i 等于长度说明没有更大的字母，取模后回到 letters[0]（题目保证循环）
    }  // 结束 nextGreatestLetter 方法
};  // 结束 Solution 类