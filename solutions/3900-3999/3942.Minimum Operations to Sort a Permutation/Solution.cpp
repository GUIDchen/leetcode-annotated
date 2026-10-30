// 3942. 排序排列的最少操作数 / Minimum Operations to Sort a Permutation
// 核心思路：以 0 为锚点按步长 +1 与 -1 展开成两种旋转顺序，检查是否递增，再用 0 到端点的距离推出每个方向两种操作方式的代价。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 题解类定义
public:  // 公开接口
    int minOperations(vector<int>& nums) {  // 主函数：返回使排列有序的最少操作数
        int n = nums.size();  // 排列长度

        int zero = ranges::find(nums, 0) - nums.begin();  // 找到 0 所在的下标

        auto check = [&](int step) -> bool {  // 检查按给定步长从 0 展开后是否递增
            for (int i = 1; i < n; i++) {  // 依次比较展开序列中的相邻两项
                int prev = (zero + (i - 1) * step + n) % n;  // 上一位置的下标，加 n 避免负数取模
                int curr = (zero + i * step + n) % n;  // 当前位置的下标

                if (nums[prev] > nums[curr]) {  // 出现逆序
                    return false;  // 该旋转方向不可行
                }  // if 分支结束
            }  // 比较循环结束
            return true;  // 全部有序，方向可行
        };  // check lambda 结束

        int ans = INT_MAX;  // 答案初始化为无穷大

        if (check(1)) {  // 步长为 1 的方向可行
            ans = min(ans, zero);  // 方式一：直接把 0 移到序列开头
            ans = min(ans, n - zero + 2);  // 方式二：反向绕一圈后再进行移动
        }  // if 分支结束

        if (check(-1)) {  // 步长为 -1 的方向可行
            ans = min(ans, zero + 2);  // 方式一：正向绕一圈后再进行移动
            ans = min(ans, n - zero);  // 方式二：直接把 0 移到序列末尾
        }  // if 分支结束

        return ans == INT_MAX ? -1 : ans;  // 两个方向都不可行时返回 -1
    }  // minOperations 函数结束
};  // 类定义结束