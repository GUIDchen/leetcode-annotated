// 题目：2952. 需要添加的硬币的最小数量（Minimum Number of Coins to be Added）
// 思路：排序后贪心维护已能凑出的区间 [1, s-1]；硬币面值不超过 s 就并进区间，否则必须补一枚面值 s 的硬币让区间翻倍。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，只用常数额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumAddedCoins(vector<int>& coins, int target) {  // coins：已有硬币面值；target：要凑到的目标值；返回最少需添加的硬币数
        sort(coins.begin(), coins.end());  // 贪心的前提：先把硬币按面值升序排好，从小到大扩展可凑区间
        int ans = 0;  // 答案：需要添加的硬币数量
        for (int i = 0, s = 1; s <= target;) {  // s 表示当前能连续凑出 [1, s-1]；i 扫描已排序的硬币
            if (i < coins.size() && coins[i] <= s) {  // 手头这枚硬币面值不超过 s，说明不会留下凑不出的空隙
                s += coins[i++];  // 取用这枚硬币，可凑区间扩展成 [1, s+coins[i]-1]
            } else {  // 否则出现断层：再大的硬币都补不上 s 这个空位
                s <<= 1;  // 补一枚面值恰为 s 的硬币，可凑区间直接翻倍为 [1, 2s-1]
                ++ans;  // 添加数量加一
            }  // if-else 分支结束
        }  // for 循环结束
        return ans;  // 返回最少需要添加的硬币数
    }  // 方法结束
};  // 类定义结束