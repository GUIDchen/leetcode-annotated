// 题目：736. Lisp 语法解析（Parse Lisp Expression）
// 思路：用一个下标 i 在字符串上做递归下降解析；scope 记录「变量名 → 各层 let 的值栈」，遇到 ( 按 let/add/mult 分派，遇到变量或整数就地求值。
// 时间复杂度：O(n)，每个字符只被常数次扫描；空间复杂度：O(n)，作用域栈与递归深度均为 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int i = 0;  // 全局解析指针：指向当前待处理的字符位置
    string expr;  // 保存待解析的表达式，供各辅助函数共享
    unordered_map<string, vector<int>> scope;  // 作用域：变量名 → 值栈；let 可嵌套，同名变量用栈保存每一层的值

    int evaluate(string expression) {  // expression：待求值的 Lisp 表达式
        expr = expression;  // 把输入存到成员变量，方便 parseVar / parseInt 直接按 i 读取
        return eval();  // 从下标 0 开始递归求值整个表达式
    }  // 结束 evaluate

    int eval() {  // 求值当前表达式（可能是整数、变量或括号表达式），返回它的值
        if (expr[i] != '(') return islower(expr[i]) ? scope[parseVar()].back() : parseInt();  // 不以 ( 开头：是变量名就取作用域栈顶值，是数字就直接解析
        int ans = 0;  // ans 保存本次求值的结果
        ++i;  // 跨过左括号 (，i 指向操作符首字母
        if (expr[i] == 'l') {  // 首字母是 l ⇒ 说明是 let 表达式
            i += 4;  // 跳过 "let " 这 4 个字符，i 指向第一个绑定名或结尾表达式
            vector<string> vars;  // vars 记录本次 let 真正压栈的变量名，退出时要逐个弹出恢复作用域
            while (1) {  // 循环处理 let 的绑定列表与结尾表达式
                string var = parseVar();  // 读出当前这一段变量名（或结尾表达式里的变量名）
                if (expr[i] == ')') {  // 变量名后面紧跟 ) ⇒ 它是 let 的结尾表达式，直接取其值
                    ans = scope[var].back();  // 取出该变量当前的值作为整个 let 的结果
                    break;  // 拿到结果后跳出循环
                }  // 否则 var 是一个绑定名，先记录下来
                ++i;  // 跳过绑定名与值之间的空格
                vars.push_back(var);  // 记录这个绑定名，供最后统一弹栈
                scope[var].push_back(eval());  // 递归求值绑定的右侧并压入作用域栈
                ++i;  // 跳过值与下一个 token 之间的空格
                if (!islower(expr[i])) {  // 下一个 token 不是小写字母 ⇒ 是 (add/mult …)，即 let 的结尾表达式
                    ans = eval();  // 求值结尾表达式作为整个 let 的结果
                    break;  // 拿到结果后跳出循环
                }  // 结束 while (1)
            }  // 结束 let 分支
            for (string v : vars) scope[v].pop_back();  // 撤销本次 let 引入的绑定，让同名变量的外层值重新可见
        } else {  // 否则是 add 或 mult 表达式
            bool add = expr[i] == 'a';  // 首字母是 a ⇒ add，否则是 mult
            i += add ? 4 : 5;  // 跳过 "add "（4 个字符）或 "mult "（5 个字符）
            int a = eval();  // 递归求第一个操作数
            ++i;  // 跳过两个操作数之间的空格
            int b = eval();  // 递归求第二个操作数
            ans = add ? a + b : a * b;  // 按运算符合并两个操作数的结果
        }  // 结束 add / mult 分支
        ++i;  // 跨过对应的右括号 )
        return ans;  // 返回本层的求值结果
    }  // 结束 eval

    string parseVar() {  // 从 i 开始读出一个变量名，并让 i 停在名字结尾
        int j = i;  // 记下变量名起点
        while (i < expr.size() && expr[i] != ' ' && expr[i] != ')') ++i;  // 名字一直延续到空格、右括号或字符串末尾为止
        return expr.substr(j, i - j);  // 截取 [j, i) 这一段作为变量名返回
    }  // 结束 parseVar

    int parseInt() {  // 从 i 开始读出一个整数（可能带负号）
        int sign = 1, v = 0;  // sign 是符号位，v 是累加的绝对值
        if (expr[i] == '-') {  // 遇到负号说明是负数
            sign = -1;  // 记下负号
            ++i;  // 跳过负号
        }  // 结束 if
        while (i < expr.size() && expr[i] >= '0' && expr[i] <= '9') {  // 逐位读取数字字符
            v = v * 10 + (expr[i] - '0');  // 把新的一位接到当前数值后面
            ++i;  // 移动到下一位
        }  // 结束 while
        return sign * v;  // 补上符号位后返回
    }  // 结束 parseInt
};  // 结束 Solution 类