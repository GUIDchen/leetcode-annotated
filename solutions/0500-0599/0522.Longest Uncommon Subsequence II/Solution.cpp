// 题目：522. 最长特殊序列 II（Longest Uncommon Subsequence II）
// 思路：答案一定来自某个完整字符串；某串若是其它串的子序列就不合法，在合法串中取最长。
// 时间复杂度：O(n²·L)，每对字符串做一次双指针子序列判断；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 公有方法区
    int findLUSlength(vector<string>& strs) {  // strs：字符串数组；返回最长特殊序列长度，没有任何特殊序列时返回 -1
        int ans = -1;  // ans 保存目前找到的最大长度，初值 -1 表示「暂时没有答案」
        int n = strs.size();  // n 是字符串个数，下面两层循环都用它作上界
        auto check = [&](const string& s, const string& t) {  // lambda：判断 s 是否为 t 的子序列（双指针贪心匹配）
            int m = s.size(), n = t.size();  // m、n 分别是两个串的长度（此处的 n 遮蔽了外层的 n）
            int i = 0;  // i 是 s 上的匹配指针，j 是 t 上的扫描指针
            for (int j = 0; i < m && j < n; ++j) {  // 只要有一方走完就停止扫描
                if (s[i] == t[j]) {  // 字符相同说明匹配成功
                    ++i;  // s 的指针前进，表示这个字符已经被 t 匹配掉
                }  // if 结束
            }  // for 结束
            return i == m;  // i 走到 m 说明 s 的每个字符都在 t 中按顺序出现，即 s 是 t 的子序列
        };  // lambda 定义结束
        for (int i = 0, j; i < n; ++i) {  // 枚举每个候选串 strs[i]，判定它是否为「特殊序列」
            int x = strs[i].size();  // x 先假设 strs[i] 合法，取它自身的长度
            for (j = 0; j < n; ++j) {  // 与所有其它串比较，看 strs[i] 是否被别的串包含
                if (i != j && check(strs[i], strs[j])) {  // 跳过自己，并检查 strs[i] 是否为 strs[j] 的子序列
                    x = -1;  // 被包含则不合法，把候选长度标记成 -1
                    break;  // 已经确定不合法，无需继续比较
                }  // if 结束
            }  // 内层 for 结束
            ans = max(ans, x);  // 用当前候选长度更新全局最大长度
        }  // 外层 for 结束
        return ans;  // 返回所有合法候选中最大的长度（没有合法串时仍是 -1）
    }  // 方法结束
};  // 类定义结束