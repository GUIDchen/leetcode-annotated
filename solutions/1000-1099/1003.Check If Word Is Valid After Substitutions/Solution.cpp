// 题目：1003. 检查替换后的词是否有效（Check If Word Is Valid After Substitutions）
// 思路：用字符串当栈，从左到右入栈；一旦栈顶三个字符正好是 abc，就说明它们来自同一次插入，整体弹出；扫描完栈空则合法。
// 时间复杂度：O(n)，每个字符入栈出栈各一次；空间复杂度：O(n)，栈最坏存全部字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isValid(string s) {  // s：待检验字符串；返回它能否由 abc 不断插入得到
        if (s.size() % 3) {  // 每次插入固定增加 3 个字符，所以长度必须是 3 的倍数
            return false;  // 长度不合法，直接判为无效
        }
        string t;  // 用 t 当栈，保存还没有被配对消掉的前缀
        for (char c : s) {  // 从左到右扫描每个字符
            t.push_back(c);  // 当前字符入栈
            if (t.size() >= 3 && t.substr(t.size() - 3, 3) == "abc") {  // 栈顶三个字符恰好是 abc，说明它们来自同一次插入
                t.erase(t.end() - 3, t.end());  // 把这 3 个字符一起弹出，等价于撤销一次插入
            }
        }
        return t.empty();  // 全部消完则栈空，字符串合法
    }
};