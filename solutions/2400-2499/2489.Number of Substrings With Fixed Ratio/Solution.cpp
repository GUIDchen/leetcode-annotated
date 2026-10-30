// 题目：2489. 固定比率的子字符串数（Number of Substrings With Fixed Ratio）
// 思路：把 n0/n1 == num1/num2 变形为 n1*num1 - n0*num2 == 0，用前缀特征值之差为 0 来统计，哈希表记录每个前缀值出现次数。
// 时间复杂度：O(n)，一次遍历加 O(1) 均摊查表；空间复杂度：O(n)，哈希表最多保存 n+1 个前缀值。
using ll = long long;  // 用 ll 作为 long long 的简写，后续计数统一用 64 位整数

class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    long long fixedRatio(string s, int num1, int num2) {  // s 是只含 '0' 与 '1' 的字符串；num1:num2 是目标比率
        ll n0 = 0, n1 = 0;  // 前缀中 '0' 与 '1' 的个数，初始为空前缀（都为 0）
        ll ans = 0;  // 满足比率的子串个数，可达 O(n^2) 量级，必须用 64 位
        unordered_map<ll, ll> cnt;  // 哈希表：键是前缀特征值 x，值是它此前出现的次数
        cnt[0] = 1;  // 空前缀的特征值 0 先记 1 次，用来统计从下标 0 开始的子串
        for (char& c : s) {  // 从左到右扩展前缀，逐字符累计
            n0 += c == '0';  // 当前字符是 '0' 就让 n0 加 1（比较结果是 0/1）
            n1 += c == '1';  // 当前字符是 '1' 就让 n1 加 1
            ll x = n1 * num1 - n0 * num2;  // 前缀特征值；两处特征值相等，则中间子串满足 n1*num1 == n0*num2
            ans += cnt[x];  // 之前每个相同特征值都能和当前位置配成一个合法子串
            ++cnt[x];  // 当前特征值出现次数加一，供后面的位置继续配对
        }  // 遍历结束
        return ans;  // 返回合法子串总数
    }  // 方法结束
};  // 类定义结束