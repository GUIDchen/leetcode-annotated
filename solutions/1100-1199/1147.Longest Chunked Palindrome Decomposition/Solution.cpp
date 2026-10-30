// 题目：1147. 段式回文（Longest Chunked Palindrome Decomposition）
// 思路：双指针从两端向中间走，枚举最短的相同前后缀长度 k，能匹配就左右各切一段计入答案，最后中间剩余部分单独算一段。
// 时间复杂度：O(n^2)，每次匹配最坏要比较 O(n) 个字符；空间复杂度：O(1)，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestDecomposition(string text) {  // text 为待分解的字符串
        int ans = 0;  // ans 记录段式回文的段数
        auto check = [&](int i, int j, int k) -> bool {  // 闭包：判断从 i、j 开始、长度 k 的两段是否完全相同
            while (k--) {  // 逐字符比较 k 次
                if (text[i++] != text[j++]) {  // 有一个字符不同就不匹配
                    return false;  // 返回不匹配
                }  // if 结束
            }  // while 结束
            return true;  // k 个字符全部相同
        };  // 闭包结束
        for (int i = 0, j = text.size() - 1; i <= j;) {  // i 指向左端，j 指向右端，向中间收缩
            bool ok = false;  // 标记本轮是否找到可以切分的相同前后缀
            for (int k = 1; i + k - 1 < j - k + 1; ++k) {  // 枚举切分长度 k，条件保证左右两段不重叠
                if (check(i, j - k + 1, k)) {  // 找到一对相同的首段与尾段
                    ans += 2;  // 一次切分贡献两段
                    i += k;  // 左边界右移 k
                    j -= k;  // 右边界左移 k
                    ok = true;  // 标记本轮成功
                    break;  // 只要最短的合法切分，立即跳出
                }  // if 结束
            }  // k 循环结束
            if (!ok) {  // 左右已经没有可以配对的相同前后缀
                ans += 1;  // 中间剩下的整体算作一段
                break;  // 结束整个循环
            }  // if 结束
        }  // 外层循环结束
        return ans;  // 返回总段数
    }  // 方法结束
};  // 类定义结束