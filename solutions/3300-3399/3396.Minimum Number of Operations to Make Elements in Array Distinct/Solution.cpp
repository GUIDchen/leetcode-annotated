// 3396. 使数组元素互不相同所需的最少操作次数 / Minimum Number of Operations to Make Elements in Array Distinct
// 核心思路：每次操作都删除前 3 个元素，因此从右往左找第一个重复元素，它的下标 i 决定了必须把前 i+1 个元素全部删掉，操作次数即 i/3 + 1；若没有重复则为 0
// 复杂度：时间 O(n)、空间 O(n)
class Solution {  // 定义 Solution 类
public:  // 公有方法
    int minimumOperations(vector<int>& nums) {  // 求使数组元素互不相同所需的最少操作次数
        unordered_set<int> s;  // 哈希集合记录已经扫描过的元素
        for (int i = nums.size() - 1; ~i; --i) {  // 从数组末尾向前遍历每个下标
            if (s.contains(nums[i])) {  // 若当前元素已经出现过，说明它及之前的整个前缀都必须被删除
                return i / 3 + 1;  // 删除前 i+1 个元素需要 (i+1+2)/3 次操作，化简为 i/3 + 1
            }  // 判断结束
            s.insert(nums[i]);  // 记录当前元素
        }  // 循环结束
        return 0;  // 没有发现重复元素，无需任何操作
    }  // 方法结束
};  // 类定义结束
