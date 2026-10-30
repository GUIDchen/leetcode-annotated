// 题目：1796. 字符串中第二大的数字（Second Largest Digit in a String）
// 思路：一次遍历，a 维护最大数字、b 维护严格次大数字，遇到数字按三种情况更新。
// 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    int secondHighest(string s) {  // s：输入字符串，返回第二大的数字，不存在则返回 -1
        int a = -1, b = -1;  // a 是最大数字，b 是第二大数字；-1 表示还没出现
        for (char& c : s) {  // 范围 for 遍历每个字符
            if (isdigit(c)) {  // 只处理数字字符
                int v = c - '0';  // 字符转成 0~9 的数值
                if (v > a) {  // 出现了更大的数字
                    b = a, a = v;  // 逗号表达式：先让旧最大值成为第二大，再更新最大值
                } else if (v > b && v < a) {  // 严格小于最大值且大于当前第二大
                    b = v;  // 更新第二大数字
                }  // if 结束
            }  // if 结束
        }  // for 结束
        return b;  // 返回第二大数字
    }  // 方法结束
};  // 类定义结束