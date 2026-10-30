// 3722. Lexicographically Smallest String After Reverse（反转后字典序最小的字符串）
// 核心思路：枚举旋转/翻转长度 k，分别尝试“翻转长度为 k 的前缀”和“翻转长度为 k 的后缀”，在所有候选串中取字典序最小者。
// 复杂度：时间 O(n^2)（枚举 n 种长度，每次构造 O(n) 的串），空间 O(n)。

class Solution {
public:
    string lexSmallest(string s) {  // 返回一次反转（翻转某个前缀或某个后缀）后字典序最小的字符串
        string ans = s;  // ans 记录当前最优答案，初始为原串（相当于翻转长度 0）
        int n = s.size();  // 取字符串长度 n
        for (int k = 1; k <= n; ++k) {  // 枚举翻转长度 k，从 1 到 n
            string t1 = s.substr(0, k);  // 方案一：取出长度为 k 的前缀
            reverse(t1.begin(), t1.end());  // 把该前缀就地翻转
            t1 += s.substr(k);  // 接上剩余后缀，得到前缀翻转后的串 t1

            string t2 = s.substr(0, n - k);  // 方案二：取出长度为 n-k 的前缀部分
            string suffix = s.substr(n - k);  // 取出长度为 k 的后缀
            reverse(suffix.begin(), suffix.end());  // 把该后缀就地翻转
            t2 += suffix;  // 拼成后缀翻转后的串 t2

            ans = min({ans, t1, t2});  // 在 ans、t1、t2 三者中取字典序最小者
        }  // 枚举结束
        return ans;  // 返回字典序最小的结果
    }  // 函数结束
};  // 题解类结束
