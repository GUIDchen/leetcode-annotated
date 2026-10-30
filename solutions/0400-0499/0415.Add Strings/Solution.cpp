// 题目：415. 字符串相加（Add Strings）
// 思路：addStrings 从个位往前逐位相加并维护进位 c，循环条件是「还有位没处理或进位不为 0」；subStrings 是配套的大数减法，先比较大小定符号，再逐位相减处理借位。
// 时间复杂度：O(max(m, n))，只与两个串的长度有关；空间复杂度：O(max(m, n))，用于存放结果字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string addStrings(string num1, string num2) {  // num1、num2 是两个十进制数字字符串，返回它们相加后的字符串
        int i = num1.size() - 1, j = num2.size() - 1;  // i、j 分别指向两个字符串的最低位（末尾字符）
        string ans;  // ans 逆序累积每一位的结果，最后整体反转
        for (int c = 0; i >= 0 || j >= 0 || c; --i, --j) {  // c 是进位；只要还有位没算完、或者还有进位，就继续循环，每轮 i、j 各左移一位
            int a = i < 0 ? 0 : num1[i] - '0';  // 取出 num1 的当前位数字；i 越界（已处理完）时按 0 处理
            int b = j < 0 ? 0 : num2[j] - '0';  // 取出 num2 的当前位数字；j 越界时同样按 0 处理
            c += a + b;  // 把两个数字与上一位的进位累加到 c
            ans += to_string(c % 10);  // 当前位的数字是 c % 10，转成字符追加到 ans 末尾
            c /= 10;  // 更新进位 c / 10（这里只可能是 0 或 1）
        }  // 循环结束：所有位与进位都处理完了
        reverse(ans.begin(), ans.end());  // ans 现在是低位在前，反转成正常的高位在前顺序
        return ans;  // 返回和的字符串表示
    }  // addStrings 方法结束

    string subStrings(string num1, string num2) {  // 大数减法：计算 num1 - num2，结果可能为负数（保留负号）
        int m = num1.size(), n = num2.size();  // 记录两个字符串的长度，用于比较大小
        bool neg = m < n || (m == n && num1 < num2);  // 若 num1 更短，或长度相同但字典序更小，则结果为负
        if (neg) {  // 结果为负的情况
            swap(num1, num2);  // 交换两个串，先按「大减小」算绝对值，最后再补负号
        }  // 交换分支结束
        int i = num1.size() - 1, j = num2.size() - 1;  // i、j 指向两个串的最低位
        string ans;  // ans 逆序累积差的每一位
        for (int c = 0; i >= 0; --i, --j) {  // c 在这里充当「借位」；只要 i 还有位就继续（被减数更长，高位直接落下）
            c = (num1[i] - '0') - c - (j < 0 ? 0 : num2[j] - '0');  // 当前位：被减数位 - 借位 - 减数位（j 越界按 0）
            ans += to_string((c + 10) % 10);  // (c + 10) % 10 把可能为负的结果回绕成 0~9 的一位数字
            c = c < 0 ? 1 : 0;  // 若当前位减出了负数，说明要向高位借 1
        }  // 循环结束
        while (ans.size() > 1 && ans.back() == '0') {  // 从最高位开始去掉多余的 0（至少保留一位，保证 0 的结果是 "0"）
            ans.pop_back();  // 弹出当前最高位的那个 0
        }  // 前导零清理完毕
        if (neg) {  // 原被减数更小，结果需要带负号
            ans.push_back('-');  // 在末尾追加负号，反转后它会出现在最前面
        }  // 负号处理结束
        reverse(ans.begin(), ans.end());  // 反转成正常的从高位到低位
        return ans;  // 返回差的字符串表示
    }  // subStrings 方法结束
};  // Solution 类结束