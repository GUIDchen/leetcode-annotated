// 题目：1432. 改变一个整数能得到的最大差值（Max Difference You Can Get From Changing an Integer）
// 思路：把 num 的数字串按位替换出最大值和最小值——最大取首位非 9 位换成 9，最小按首位是否为 1 分别换成 1 或后续首个非 0/1 位换成 0。
// 时间复杂度：O(d²)，d 为位数（每次替换扫描一遍串）；空间复杂度：O(d)，存放两个数字串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDiff(int num) {  // num：原整数，返回「替换后的最大值 - 替换后的最小值」
        auto replace = [](string& s, char a, char b) {  // 小工具：把字符串 s 中所有字符 a 原地换成 b
            for (auto& c : s) {  // 逐字符扫描整个字符串
                if (c == a) {  // 命中目标字符
                    c = b;  // 替换成新字符
                }  // if 结束
            }  // for 结束
        };  // lambda 定义结束
        string a = to_string(num);  // 最大值：把最高位的第一个非 9 数字全部换成 9
        string b = a;  // 最小值：先复制一份，单独处理
        for (int i = 0; i < a.size(); ++i) {  // 从最高位开始找第一个不是 9 的数字
            if (a[i] != '9') {  // 找到后全换成 9，这样数值最大
                replace(a, a[i], '9');  // 把它所有出现的位置都换成 9
                break;  // 只需换一次，后面的数字不再处理
            }  // if 结束
        }  // for 结束
        if (b[0] != '1') {  // 最小值规则：首位不能变成 0（避免前导零）
            replace(b, b[0], '1');  // 首位不是 1 时把它整体换成 1，得到最小且合法的最小值
        } else {  // 首位已经是 1，只能改后面的位
            for (int i = 1; i < b.size(); ++i) {  // 从第二位开始找第一个既不是 0 也不是 1 的数字
                if (b[i] != '0' && b[i] != '1') {  // 换成 0 不会造成前导零，可以放心替换
                    replace(b, b[i], '0');  // 把它所有出现的位置都换成 0
                    break;  // 只换一次即可
                }  // if 结束
            }  // for 结束
        }  // else 结束
        return stoi(a) - stoi(b);  // 两个替换后的数字相减即为最大差值
    }  // 方法结束
};  // 类定义结束