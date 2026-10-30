// 3461. 判断操作后字符串中的数字是否相等 I / Check If Digits Are Equal in String After Operations I
// 核心思路：按题意暴力模拟，每轮把相邻两位相加后对 10 取个位，长度减一直至只剩两位，再比较这两位。
// 复杂度：时间 O(n^2)，空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有方法
    bool hasSameDigits(string s) {  // 判断反复相邻求和后最后剩下的两位是否相等
        int n = s.size();  // 字符串长度
        string t = s;  // 拷贝一份，在副本上原地模拟
        for (int k = n - 1; k > 1; --k) {  // 每轮长度减一，直到只剩两位
            for (int i = 0; i < k; ++i) {  // 遍历本轮需要计算的 k 个位置
                t[i] = (t[i] - '0' + t[i + 1] - '0') % 10 + '0';  // 两位数字相加取个位，再转回字符
            }  // 结束内层循环
        }  // 结束外层循环
        return t[0] == t[1];  // 仅剩两位，判断是否相等
    }  // 结束方法
};  // 结束类定义
