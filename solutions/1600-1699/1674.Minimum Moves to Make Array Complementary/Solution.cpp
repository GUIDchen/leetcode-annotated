// 题目：1674. 使数组互补的最少操作次数（Minimum Moves to Make Array Complementary）
// 思路：首尾配对后，对每一对 (x ≤ y) 统计「目标和 t 需要几次操作」，用差分数组 d 做区间加，最后前缀和取最小值。
// 时间复杂度：O(n + limit)，配对 O(n/2)、扫描差分数组 O(limit)；空间复杂度：O(limit)，差分数组大小 2·limit + 2。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minMoves(vector<int>& nums, int limit) {  // nums：待配对的数组；limit：每个元素可以变成 1..limit 之间的任意值
        int n = nums.size();  // 数组长度，用于定位对称位置 n - i - 1
        int d[limit * 2 + 2];  // 差分数组：下标是目标和 t，d[t] 记录 t 处操作的增量
        memset(d, 0, sizeof(d));  // 差分数组全部清零，避免受栈上残留值影响
        for (int i = 0; i < n / 2; ++i) {  // 只枚举前半部分，与后半部分首尾配对
            int x = nums[i], y = nums[n - i - 1];  // 取出对称的两个元素 x = nums[i]、y = nums[n-i-1]
            if (x > y) {  // 保证 x ≤ y，方便下面按区间分类
                swap(x, y);  // 交换成有序的两个数
            }  // if 结束
            d[2] += 2;  // t ∈ [2, x]：需要改两个数，整体 +2
            d[x + 1] -= 2;  // t = x + 1 处扣掉 +2 的区间尾
            d[x + 1] += 1;  // t ∈ [x+1, x+y-1]：只需改一个数，区间 +1
            d[x + y] -= 1;  // t = x + y 处扣掉 +1 的区间尾（此处 0 次操作）
            d[x + y + 1] += 1;  // t ∈ [x+y+1, y+limit]：只需改一个数，区间重新 +1
            d[y + limit + 1] -= 1;  // t = y+limit+1 处扣掉 +1 的区间尾
            d[y + limit + 1] += 2;  // t ∈ [y+limit+1, 2·limit]：需要改两个数，恢复 +2
        }  // 配对循环结束，差分数组已记录每对对所有目标和的影响
        int ans = n;  // 答案上界：全部改成 1 也能配对，所以最多 n 次操作
        for (int i = 2, s = 0; i <= limit * 2; ++i) {  // 从 t = 2 开始做前缀和，s 就是目标和为 t 时的总操作数
            s += d[i];  // 累加差分，得到当前目标和的真实操作次数
            ans = min(ans, s);  // 在所有可能的目标和中取最小操作次数
        }  // 扫描结束
        return ans;  // 返回最少操作次数
    }  // 方法结束
};  // 类定义结束