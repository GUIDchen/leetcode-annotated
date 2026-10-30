// 3678. Smallest Absent Positive Greater Than Average（大于平均值的最小未出现正整数）
// 核心思路：哈希集合记录出现过的数并求和，从 max(1, 平均值下取整 + 1) 开始逐个检查是否未出现过。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // 定义 Solution 类
public:
    int smallestAbsent(vector<int>& nums) {  // 求大于平均值且未出现过的最小正整数
        unordered_set<int> s;  // 记录数组中出现过的所有数
        int sum = 0;  // 记录数组元素之和
        for (int x : nums) {  // 遍历数组中的每个元素
            s.insert(x);  // 把 x 加入集合，便于后续判重
            sum += x;  // 累加元素之和
        }
        int ans = max(1, sum / (int) nums.size() + 1);  // 从严格大于平均值的最小正整数开始找
        while (s.contains(ans)) {  // 该数已经出现过
            ++ans;  // 向后继续找下一个候选
        }
        return ans;  // 返回最小未出现且大于平均值的正整数
    }
};
