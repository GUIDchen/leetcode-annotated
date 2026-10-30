// 题目：809. 情感丰富的文字（Expressive Words）
// 思路：把 s 和每个单词都切成「连续相同字符段」，用双指针逐段比较字符与段长，再按扩张规则判定是否可行。
// 时间复杂度：O(L * |s|)，L 为 words 中单词个数；空间复杂度：O(1)，只用了若干指针与计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int expressiveWords(string s, vector<string>& words) {  // s 是目标字符串，words 是待检验的单词列表
        auto check = [](string& s, string& t) -> int {  // 局部 lambda：判断单词 t 能否通过扩张得到 s，返回 1 或 0
            int m = s.size(), n = t.size();  // m 是 s 的长度，n 是 t 的长度
            if (n > m) return 0;  // t 比 s 还长，扩张只会变长，不可能相等
            int i = 0, j = 0;  // 双指针：i 指向 s，j 指向 t
            while (i < m && j < n) {  // 两串都没扫完时，逐段比较
                if (s[i] != t[j]) return 0;  // 段首字符必须完全相同
                int k = i;  // k 用来统计 s 中与 s[i] 相同的一段连续字符
                while (k < m && s[k] == s[i]) ++k;  // 向后扫描，定位这一段在 s 中的结束位置
                int c1 = k - i;  // c1 是 s 中该字符连续出现的次数
                i = k, k = j;  // i 推进到 s 的下一段；k 重置为 j，准备统计 t 的段长
                while (k < n && t[k] == t[j]) ++k;  // 向后扫描，定位这一段在 t 中的结束位置
                int c2 = k - j;  // c2 是 t 中该字符连续出现的次数
                j = k;  // j 推进到 t 的下一段
                if (c1 < c2 || (c1 < 3 && c1 != c2)) return 0;  // 段长只允许被扩张：c1 不能小于 c2；且 s 这段不足 3 个时长度必须完全相等
            }  // while 结束，回到循环继续比较下一段
            return i == m && j == n;  // 两串必须同时扫描完，剩下的段都不合法
        };  // lambda 定义结束

        int ans = 0;  // 统计能够扩张成 s 的单词个数
        for (string& t : words) ans += check(s, t);  // 每个单词检验一次，check 返回 1 或 0，直接累加到答案
        return ans;  // 返回答案
    }  // 方法结束
};  // 类定义结束