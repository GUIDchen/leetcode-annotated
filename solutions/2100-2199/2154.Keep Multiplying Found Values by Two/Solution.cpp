// 题目：2154. 将找到的值乘以 2（Keep Multiplying Found Values by Two）
// 思路：把数组放进哈希集合，只要 original 还在集合里就不断乘 2，直到集合中查不到为止。
// 时间复杂度：O(n + log M)，建集合 O(n)、倍增 O(log M)（M 为最终值）；空间复杂度：O(n)，哈希集合存放去重后的元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findFinalValue(vector<int>& nums, int original) {  // nums：输入数组；original：初始值；返回最终值
        unordered_set<int> s(nums.begin(), nums.end());  // 哈希集合：把数组元素全部放入，后续可以 O(1) 判断某个值是否存在
        while (s.contains(original)) {  // 只要原值还在集合中，就继续倍增
            original <<= 1;  // 左移一位等价于乘 2
        }  // 结束循环
        return original;  // 集合里查不到该值了，返回最终结果
    }  // 结束方法
};  // 结束题解类