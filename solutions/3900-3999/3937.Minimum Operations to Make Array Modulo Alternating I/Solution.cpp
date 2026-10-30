// 3937. 使数组变为模交替数组的最少操作次数 I / Minimum Operations to Make Array Modulo Alternating I
// 核心思路：先把每个元素对 k 取模，再枚举偶数位与奇数位各自的模目标值（必须不同），按模 k 意义下的最短距离累加操作次数。
// 复杂度：时间 O(n * k^2)，空间 O(1)。
class Solution {  // 题解类定义
public:  // 公开接口
    int minOperations(vector<int>& nums, int k) {  // 主函数：返回最少操作次数
        int n = nums.size();  // 数组长度

        for (int& v : nums) {  // 引用遍历，原地修改数组
            v %= k;  // 每个元素先对 k 取模
        }  // 取模循环结束

        int ans = INT_MAX;  // 答案初始化为无穷大

        for (int x = 0; x < k; ++x) {  // 枚举偶数下标的模目标值 x
            for (int y = 0; y < k; ++y) {  // 枚举奇数下标的模目标值 y
                if (x != y) {  // 交替要求两个目标值不同
                    int cnt = 0;  // 当前方案的代价

                    for (int i = 0; i < n; ++i) {  // 遍历数组累加代价
                        int target = (i & 1) ? y : x;  // 按下标奇偶选择目标值
                        int diff = abs(target - nums[i]);  // 当前值与目标的直接差值
                        cnt += min(diff, k - diff);  // 模 k 意义下取更短的距离
                    }  // 代价累加循环结束

                    ans = min(ans, cnt);  // 更新全局最优答案
                }  // if 分支结束
            }  // 内层枚举结束
        }  // 外层枚举结束

        return ans;  // 返回最少操作次数
    }  // minOperations 函数结束
};  // 类定义结束