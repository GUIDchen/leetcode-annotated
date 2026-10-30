// 题目：2810. 故障键盘（Faulty Keyboard）
// 思路：用 t 累积已输入的字符；按下 'i' 时把 t 整体反转，其他字符直接追加到末尾，最后返回 t。
// 时间复杂度：O(n^2)，最坏情况下每个 'i' 都要翻转一次当前串；空间复杂度：O(n)，结果串长度不超过输入长度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string finalString(string s) {  // s：按键序列；返回最终屏幕上显示的字符串
        string t;  // t 累积当前已经输入的字符串
        for (char c : s) {  // 按顺序处理每一次按键
            if (c == 'i') {  // 按下 'i'：触发整串反转
                reverse(t.begin(), t.end());  // 原地反转已输入的 t，耗时 O(|t|)
            } else {  // 其他字符直接追加到末尾
                t.push_back(c);  // 把字符追加到 t 的尾部
            }
        }
        return t;  // 返回最终显示的字符串
    }
};  // 类定义结束