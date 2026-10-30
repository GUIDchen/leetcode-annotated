// 题目：2566. 替换一个数字后的最大差值（Maximum Difference by Remapping a Digit）
// 思路：把首位数字全部替换成 0 得到最小值；再从高位往低位找第一个非 9 的数字，把它全部替换成 9 得到最大值，两者相减。
// 时间复杂度：O(d^2)，d 为数字位数（d ≤ 10，可视为常数）；空间复杂度：O(d)，两个等长的字符串副本。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minMaxDifference(int num) {  // num：输入整数，可以把某一种数字全部改写成另一个数字
        string s = to_string(num);  // 转成字符串，便于按位处理；这份副本用来构造最小值
        string t = s;  // 再复制一份，用来构造最大值
        char first = s[0];  // 记录最高位数字：把它替换成 0 能让结果最小
        for (char& c : s) {  // 用引用遍历，才能原地修改字符串
            if (c == first) {  // 与最高位相同的数字
                c = '0';  // 全部换成 '0'
            }
        }
        int mi = stoi(s);  // 替换完成后转回整数，得到最小值
        for (int i = 0; i < t.size(); ++i) {  // 从高位到低位找第一个不等于 '9' 的数字
            if (t[i] != '9') {  // 找到可以放大的数字
                char second = t[i];  // 记下要被替换的数字
                for (int j = i; j < t.size(); ++j) {  // 从当前位置往后遍历（前面的位都已是 '9'，无需再看）
                    if (t[j] == second) {  // 遇到相同的数字
                        t[j] = '9';  // 全部换成 '9'，这样得到最大值
                    }
                }
                return stoi(t) - mi;  // 最大值减去最小值，就是最大差值
            }
        }
        return num - mi;  // 所有位都是 '9' 时无法变大，最大差值就是 num 减去最小值
    }
};