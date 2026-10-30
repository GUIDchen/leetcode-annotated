// 题目：2702. 使数字变为非正数的最小操作次数（Minimum Operations to Make Numbers Non-positive）
// 核心思路：二分答案 t。每次操作可以让一个数减 x、其余所有数减 y，所以 t 次操作等于每个数都先减 t*y，再额外挑某些数各多减 t*(x-y) 的量（即多给一次 x 操作）；逐个元素算出它「至少需要几次 x 操作」，总数不超过 t 就可行。
// 时间复杂度：O(n log(max(nums)))，二分 log 级别，每次 check 扫一遍数组；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums, int x, int y) {  // nums：数组；x：每次额外单独减的量；y：每次对其余元素统一减的量
        int l = 0, r = *max_element(nums.begin(), nums.end());  // 答案上界：即使每次都用 y 去减最大值，t 次也够用，故 r 取最大值
        auto check = [&](int t) {  // 判定函数：t 次操作是否足以把所有数变成非正数
            long long cnt = 0;  // cnt：所有元素「必须用 x 操作」的次数总和
            for (int v : nums) {  // 逐个元素估算它需要多少次 x 操作
                if (v > 1LL * t * y) {  // 只靠 t 次 y 还不够减到非正（1LL 防 int 乘法溢出）
                    cnt += (v - 1LL * t * y + x - y - 1) / (x - y);  // 向上取整 (v - t*y) / (x - y)：补上 x 操作比 y 多减的部分
                }
            }
            return cnt <= t;  // 单元素额外操作的次数总和不超过总操作次数 t，就说明 t 次够用
        };
        while (l < r) {  // 二分最小的可行 t
            int mid = (l + r) >> 1;  // 取中点，>> 1 等价于整除 2
            if (check(mid)) {  // mid 次操作可行
                r = mid;  // 答案不会比 mid 大，收缩右边界
            } else {  // mid 次不够用
                l = mid + 1;  // 答案至少是 mid + 1，抬高左边界
            }
        }
        return l;  // 二分收敛到最小可行操作次数
    }
};