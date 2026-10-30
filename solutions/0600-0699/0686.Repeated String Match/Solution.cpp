// 题目：686. 重复叠加字符串匹配（Repeated String Match）
// 思路：先把 a 叠加到长度不小于 b，再最多多叠 2 次（覆盖起点错位所需的额外汇合）；每次检查 b 是否为子串，都不行则返回 -1。
// 时间复杂度：O(n·m)，每次子串查找 O(n·m)，常数次查找；空间复杂度：O(n)，只需保存叠加后的字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    int repeatedStringMatch(string a, string b) {  // a 是用来重复的字符串，b 是目标子串
        int m = a.size(), n = b.size();  // m 是 a 的长度，n 是 b 的长度
        int ans = (n + m - 1) / m;  // 向上取整：至少要叠几次，长度才够 b
        string t = "";  // t 用来存放叠加后的字符串
        for (int i = 0; i < ans; ++i) t += a;  // 先原样叠加 ans 次 a
        for (int i = 0; i < 3; ++i) {  // 再多试 2 次，因为 b 的起点可能落在 a 的任意偏移处
            if (t.find(b) != -1) return ans;  // 找到 b 就返回当前的叠加次数
            ++ans;  // 叠加次数加一
            t += a;  // 再叠加一次 a 后继续检查
        }
        return -1;  // 试满仍找不到，说明无论如何都无法匹配
    }
};