// 题目：915. 分割数组（Partition Array into Disjoint Intervals）
// 核心思路：先从右往左预处理后缀最小值 mi[i]，再从左往右扫描维护左段最大值 mx；第一个满足 mx <= mi[i] 的下标 i 就是最短左段长度。
// 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(n)，后缀最小值数组。
class Solution {  // 题解类
public:  // 对外接口
    int partitionDisjoint(vector<int>& nums) {  // 返回最小的左段长度 left，使左段最大值 <= 右段最小值
        int n = nums.size();  // 数组长度
        vector<int> mi(n + 1, INT_MAX);  // mi[i] 表示 nums[i..n-1] 的最小值，末尾放哨兵 INT_MAX 以免越界判断
        for (int i = n - 1; ~i; --i) {  // 从右往左预处理后缀最小值（~i 等价于 i >= 0）
            mi[i] = min(nums[i], mi[i + 1]);  // 递推：取当前元素与右侧后缀最小值中的较小者
        }  // 后缀预处理结束
        int mx = 0;  // 从左往右扫描时维护左段最大值（元素非负，初值取 0）
        for (int i = 1;; ++i) {  // 枚举左段长度 i（至少为 1），题目保证有解所以不设上界
            int v = nums[i - 1];  // 把 nums[i-1] 纳入左段
            mx = max(mx, v);  // 更新左段最大值
            if (mx <= mi[i]) {  // 左段最大值不超过右段最小值，说明可以在 i 处分割
                return i;  // 第一次满足条件，即最短左段长度
            }  // 条件不满足则扩大左段继续尝试
        }  // 循环一定在内部 return，这里只是收尾
    }  // 方法结束
};  // 类定义结束