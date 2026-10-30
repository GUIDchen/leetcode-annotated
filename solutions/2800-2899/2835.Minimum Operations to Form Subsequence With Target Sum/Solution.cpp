// 题目：2835. 使子序列的和等于目标的最少操作次数（Minimum Operations to Form Subsequence With Target Sum）
// 思路：把每个数按二进制拆成 2 的幂块并统计每层块数，再自低向高构造 target：target 的第 i 位为 1 时，若该层没有剩余块，就从更高层把一个块一路劈半下来（每劈一次算一次操作），累计劈的次数即为答案。
// 时间复杂度：O(32n)，每个元素拆 32 位，之后每层最多被扫过有限次；空间复杂度：O(1)，只用一个长度 32 的计数器数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums, int target) {  // nums：可操作的正整数数组；target：要凑出的目标和
        long long s = 0;  // 所有元素的总和，用来提前判断是否无解
        int cnt[32]{};  // cnt[i] 表示当前可用的「2 的 i 次幂」块的数量，全部初始化为 0
        for (int x : nums) {  // 遍历数组中的每个数
            s += x;  // 累加总和
            for (int i = 0; i < 32; ++i) {  // 逐位检查这个数的二进制表示
                if (x >> i & 1) {  // 第 i 位是 1
                    ++cnt[i];  // 说明它可以拆出一块大小为 2^i 的块
                }
            }
        }
        if (s < target) {  // 总和都不够目标值
            return -1;  // 再怎么操作也凑不出来，返回 -1
        }
        int i = 0, j = 0;  // i：当前要满足的 target 的位下标；j：当前可用的最低位块所在层
        int ans = 0;  // 记录总共需要的操作次数
        while (1) {  // 从低到高逐位满足 target
            while (i < 32 && (target >> i & 1) == 0) {  // 跳过 target 中为 0 的位，它们不需要贡献
                ++i;
            }
            if (i == 32) {  // 32 位都已处理完，说明 target 已被完整凑出
                return ans;  // 返回累计的操作次数
            }
            while (j < i) {  // 把低于第 i 位的小块尽量两两合成更大的块
                cnt[j + 1] += cnt[j] / 2;  // 两块 2^j 等价于一块 2^(j+1)，向上进位
                cnt[j] %= 2;  // 进位后本层最多只剩 0 或 1 块
                ++j;
            }
            while (cnt[j] == 0) {  // 当前层没有块，只能往更高层找更大的块来劈
                cnt[j] = 1;  // 劈一次会让本层留下一个 2^j 的块
                ++j;  // 继续往上一层找可劈的块
            }
            ans += j - i;  // 把一块 2^j 一路劈到 2^i 需要 j-i 次操作，累加代价
            --cnt[j];  // 用掉这一块
            j = i;  // 从第 i 层继续向后推进
            ++i;
        }
    }
};