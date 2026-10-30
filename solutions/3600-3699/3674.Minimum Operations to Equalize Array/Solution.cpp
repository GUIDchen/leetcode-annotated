// 3674. Minimum Operations to Equalize Array（数组元素相等的最小操作次数）
// 核心思路：所有元素相同则无需操作；只要存在与首元素不同的元素，就一定能用一次操作使全部相等。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 定义 Solution 类
public:
    int minOperations(vector<int>& nums) {  // 求使数组元素全部相等的最小操作次数
        for (int x : nums) {  // 遍历数组中的每个元素
            if (x != nums[0]) {  // 发现与首个元素不同的元素
                return 1;  // 存在不同元素，只需一次操作即可全部相等
            }
        }
        return 0;  // 所有元素都相同，无需任何操作
    }
};
