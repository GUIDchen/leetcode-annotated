// 题目：1208. 尽可能使字符串相等（Get Equal Substrings Within Budget）
// 思路：先对「逐位改字符的代价」做前缀和，再二分答案长度，用前缀和 O(1) 判定任一窗口是否可行。
// 时间复杂度：O(n log n)，前缀和 O(n)，二分 O(log n) 轮、每轮 O(n) 判定；空间复杂度：O(n)，需要长度为 n+1 的前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int equalSubstring(string s, string t, int maxCost) {  // s、t：两个等长字符串；maxCost：允许的总修改代价；返回最长可转化的子串长度
        int n = s.size();  // 字符串长度，后续数组规模和二分上界都用到它
        int f[n + 1];  // 代价前缀和数组：f[i] 表示把前 i 个字符改成一样所需的代价
        f[0] = 0;  // 空前缀代价为 0，作为递推的起点
        for (int i = 0; i < n; ++i) {  // 逐位累加代价，构造前缀和
            f[i + 1] = f[i] + abs(s[i] - t[i]);  // 第 i 位的代价是两字符 ASCII 码差的绝对值，累加到前缀和上
        }  // 前缀和构造结束
        auto check = [&](int x) -> bool {  // 判定函数：是否存在长度为 x 的子串，其总代价不超过 maxCost
            for (int i = 0; i + x - 1 < n; ++i) {  // 枚举所有长度为 x 的窗口左端点 i
                int j = i + x - 1;  // 由左端点算出窗口右端点 j
                if (f[j + 1] - f[i] <= maxCost) {  // 前缀和相减即窗口内代价和，不超过预算就说明该长度可行
                    return true;  // 找到一个可行窗口，立即返回真
                }  // 预算判断结束
            }  // 窗口枚举结束
            return false;  // 所有窗口都超预算，长度 x 不可行
        };  // check 判定函数定义结束
        int l = 0, r = n;  // 二分答案区间：最长长度至少 0，至多 n
        while (l < r) {  // 二分「最大的可行长度」
            int mid = (l + r + 1) >> 1;  // 取上中位数，配合下面的 l = mid 避免死循环
            if (check(mid)) {  // 长度 mid 可行；由单调性，比它短的长度一定也可行
                l = mid;  // 保留 mid 作为当前最优，继续向更长的一侧尝试
            } else {  // 长度 mid 不可行，答案只能更短
                r = mid - 1;  // 收缩上界到下中位数
            }  // 二分支结束
        }  // 二分循环结束
        return l;  // 收敛点就是最大可行长度
    }  // equalSubstring 方法结束
};  // 题解类定义结束