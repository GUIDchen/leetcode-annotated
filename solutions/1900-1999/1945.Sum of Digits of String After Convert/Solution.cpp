// 题目：1945. 字符串转化后的各位数字之和（Sum of Digits of String After Convert）
// 思路：先把每个字母换成它在字母表中的序号（1..26）拼成数字串，再重复 k 次「各位数字求和」，最后把剩下的数字串转成整数。
// 时间复杂度：O(n + k·D)，D 为数字串长度且每次至少缩短一位；空间复杂度：O(n)，存放转换后的数字串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getLucky(string s, int k) {  // s：小写字母串；k：数字和变换的次数
        string t;  // t 用来累积字母转换后的数字串
        for (char c : s) {  // 遍历原字符串中的每个字母
            t += to_string(c - 'a' + 1);  // c - 'a' + 1 得到 1..26，to_string 转成十进制字符串后拼到 t 末尾（10 以上会占两位）
        }
        s = t;  // 把转换结果赋回 s，后面 k 次变换都在这个数字串上进行
        while (k--) {  // 做 k 次数字和变换；while(k--) 先判断 k 非零再自减
            int t = 0;  // 这一轮的数字和；局部变量 t 遮蔽了外层的 string t，不影响原数字串
            for (char c : s) {  // 遍历当前数字串中的每个字符
                t += c - '0';  // c - '0' 把数字字符转成数值后累加
            }
            s = to_string(t);  // 用这一轮的和替换数字串，供下一轮继续收敛
        }
        return stoi(s);  // k 轮后串已收敛，stoi 转成整数返回
    }
};
