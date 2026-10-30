// 题目：3931. 检查相邻数字差（Check Adjacent Digit Differences）
// 思路：从左到右比较每一对相邻字符，数字字符的 ASCII 差恰好等于数字差，只要有一对超过 2 就返回 false，全部满足则返回 true。
// 时间复杂度：O(n)，最多扫描一遍；空间复杂度：O(1)，只用循环变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isAdjacentDiffAtMostTwo(string s) {  // s：只含数字的字符串，返回是否所有相邻数字差都至多为 2
        for (int i = 1; i < s.size(); ++i) {  // 从第二个字符开始逐对比较
            if (abs(s[i - 1] - s[i]) > 2) {  // 字符相减等价于数字相减，差值超过 2 即不合法
                return false;  // 出现不满足的一对，直接判假
            }  // 分支结束
        }  // 遍历结束
        return true;  // 所有相邻对都满足，返回真
    }  // 方法结束
};  // 类定义结束