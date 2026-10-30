// 题目：3703. 移除 K-平衡子字符串（Remove K-Balanced Substrings）
// 核心思路：用「字符 + 连续出现次数」的栈表示当前串并模拟删除：遇到右括号后，若栈顶是一段长度恰为 k 的 ')' 且其下方紧跟一段长度至少 k 的 '('，就把这两段各削去 k 个，等价于删掉最近的 k 个 '(' 与 k 个 ')'。
// 复杂度：时间 O(n)，每个字符均摊入栈出栈一次；空间 O(n)，栈最多存 n 个字符段。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string removeSubstring(string s, int k) {  // 返回反复删除所有 K-平衡子串后的结果
        vector<pair<char, int>> stk;  // 栈元素是「字符，该字符的连续个数」这样的段
        for (char c : s) {  // 从左到右扫描每个字符
            if (!stk.empty() && stk.back().first == c) {  // 栈顶段字符相同，可以并入这一段
                stk.back().second += 1;  // 该段长度加一
            } else {  // 字符与栈顶不同，或者栈为空
                stk.emplace_back(c, 1);  // 新开一段，初始长度 1
            }  // 结束入栈处理
            if (c == ')' && stk.size() > 1) {  // 只有出现右括号且栈里至少有 '(' 段和 ')' 段两段时才可能删除
                auto& top = stk.back();  // 栈顶段：当前的 ')' 段
                auto& prev = stk[stk.size() - 2];  // 次栈顶段：紧邻的 '(' 段
                if (top.second == k && prev.second >= k) {  // ')' 段恰好 k 个、'(' 段不少于 k 个，凑成 K-平衡子串
                    stk.pop_back();  // 先弹出 ')' 段：删除 k 个右括号后该段归零
                    prev.second -= k;  // 再从 '(' 段削去 k 个左括号
                    if (prev.second == 0) {  // '(' 段被削空后不应留在栈里
                        stk.pop_back();  // 弹出空的 '(' 段
                    }  // 结束空段清理
                }  // 结束 K-平衡判定
            }  // 结束删除逻辑
        }  // 结束扫描
        string res;  // 存放还原出来的结果字符串
        for (auto& p : stk) {  // 按顺序展开栈中每个字符段
            res.append(p.second, p.first);  // 把该段字符重复其次数追加到结果
        }  // 结束展开
        return res;  // 返回删除后的最终字符串
    }  // 结束 removeSubstring
};  // 结束题解类
