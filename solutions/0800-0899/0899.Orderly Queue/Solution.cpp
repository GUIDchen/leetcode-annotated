// 题目：899. 有序队列（Orderly Queue）
// 核心思路：k == 1 时只能把首字符搬到末尾，枚举所有循环移位取字典序最小；k >= 2 时可等价于任意交换，直接排序。
// 时间复杂度：k == 1 时 O(n^2)，k >= 2 时 O(n log n)；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string orderlyQueue(string s, int k) {  // s：输入字符串；k：每次可移动的字符数
        if (k == 1) {  // 只能做循环移位，答案是所有移位中最小的那一个
            string ans = s;  // 用原串作为当前最优解
            for (int i = 0; i < s.size() - 1; ++i) {  // 一共只有 n 种不同的循环移位
                s = s.substr(1) + s[0];  // 把首字符搬到最后，得到下一个循环移位
                if (s < ans) ans = s;  // 字典序更小就更新答案
            }  // 返回最小的循环移位
            return ans;
        }  // k >= 2 时可以交换任意两个字符，直接升序排列
        sort(s.begin(), s.end());  // 排序结果即最小字典序
        return s;
    }
};