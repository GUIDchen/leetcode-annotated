// 题目：2586. 统计范围内的元音字符串数（Count the Number of Vowel Strings in Range）
// 思路：把 [left, right] 内的字符串逐个取出，检查首字母和尾字母是否都是元音字母，是则答案加一。
// 时间复杂度：O(right - left + 1)，每次检查常数时间；空间复杂度：O(1)，只用了固定几个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int vowelStrings(vector<string>& words, int left, int right) {  // words 为字符串数组，left/right 是闭区间端点
        auto check = [](char c) -> bool {  // 定义一个判断单字符是否元音的 lambda
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';  // 五个元音字母之一即为真
        };  // lambda 定义结束
        int ans = 0;  // 满足条件的字符串个数
        for (int i = left; i <= right; ++i) {  // 遍历区间内的每个下标
            auto w = words[i];  // 取出当前字符串（拷贝，便于下标访问）
            ans += check(w[0]) && check(w[w.size() - 1]);  // 首尾都是元音则加 1，否则加 0
        }
        return ans;  // 返回区间内元音字符串的数量
    }
};