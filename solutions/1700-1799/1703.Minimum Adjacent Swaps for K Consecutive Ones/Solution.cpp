// 题目：1703. 得到连续 K 个 1 的最少相邻交换次数（Minimum Adjacent Swaps for K Consecutive Ones）
// 思路：记录每个 1 的下标，枚举由连续 k 个 1 组成的窗口，以窗口内中位的那个 1 作不动的锚点；再用前缀和 O(1) 算出其余 1 向锚点靠拢所需的总交换次数。
// 时间复杂度：O(n)，统计位置 O(n)，窗口滑动 O(n)；空间复杂度：O(n)，需要存 1 的下标与前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minMoves(vector<int>& nums, int k) {  // nums 是 0/1 数组，k 是要求的连续 1 的个数
        vector<int> arr;  // 记录每个 1 在 nums 中的原始下标
        for (int i = 0; i < nums.size(); ++i) {  // 一次扫描收集所有 1 的位置
            if (nums[i]) {  // 当前位是 1
                arr.push_back(i);  // 把它的下标存进 arr，后面按下标做计算
            }
        }
        int m = arr.size();  // 1 的总个数，窗口右边界不能超过它
        long s[m + 1];  // 前缀和数组，s[i] 表示 arr 前 i 个元素之和（含固定偏移）
        s[0] = 1;  // 起点置 1，相当于给所有前缀和统一加一个常数，做差时会被抵消
        for (int i = 0; i < m; ++i) {  // 递推构造前缀和
            s[i + 1] = s[i] + arr[i];  // s[i + 1] 等于前 i 个和再加上第 i 个元素
        }
        long ans = 1L << 60;  // 用一个足够大的数作为答案初值（约 1.15e18）
        int x = (k + 1) / 2;  // 窗口内中位元素左边（含自己）的个数，向上取整
        int y = k - x;  // 中位元素右边的个数
        for (int i = x - 1; i < m - y; ++i) {  // 枚举中位 1 的下标 i，保证两侧元素都不越界
            int j = arr[i];  // 中位 1 的原始下标，也就是这 k 个 1 的最终聚集锚点
            long ls = s[i + 1] - s[i + 1 - x];  // 左侧 x 个 1（含中位）的原始下标和
            long rs = s[i + 1 + y] - s[i + 1];  // 右侧 y 个 1 的原始下标和
            long a = (j + j - x + 1L) * x / 2 - ls;  // 把左侧这些 1 紧挨着贴到 j 左边所需的交换次数
            long b = rs - (j + 1L + j + y) * y / 2;  // 把右侧这些 1 紧挨着贴到 j 右边所需的交换次数
            ans = min(ans, a + b);  // 取所有锚点里总代价最小的那个
        }
        return ans;  // 返回最少相邻交换次数
    }
};