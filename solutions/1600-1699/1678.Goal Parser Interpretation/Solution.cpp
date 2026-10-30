// 题目：1678. 设计 Goal 解析器（Goal Parser Interpretation）
// 思路：直接在原字符串上按固定顺序替换：先把所有 "()" 换成 "o"，再把所有 "(al)" 换成 "al"。
// 时间复杂度：O(n²)，每次 find/replace 都要移动字符串；空间复杂度：O(1)（不计返回值拷贝）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string interpret(string command) {  // command：待解析的命令字符串，返回解析后的字符串
        while (command.find("()") != -1) command.replace(command.find("()"), 2, "o");  // 只要还存在 "()"，就反复替换成 "o"（长度由 2 变 1）
        while (command.find("(al)") != -1) command.replace(command.find("(al)"), 4, "al");  // 再把所有 "(al)" 替换成 "al"（长度由 4 变 2）
        return command;  // 返回替换完成的字符串
    }  // 方法结束
};  // 类定义结束