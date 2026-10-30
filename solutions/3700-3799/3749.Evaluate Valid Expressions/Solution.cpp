// 题目：3749. 计算有效表达式（Evaluate Valid Expressions）
// 核心思路：表达式是嵌套的 op(a,b) 结构，用递归下降解析：遇到数字或负号就解析字面量，否则先读到左括号取出运算符，再依次解析两个子表达式并按 add/sub/mul/div 求值，返回「结果 + 下一个未处理下标」。
// 复杂度：时间 O(n)，每个字符只会被扫描常数次；空间 O(n)，递归栈深度与表达式嵌套层数成正比。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long evaluateExpression(string expression) {  // 解析并计算嵌套表达式 expression，返回其整数值
        auto parse = [&](this auto&& parse, int i) -> pair<long long, int> {  // 递归下降：parse(i) 解析从 i 开始的子表达式，返回 {结果, 下一个未处理下标}
            if (isdigit(expression[i]) || expression[i] == '-') {  // 以数字或负号开头，说明当前是一个整数字面量
                int j = i;  // j 用于向后扫描字面量的结束位置
                if (expression[j] == '-') {  // 首位是负号时先跳过它
                    j++;  // 跳过负号
                }  // if 分支结束
                while (j < expression.size() && isdigit(expression[j])) {  // 继续吞掉后面连续的数字字符
                    j++;  // 指针后移
                }  // 循环结束
                long long num = stoll(expression.substr(i, j - i));  // 取出 [i, j) 这段子串并转成长整型
                return {num, j};  // 返回字面量的值和它的结束下标
            }  // 字面量分支结束

            int j = i;  // 从 i 开始向后扫描，去寻找标识运算符结束的左括号 '('
            while (expression[j] != '(') {  // 一直右移直到遇到左括号 '('
                j++;  // 指针后移
            }  // 循环结束
            string op = expression.substr(i, j - i);  // 取出运算符字符串 op（add/sub/mul/div）
            j++;  // 跳过左括号 '('

            auto [val1, next_j1] = parse(j);  // 递归解析第一个参数 a
            j = next_j1 + 1;  // 跳过参数之间的逗号 ','

            auto [val2, next_j2] = parse(j);  // 递归解析第二个参数 b
            j = next_j2 + 1;  // 跳过右括号 ')'，于是 j 指向整个表达式之后

            long long res = 0;  // res 存放本次运算的结果
            if (op == "add") {  // 加法
                res = val1 + val2;  // a + b
            } else if (op == "sub") {  // 减法
                res = val1 - val2;  // a - b
            } else if (op == "mul") {  // 乘法
                res = val1 * val2;  // a * b
            } else if (op == "div") {  // 除法，题目保证所有除法结果都是整数
                res = val1 / val2;  // a / b
            }  // 运算分支结束

            return {res, j};  // 返回结果和下一个未处理的下标
        };  // lambda 定义结束

        return parse(0).first;  // 从下标 0 开始解析整个表达式，取结果部分
    }  // 方法结束
};  // 类定义结束
