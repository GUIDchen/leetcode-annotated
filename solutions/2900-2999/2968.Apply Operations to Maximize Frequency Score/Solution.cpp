// 题目：2968. 执行操作使频率分数最大（Apply Operations to Maximize Frequency Score）
// 思路：排序后二分答案长度，用前缀和 O(1) 求出把某个窗口全部变成其中位数所需的代价，滑动检查是否存在长度 mid 的可行窗口。
// 时间复杂度：O(n log n)（排序 + 二分 O(log n) 次、每次 O(n) 检查）；空间复杂度：O(n)（前缀和数组）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxFrequencyScore(vector<int>& nums, long long k) {  // nums：初始数组；k：总共可用的加一操作次数（每次可让某个元素 +1）
        sort(nums.begin(), nums.end());  // 先排序：最优方案一定是把一段连续区间的元素都改成同一个值（该区间的中位数）
        int n = nums.size();  // n 为数组长度
        vector<long long> s(n + 1, 0);  // 前缀和数组 s，s[i] 表示前 i 个元素之和；用 long long 防止累加溢出
        for (int i = 1; i <= n; i++) {  // 从 1 开始逐位构造前缀和
            s[i] = s[i - 1] + nums[i - 1];  // 递推式：前 i 项和 = 前 i-1 项和 + 第 i 个元素（下标 0 基）
        }

        int l = 0, r = n;  // 二分答案：在 [0, n] 中找「能凑出至少 l 个相同值」的最大长度
        while (l < r) {  // 循环直到区间收缩到一个点
            int mid = (l + r + 1) >> 1;  // 取上中位数，配合下面的 l = mid 才不会死循环
            bool ok = false;  // 标记长度 mid 是否可行（初始为不可行）

            for (int i = 0; i <= n - mid; i++) {  // 枚举长度为 mid 的所有窗口，i 是窗口左端点，n - mid 是最远的可行左端点
                int j = i + mid;  // j 是窗口右端点的下一个位置，窗口实际覆盖 [i, j-1]
                int x = nums[(i + j) / 2];  // 目标值 x 取窗口的中位数：把整段都变成中位数，总代价最小
                long long left = ((i + j) / 2 - i) * (long long) x - (s[(i + j) / 2] - s[i]);  // 左半段 [i, m-1] 全部提升到 x 的代价：个数乘 x 减去这段原前缀和
                long long right = (s[j] - s[(i + j) / 2]) - ((j - (i + j) / 2) * (long long) x);  // 右半段 [m, j-1] 全部降低到 x 的代价：这段原前缀和减去个数乘 x

                if (left + right <= k) {  // 总代价不超过 k，说明这个长度可以做到
                    ok = true;  // 记录可行，后面只需收缩二分上界
                    break;  // 早停：只要有一个窗口可行就够
                }
            }

            if (ok) {  // 长度 mid 可行
                l = mid;  // 把下界抬到 mid，尝试更长
            } else {  // 长度 mid 不可行
                r = mid - 1;  // 把上界收缩到 mid - 1
            }
        }

        return l;  // 二分结束时 l 就是最大的可行频率分数
    }
};