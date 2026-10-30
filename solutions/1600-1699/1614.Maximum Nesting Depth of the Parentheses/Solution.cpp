// 题目：1614. 括号的最大嵌套深度（Maximum Nesting Depth of the Parentheses）
// 思路：一次扫描，遇到左括号就深度加一并更新答案，遇到右括号就深度减一；其余字符忽略。
// 时间复杂度：O(n)，字符串只扫一遍；空间复杂度：O(1)，只用两个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDepth(string s) {  // s：由括号、字母和运算符组成的合法字符串
        int ans = 0, d = 0;  // ans 保存历史最大深度，d 是当前嵌套深度
        for (char& c : s) {  // 逐字符扫描整个字符串
            if (c == '(') {  // 遇到左括号，说明进入新的一层
                ans = max(ans, ++d);  // 先自增再与答案取较大值，保证记录的是历史最深
            } else if (c == ')') {  // 遇到右括号，说明退出一层
                --d;  // 当前深度减一
            }
        }
        return ans;  // 返回扫描过程中出现的最大嵌套深度
    }
};
