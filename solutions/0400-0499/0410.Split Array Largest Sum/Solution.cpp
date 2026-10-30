// 题目：410. 分割数组的最大值（Split Array Largest Sum）
// 思路：二分答案「子数组和的上限」，判定函数用贪心顺序切分，统计所需段数是否不超过 k。
// 时间复杂度：O(n log(sum - max))，每次判定 O(n)，二分对数值范围；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int splitArray(vector<int>& nums, int k) {  // nums 是非负数组，k 是必须切成的段数（连续子数组）
        int left = 0, right = 0;  // 二分下界 left 与上界 right
        for (int& x : nums) {  // 一遍遍历同时确定二分区间
            left = max(left, x);  // 子数组和不会小于最大元素，故下界取最大值
            right += x;  // 上界取整个数组之和（只切一段时的答案）
        }  // 区间下界初始化结束
        auto check = [&](int mx) {  // 判定函数：子数组和不超过 mx 时，所需段数是否 ≤ k
            int s = 1 << 30, cnt = 0;  // s 置为极大值以保证首元素必触发一次切段；cnt 记录切出的段数
            for (int& x : nums) {  // 贪心顺序累加，不重排数组
                s += x;  // 把当前元素并入当前段
                if (s > mx) {  // 超过上限就必须在此处切开
                    s = x;  // 当前元素成为新一段的开头
                    ++cnt;  // 段数加一
                }  // 超限分支结束
            }  // 累加循环结束
            return cnt <= k;  // 段数不超过 k 说明上限 mx 可行
        };  // 判定 lambda 结束
        while (left < right) {  // 二分答案：寻找最小的可行上限
            int mid = (left + right) >> 1;  // 取中点（右移一位等价于整除 2）
            if (check(mid)) {  // mid 已经可行
                right = mid;  // 答案不会超过 mid，收缩右边界
            } else {  // mid 太小，切出的段数超过 k
                left = mid + 1;  // 答案至少是 mid + 1，收缩左边界
            }  // 分支结束
        }  // 二分结束，left == right 即答案
        return left;  // 返回最小的子数组和最大值
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，此处保持一致）