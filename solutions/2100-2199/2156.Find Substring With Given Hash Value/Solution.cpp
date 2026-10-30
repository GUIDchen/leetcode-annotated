// 题目：2156. 查找给定哈希值的子串（Find Substring With Given Hash Value）
// 思路：先算出最后一个长度为 k 的窗口的哈希，再借助 power^(k-1) 从右向左滚动更新，哈希命中就更新起点，最终得到最靠左的子串。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用常数个整数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string subStrHash(string s, int power, int modulo, int k, int hashValue) {  // s：原串；power：幂底数；modulo：取模数；k：子串长度；hashValue：目标哈希值
        long long h = 0, p = 1;  // h：当前窗口的哈希值；p：power^(k-1) % modulo，滚动时用于减去最高位
        int n = s.size();  // 原串长度 n
        for (int i = n - 1; i >= n - k; --i) {  // 从右往左累加，先算出最后一个长度为 k 的窗口的哈希
            int val = s[i] - 'a' + 1;  // 把字符映射到 1..26
            h = ((h * power % modulo) + val) % modulo;  // 反向累加：越靠窗口左边的字符权重越高
            if (i != n - k) {  // 最右字符权重为 power^0，不计入 p
                p = p * power % modulo;  // 累乘得到 power^(k-1) % modulo
            }  // 结束第一个循环
        }  // 结束初始窗口计算
        int j = n - k;  // 记录答案子串的起始下标，先默认是最后一个窗口
        for (int i = n - k - 1; i >= 0; --i) {  // 窗口整体左移一位，滚动更新哈希
            int pre = s[i + k] - 'a' + 1;  // 即将滑出窗口的最右字符
            int cur = s[i] - 'a' + 1;  // 新进入窗口的最左字符
            h = ((h - pre * p % modulo + modulo) * power % modulo + cur) % modulo;  // 先减去最高位再整体左移，最后加上新字符；+modulo 防止负数取模
            if (h == hashValue) {  // 哈希与目标值相同，说明找到候选子串
                j = i;  // 越往左移动下标越小，最终保留最靠左的起点
            }  // 结束 if 判断
        }  // 结束滚动循环
        return s.substr(j, k);  // 按起点和长度取出答案子串
    }  // 结束方法
};  // 结束题解类