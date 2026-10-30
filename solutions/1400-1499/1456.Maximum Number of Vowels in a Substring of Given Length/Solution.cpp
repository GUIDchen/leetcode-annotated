// 题目：1456. 定长子串中元音的最大数目（Maximum Number of Vowels in a Substring of Given Length）
// 思路：滑动窗口，先统计首个长度 k 窗口内的元音数，之后每次右移一位，加上新进窗口的字符、减去移出窗口的字符，边滑动边取最大值。
// 时间复杂度：O(n)，每个字符最多进、出窗口各一次；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxVowels(string s, int k) {  // s：原字符串；k：固定窗口长度
        auto isVowel = [](char c) {  // 局部 lambda：判断一个字符是不是元音
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';  // 是 a、e、i、o、u 之一就返回 true（C++ 中 bool 参与运算时按 1/0 计）
        };  // lambda 定义结束
        int cnt = count_if(s.begin(), s.begin() + k, isVowel);  // count_if 统计第一个长度为 k 的窗口里有多少个元音
        int ans = cnt;  // 答案先记为第一个窗口的元音数
        for (int i = k; i < s.size(); ++i) {  // i 是窗口右端点，从 k 开始每次右移一格，直到字符串末尾
            cnt += isVowel(s[i]) - isVowel(s[i - k]);  // 加 1 表示新字符是元音，减 1 表示被移出窗口的字符是元音，用加减抵消实现 O(1) 更新
            ans = max(ans, cnt);  // 与当前答案比较，保留更大值
        }  // for 循环体结束
        return ans;  // 返回任意长度 k 子串中元音数目的最大值
    }  // 方法体结束
};  // 类定义结束