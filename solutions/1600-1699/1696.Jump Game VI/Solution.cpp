// 题目：1696. 跳跃游戏 VI（Jump Game VI）
// 思路：线性 dp + 单调队列。f[i] 表示跳到 i 的最大得分，f[i] = nums[i] + max(f[i-k..i-1])；用递减队列维护窗口内 f 的最大值。
// 时间复杂度：O(n)，每个下标最多入队、出队一次；空间复杂度：O(n)，f 数组与单调队列各占 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxResult(vector<int>& nums, int k) {  // nums：每一步的得分；k：单次最多能跳的步数
        int n = nums.size();  // 数组长度
        int f[n];  // f[i]：跳到下标 i 时能获得的累计最大得分
        f[0] = 0;  // 起点之前的得分视为 0，保证 i = 0 时能正确取到 nums[0]
        deque<int> q = {0};  // 单调递减队列，存下标，队头是窗口内 f 值最大的位置
        for (int i = 0; i < n; ++i) {  // 依次计算每个位置的最优得分
            if (i - q.front() > k) {  // 队头离当前太远（超过 k 步），已经不可达
                q.pop_front();  // 弹出失效的队头
            }
            f[i] = nums[i] + f[q.front()];  // 从窗口内得分最高的位置跳过来，再加上当前格子的得分
            while (!q.empty() && f[i] >= f[q.back()]) {  // 新来的 f[i] 更大，队尾那些位置的 f 值再也不会被选中
                q.pop_back();  // 弹出队尾，维持队列单调递减
            }
            q.push_back(i);  // 把当前位置加入队列，供后面的位置使用
        }
        return f[n - 1];  // 答案是跳到最后一格的最大得分
    }
};