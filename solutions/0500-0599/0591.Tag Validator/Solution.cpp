// 题目：591. 标签验证器（Tag Validator）
// 思路：用栈模拟解析：遇到 <![CDATA[ 整段跳过，遇到 </ 就校验栈顶同名标签并弹栈，遇到 < 就校验标签名并压栈；栈非空或根标签后仍有内容均非法。
// 时间复杂度：O(n)，每一步都用 find 向前推进、不回头扫描；空间复杂度：O(n)，栈最深为嵌套标签层数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isValid(string code) {  // code 是待验证的代码片段
        stack<string> stk;  // 栈里存放尚未闭合的标签名
        for (int i = 0; i < code.size(); ++i) {  // 从左到右逐字符扫描整个字符串
            if (i && stk.empty()) return false;  // 首个标签之后栈已空，说明根标签提前闭合，后面还敢有内容
            if (code.substr(i, 9) == "<![CDATA[") {  // 进入 CDATA 段，段内内容不需要转义
                i = code.find("]]>", i + 9);  // 直接跳到 CDATA 的结束标记 ]]> 处
                if (i < 0) return false;  // 找不到 ]]> 说明 CDATA 没有闭合
                i += 2;  // 循环末尾还会 ++i，这里补 2 正好让 i 停在 '>' 上
            } else if (code.substr(i, 2) == "</") {  // 以 </ 开头的是结束标签
                int j = i + 2;  // 标签名从 i+2 开始
                i = code.find('>', j);  // 找到结束尖括号
                if (i < 0) return false;  // 没有 '>' 说明标签没有闭合
                string t = code.substr(j, i - j);  // 取出标签名
                if (!check(t) || stk.empty() || stk.top() != t) return false;  // 名字不合法、没有可闭合的标签、或与栈顶不匹配，三者任一即失败
                stk.pop();  // 匹配成功，弹出这个标签
            } else if (code.substr(i, 1) == "<") {  // 以 < 开头的是开始标签
                int j = i + 1;  // 标签名从 i+1 开始
                i = code.find('>', j);  // 找结束尖括号
                if (i < 0) return false;  // 没有 '>' 就非法
                string t = code.substr(j, i - j);  // 取出标签名
                if (!check(t)) return false;  // 标签名必须是 1~9 位大写字母
                stk.push(t);  // 入栈，等待后续用 </...> 闭合
            }
        }
        return stk.empty();  // 扫描结束后必须所有标签都已闭合，即栈为空
    }

    bool check(string tag) {  // 校验标签名格式是否合法
        int n = tag.size();  // 标签名的长度
        if (n < 1 || n > 9) return false;  // 长度必须在 1 到 9 之间
        for (char& c : tag)  // 逐个字符检查
            if (!isupper(c))  // 必须是大写字母
                return false;  // 出现非法字符就失败
        return true;  // 格式合法
    }
};