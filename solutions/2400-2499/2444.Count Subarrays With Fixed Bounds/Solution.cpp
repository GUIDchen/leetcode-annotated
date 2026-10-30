// 题目：2444. 统计定界子数组的数目（Count Subarrays With Fixed Bounds）
// 思路：枚举右端点 i，维护最近一次 minK、maxK 与越界值的位置，累加 min(j1, j2) - k 的正部。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了几个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {  // 统计最小值恰为 minK、最大值恰为 maxK 的连续子数组个数
        long long ans = 0;  // 累计答案；子数组个数可达 O(n^2)，用 64 位整型防止溢出
        int j1 = -1, j2 = -1, k = -1;  // j1/j2 是 minK/maxK 最近出现的下标，k 是最近出现的越界元素下标
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {  // 枚举右端点 i；size() 返回无符号数，先转 int 避免有符号/无符号比较警告
            if (nums[i] < minK || nums[i] > maxK) {  // 当前元素落在 [minK, maxK] 之外
                k = i;  // 越界元素把数组切成互不影响的若干段，记下新的段边界
            }
            if (nums[i] == minK) {  // 当前元素正好等于下界
                j1 = i;  // 更新 minK 的最新位置
            }
            if (nums[i] == maxK) {  // 当前元素正好等于上界
                j2 = i;  // 更新 maxK 的最新位置
            }
            ans += max(0, min(j1, j2) - k);  // 左端点须在 k 右侧且不晚于 min(j1, j2)，可选个数为 max(0, min(j1, j2) - k)
        }
        return ans;  // 返回以各位置为右端点的合法子数组总数
    }
};  // 类定义结束
