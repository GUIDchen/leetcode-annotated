// 题目：942. 增减字符串匹配（DI String Match）
// 思路：用双指针维护可选数字区间 [low, high]；遇到 'I' 就取当前最小值（后面一定还有更大的数），遇到 'D' 就取当前最大值，最后剩下的数填到末尾。
// 时间复杂度：O(n)，只遍历一次字符串；空间复杂度：O(n)，需要长度为 n+1 的答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> diStringMatch(string s) {  // s 是由 'I'/'D' 组成的字符串，返回满足增减关系的 0..n 的排列
        int n = s.size();  // 字符串长度 n，答案数组长度为 n + 1
        int low = 0, high = n;  // 可选数字区间 [low, high]，初始恰好覆盖 0..n
        vector<int> ans(n + 1);  // 预分配答案数组，长度比 s 多一个
        for (int i = 0; i < n; ++i) {  // 逐个处理每个趋势字符
            if (s[i] == 'I') {  // 'I' 表示下一个位置的数要更大
                ans[i] = low++;  // 填当前最小值，剩余数字都比它大，必然能满足 'I'
            } else {  // 否则是 'D'，下一个位置的数要更小
                ans[i] = high--;  // 填当前最大值，剩余数字都比它小，必然能满足 'D'
            }
        }
        ans[n] = low;  // 最后只剩一个数字（此时 low == high），填到数组末尾
        return ans;  // 返回构造好的排列
    }
};  // 类定义结束