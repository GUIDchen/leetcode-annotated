// 题目：1896. 反转表达式值的最少操作次数（Minimum Cost to Change the Final Value of Expression）
// 思路：中缀表达式用双栈转后缀求值，每个子表达式保存「(当前值, 反转它所需的最少操作数)」，合并时按 &、| 的真值表分类取最小代价。
// 时间复杂度：O(n)，每个字符进出栈各一次；空间复杂度：O(n)，操作数栈与运算符栈都与表达式长度同阶。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperationsToFlip(string expression) {  // expression：只含 0、1、&、| 和括号的布尔表达式
        vector<pair<int, int>> nums;  // 操作数栈：first 存子表达式的值，second 存「反转该值所需的最少操作次数」
        vector<char> ops;  // 运算符栈：存放 &、| 和左括号
        auto merge = [&](char op) {  // 合并函数：弹出两个操作数，按运算符 op 计算「值 + 反转代价」
            auto b = nums.back();  // 右操作数（后进先出）
            nums.pop_back();  // 弹出右操作数
            auto a = nums.back();  // 左操作数
            nums.pop_back();  // 弹出左操作数
            int v1 = a.first, c1 = a.second, v2 = b.first, c2 = b.second;  // 拆开两个操作数的值与代价，便于下面判断
            int val, cost;  // val：合并后的值；cost：把合并结果反转所需的最小操作数
            if (op == '&') {  // 先处理与运算
                val = v1 & v2;  // 与运算的真值：两个都是 1 才是 1
                if (v1 == 1 && v2 == 1) {  // 1 & 1 = 1，本次想把结果由 1 反成 0
                    cost = min(c1, c2);  // 把任意一个操作数反成 0 即可，取代价较小者
                } else if (v1 == 0 && v2 == 0) {  // 0 & 0 = 0，本次想把结果由 0 反成 1
                    cost = min(c1 + c2, 1 + min(c1, c2));  // 两条路：把两个 0 都反成 1（c1+c2）；或把 & 改成 | 再反一个（1+min）
                } else {  // 一 0 一 1：结果是 0
                    cost = min(v1 == 0 ? c1 : c2, 1);  // 反掉那个 0 操作数，或直接把 & 改成 |（代价 1）
                }
            } else {  // 否则只能是或运算
                val = v1 | v2;  // 或运算的真值：有一个 1 就是 1
                if (v1 == 0 && v2 == 0) {  // 0 | 0 = 0，本次想把结果由 0 反成 1
                    cost = min(c1, c2);  // 把任意一个操作数反成 1 即可
                } else if (v1 == 1 && v2 == 1) {  // 1 | 1 = 1，本次想把结果由 1 反成 0
                    cost = min(c1 + c2, 1 + min(c1, c2));  // 把两个 1 都反掉；或把 | 改成 & 再反一个
                } else {  // 一 0 一 1：结果是 1
                    cost = min(v1 == 1 ? c1 : c2, 1);  // 反掉那个 1 操作数，或直接把 | 改成 &（代价 1）
                }
            }
            nums.emplace_back(val, cost);  // 把合并结果压回操作数栈
        };  // 合并 lambda 结束
        for (char c : expression) {  // 从左到右扫描表达式，做中缀转后缀
            if (c == '(') {  // 左括号直接入栈，作为子表达式的边界
                ops.push_back(c);  // 记下左括号
            } else if (c == '0' || c == '1') {  // 常量：值就是字符本身，反转它需要 1 次操作
                nums.emplace_back(c - '0', 1);  // 压入 (值, 1)
            } else if (c == '&' || c == '|') {  // 运算符：先把栈顶同优先级的 & 与 | 全部结算（二者优先级相同、左结合）
                while (!ops.empty() && (ops.back() == '&' || ops.back() == '|')) {  // 栈顶还是运算符就继续结算
                    merge(ops.back());  // 结算栈顶运算符
                    ops.pop_back();  // 该运算符已用掉，出栈
                }
                ops.push_back(c);  // 当前运算符入栈
            } else {  // 剩下的只可能是右括号
                while (ops.back() != '(') {  // 把括号内的运算全部结算完
                    merge(ops.back());  // 结算括号内的运算符
                    ops.pop_back();  // 用完出栈
                }
                ops.pop_back();  // 弹出左括号，括号本身不参与计算
            }
        }
        while (!ops.empty()) {  // 扫描结束，栈里剩余的运算符依次结算
            merge(ops.back());  // 结算栈顶运算符
            ops.pop_back();  // 出栈
        }
        return nums[0].second;  // 栈中只剩整个表达式的 (值, 反转代价)，答案就是代价
    }
};
