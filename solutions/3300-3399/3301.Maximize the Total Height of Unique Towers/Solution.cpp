// 题目：3301. 高度互不相同的最大塔高和（Maximize the Total Height of Unique Towers）
// 思路：降序排序后贪心，每座塔取 min(自身上限, 上一座高度 - 1)，为后面的塔留出递减空间。
// 时间复杂度：O(n log n)，排序为主；空间复杂度：O(log n)，原地排序所需的栈空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumTotalSum(vector<int>& maximumHeight) {  // maximumHeight：每座塔允许的最大高度；返回高度互不相同的最大总和，做不到返回 -1
        ranges::sort(maximumHeight, greater<int>());  // 从大到小排序，先安排大的塔，后面的塔才有空间保持高度互不相同
        long long ans = 0;  // ans 累加确定的塔高，用 long long 防止溢出
        int mx = 1 << 30;  // mx 记录上一座塔的高度；1<<30 当作“无穷大”，让第一座塔不受限制
        for (int x : maximumHeight) {  // 按上限从大到小依次确定每座塔的高度
            x = min(x, mx - 1);  // 当前塔最高只能取 mx-1，保证与上一座塔高度不同
            if (x <= 0) {  // 高度被压到 0 或负数，说明已无法再分配合法高度
                return -1;  // 无法构造，按题意返回 -1
            }
            ans += x;  // 累加当前塔高
            mx = x;  // 更新上界，供下一座塔使用
        }
        return ans;  // 返回最大总高度
    }
};
