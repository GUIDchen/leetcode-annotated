// 题目：2866. 美丽塔 II（Beautiful Towers II）
// 思路：单调栈求每个位置左边/右边第一个严格更矮的位置，得到以 i 为山顶时左侧递降前缀和 f[i] 与右侧递降后缀和 g[i]，答案取 max(f[i] + g[i] - maxHeights[i])。
// 时间复杂度：O(n)，每个下标最多进出栈一次；空间复杂度：O(n)，存放左右边界与两个前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumSumOfHeights(vector<int>& maxHeights) {  // maxHeights：每座塔的高度上限，返回最大高度和
        int n = maxHeights.size();  // 塔的数量
        stack<int> stk;  // 单调栈，存下标，对应的高度从栈底到栈顶单调不降
        vector<int> left(n, -1);  // left[i] 是 i 左边第一个高度严格小于 maxHeights[i] 的下标，找不到则为 -1
        vector<int> right(n, n);  // right[i] 是 i 右边第一个高度小于等于 maxHeights[i] 的下标，找不到则为 n
        for (int i = 0; i < n; ++i) {  // 从左往右一遍，求 left
            int x = maxHeights[i];  // 当前位置的高度上限
            while (!stk.empty() && maxHeights[stk.top()] > x) {  // 栈顶比当前高，说明它不可能是当前及以后位置的最近更矮点
                stk.pop();  // 弹出栈顶，维持栈内高度单调不降
            }
            if (!stk.empty()) {  // 弹完之后栈顶就是左边第一个严格更矮的位置
                left[i] = stk.top();  // 记录左边界
            }
            stk.push(i);  // 当前下标入栈，供右边的位置使用
        }
        stk = stack<int>();  // 清空栈，准备从右往左再扫一遍
        for (int i = n - 1; ~i; --i) {  // 从右往左扫；~i 等价于 i >= 0
            int x = maxHeights[i];  // 当前位置的高度上限
            while (!stk.empty() && maxHeights[stk.top()] >= x) {  // 用 >= 弹栈，把等高的右侧位置留给它自己，避免重复计算
                stk.pop();  // 弹出栈顶，维持栈内高度单调不降
            }
            if (!stk.empty()) {  // 栈顶是右边第一个高度小于当前值的位置
                right[i] = stk.top();  // 记录右边界
            }
            stk.push(i);  // 当前下标入栈，供左边的位置使用
        }
        long long f[n], g[n];  // f[i]：以 i 为山顶时左半部分（含 i）的高度和；g[i]：右半部分（含 i）的高度和
        for (int i = 0; i < n; ++i) {  // 正序递推 f
            int x = maxHeights[i];  // 当前位置的高度上限
            if (i && x >= maxHeights[i - 1]) {  // 左边邻居不比它高，左侧仍可保持原样的高度序列
                f[i] = f[i - 1] + x;  // 直接沿用 f[i-1]，再补上自己这一格
            } else {  // 左边邻居更高，需要把一段区间压低到 x
                int j = left[i];  // j 是左边第一个比 x 矮的位置
                f[i] = 1LL * x * (i - j) + (j != -1 ? f[j] : 0);  // 区间 (j, i] 全部填 x；j 及以左沿用 f[j]
            }
        }
        for (int i = n - 1; ~i; --i) {  // 逆序递推 g
            int x = maxHeights[i];  // 当前位置的高度上限
            if (i < n - 1 && x >= maxHeights[i + 1]) {  // 右边邻居不比它高，右侧序列可以直接复用
                g[i] = g[i + 1] + x;  // 沿用 g[i+1]，再补上自己这一格
            } else {  // 右边邻居更高，需要把一段区间压低到 x
                int j = right[i];  // j 是右边第一个不高于 x 的位置
                g[i] = 1LL * x * (j - i) + (j != n ? g[j] : 0);  // 区间 [i, j) 全部填 x；j 及其右侧沿用 g[j]
            }
        }
        long long ans = 0;  // 记录最大的高度和
        for (int i = 0; i < n; ++i) {  // 枚举每个位置作为山顶
            ans = max(ans, f[i] + g[i] - maxHeights[i]);  // 左右两段都含 i，减去重复算了一次的山顶高度
        }
        return ans;  // 返回最大高度和
    }
};