// 题目：2901. 最长相邻不相等子序列 II（Longest Unequal Adjacent Groups Subsequence II）
// 思路：动态规划，f[i] 表示以 i 结尾的最长合法链长，转移要求分组不同且两词只差一个字符，再用前驱数组回溯出整条链。
// 时间复杂度：O(n^2 * m)，n 为词数、m 为词长（check 逐位比较）；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> getWordsInLongestSubsequence(vector<string>& words, vector<int>& groups) {  // words：候选词；groups：每个词的分组号，要求相邻词分组不同
        auto check = [](string& s, string& t) {  // 判断两个词是否长度相同且恰好只差一个字符（汉明距离为 1）
            if (s.size() != t.size()) {  // 长度不同则不可能只差一个字符
                return false;  // 直接判定不合法
            }  // if 语句结束
            int cnt = 0;  // 统计不同字符的个数
            for (int i = 0; i < s.size(); ++i) {  // 逐位比较两个词
                cnt += s[i] != t[i];  // 该位不同则计数加一（利用 bool 转 int 的隐式转换）
            }  // for 循环结束
            return cnt == 1;  // 恰好一位不同才算合法
        };  // lambda 定义结束，check 可像函数一样调用
        int n = groups.size();  // 元素个数
        vector<int> f(n, 1);  // f[i]：以 i 结尾的最长合法子序列长度，至少包含自己故初值为 1
        vector<int> g(n, -1);  // g[i]：子序列中 i 的前驱下标，-1 表示没有前驱
        int mx = 1;  // 记录全局最长长度，最后用来定位终点
        for (int i = 0; i < n; ++i) {  // 依次枚举子序列的结尾下标 i
            for (int j = 0; j < i; ++j) {  // 枚举可能的倒数第二个元素下标 j
                if (groups[i] != groups[j] && f[i] < f[j] + 1 && check(words[i], words[j])) {  // 三个条件同时满足：分组不同、能延长当前链、两词只差一个字符
                    f[i] = f[j] + 1;  // 更新以 i 结尾的最长长度
                    g[i] = j;  // 记录前驱，供后面回溯路径
                    mx = max(mx, f[i]);  // 同步维护全局最大值
                }  // if 语句结束
            }  // 内层 j 循环结束
        }  // 外层 i 循环结束
        vector<string> ans;  // 保存最终答案
        for (int i = 0; i < n; ++i) {  // 找到第一个长度等于全局最大的终点
            if (f[i] == mx) {  // 该下标就是某条最长链的末尾
                for (int j = i; ~j; j = g[j]) {  // 沿前驱指针回溯，~j 等价于 j != -1
                    ans.emplace_back(words[j]);  // 逆序收集路径上的单词
                }  // while 循环结束
                break;  // 只需一条最长链，找到后立即跳出
            }  // if 语句结束
        }  // for 循环结束
        reverse(ans.begin(), ans.end());  // 回溯得到的是逆序，翻转成正序
        return ans;  // 返回答案
    }  // 方法结束
};  // 类定义结束