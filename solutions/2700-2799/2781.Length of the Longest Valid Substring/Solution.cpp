// 题目：2781. 最长合法子字符串的长度（Length of the Longest Valid Substring）
// 核心思路：滑动窗口 + 哈希集合。右端 j 逐个右移，只枚举以 j 结尾、长度不超过 10 的子串（禁用串长度上限为 10），一旦命中就把左端 i 跳到命中起点之后，使窗口内始终不含禁用串。
// 时间复杂度：O(n * L^2)，n 为串长、L = 10 为禁用串长度上限（截取子串还需 O(L)）；空间复杂度：O(mL)，哈希集合保存全部禁用串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestValidSubstring(string word, vector<string>& forbidden) {  // word：待检查的字符串；forbidden：所有禁用子串；返回最长合法子串的长度
        unordered_set<string> s(forbidden.begin(), forbidden.end());  // 把 forbidden 装进哈希集合，之后 O(1) 判断任意子串是否被禁用
        int ans = 0, n = word.size();  // ans 记录历史最长合法长度；n 是 word 的长度
        for (int i = 0, j = 0; j < n; ++j) {  // 滑动窗口 [i, j]：j 是右端点逐格右扩，i 是左端点只在命中禁用串时右跳
            for (int k = j; k > max(j - 10, i - 1); --k) {  // 只枚举以 j 结尾的子串起点 k：长度最多 10（禁用串长度上限），且不能越过窗口左端 i
                if (s.count(word.substr(k, j - k + 1))) {  // 取出子串 word[k..j] 去集合里查，count 返回 0 或 1
                    i = k + 1;  // 命中禁用串：起点 k 必须被排除，窗口左端至少要推到 k+1
                    break;  // 更短的子串都是它的子串、同样非法，无需继续检查
                }  // 内层循环结束
            }  // 此时窗口 [i, j] 内不含任何禁用串
            ans = max(ans, j - i + 1);  // 用当前合法窗口长度刷新答案
        }  // 外层循环结束
        return ans;  // 返回最长合法子串长度
    }  // 方法结束
};  // 类定义结束